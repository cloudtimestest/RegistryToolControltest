/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: RegistryControl.cpp
Description:  set the priority to access to registry editing tools.
Author: sunlei
Version: 1.0.0
Date: 2013.12.06
History: 
*****************************************************************************/

#include "stdafx.h"

#include "Registry.h"
#include "OSVersion.h"
#include "RegistryControl.h"

#define INITGUID
#include <Guiddef.h>
#include <Gpedit.h>
//#include <objbase.h>

//#pragma comment(lib, "ole32.lib")


RegistryControl::RegistryControl()
{
	OSVersion osVersion;
	m_dwOSVersion = WIN_XX;
	osVersion.GetSystemVersion(m_dwOSVersion);
}

RegistryControl::~RegistryControl()
{

}

/*************************************************
Function: RegistryToolEnable
Description: ����ָ���û��µ�ע���༭����
Parameters:  mUser:			Ҫ�������û���
		     isEnable:		���û����
Output: Return nonzero if the setting is made successfully. Otherwise, zero.
*************************************************/
BOOL RegistryControl::RegistryToolEnable(LPTSTR mUser, BOOL isEnable)
{
	BOOL ret = FALSE;

	TCHAR curUserName[MAX_PATH] = {0};
	DWORD dwLength = MAX_PATH - 1;

	//��õ�ǰ�û���
	if (GetUserName(curUserName, &dwLength))
	{
		if (_tcsicmp(curUserName, mUser) == 0)  //���õ�ǰ�û�
		{
			ret = RegistryToolEnableForCurrentUser(isEnable);
		} 
		else  //���û�����
		{
			ret = RegistryToolEnableForOtherUser(mUser, isEnable);
		}
	}

	return ret;
}

//����ע���ʵ��ע����ߵ����úͽ���
BOOL RegistryControl::RegistryToolEnableForCurrentUser(BOOL isEnable)
{
	BOOL ret = FALSE;

	Registry regOper;

	if (isEnable)
	{
		//ɾ��ע���ֵ DisableRegistryTools������ע�����
		if (regOper.RegValueExists(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), _T("DisableRegistryTools"), REG_DWORD))
		{
			ret = regOper.RegDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), _T("DisableRegistryTools"));
		}
	}
	else
	{
		//
		if (!regOper.RegKeyExists(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System")))
		{
			regOper.RegCreateKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"));
		}

		DWORD value = 2;

		//����ע���ֵ DisableRegistryToolsΪ2������ע�����
		ret = regOper.RegWriteDwordValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), _T("DisableRegistryTools"), value);
	}

	IGroupPolicyObject *pGPO = NULL;

	CoInitialize(NULL);

	CoCreateInstance(CLSID_GroupPolicyObject, NULL, CLSCTX_ALL,IID_IGroupPolicyObject, (LPVOID*)&pGPO);
	GUID RegistryId = REGISTRY_EXTENSION_GUID;
	//save method �ĵ�һ������һ��ҪTrue
	pGPO->Save(TRUE,TRUE,const_cast<GUID*>(&RegistryId),const_cast<GUID*>(&CLSID_GPESnapIn));
	pGPO->Release();

	CoUninitialize();

	return ret;
}

//���û�����ע���
BOOL RegistryControl::RegistryToolEnableForOtherUser(LPTSTR mUser, BOOL isEnable)
{
	BOOL ret = FALSE;

	TCHAR keyName[MAX_PATH] = {0};
	TCHAR FileName[MAX_PATH] = {0};
	TCHAR sysDrive[MAX_PATH] = {0};

	Registry registry;

	//���ע����ļ�·��
	ExpandEnvironmentStrings(_T("%SystemDrive%"), sysDrive, MAX_PATH-1);

	_sntprintf(keyName, MAX_PATH-1, _T("HKU\\%s"),mUser);

	//WES09��WES7·����ͬ
	switch (m_dwOSVersion)
	{
	case WIN_XP:
		{
			_sntprintf(FileName, MAX_PATH-1, _T("%s\\Documents and Settings\\%s\\ntuser.dat"), sysDrive, mUser);
		}
		break;
	case WIN_7:
		{
			_sntprintf(FileName, MAX_PATH-1, _T("%s\\Users\\%s\\ntuser.dat"), sysDrive, mUser);
		}
		break;
	default:
		break;
	}

	//����ָ���û���ע��������ļ�
	TCHAR parameter[MAX_PATH] = {0};
	_sntprintf(parameter, MAX_PATH-1, _T("LOAD \"%s\" \"%s\""), keyName, FileName);
	ShellExecute(NULL, _T("open"), _T("REG"), parameter, NULL, SW_HIDE);

	Sleep(800);

	TCHAR subKey[MAX_PATH] = {0};
	_sntprintf(subKey, MAX_PATH-1, _T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), mUser);

	//�޸�ָ���û�ע���
	if (isEnable)
	{
		if (registry.RegValueExists(HKEY_USERS, subKey, _T("DisableRegistryTools"), REG_DWORD))
		{
			ret = registry.RegDeleteValue(HKEY_USERS, subKey, _T("DisableRegistryTools"));
		}
	} 
	else
	{
		if (!registry.RegKeyExists(HKEY_USERS, subKey))
		{
			registry.RegCreateKey(HKEY_USERS, subKey);
		}

		DWORD value = 2;

		ret = registry.RegWriteDwordValue(HKEY_USERS, subKey, _T("DisableRegistryTools"), value);
	}
	
	//�ӳٵȴ�����֤ע���Ķ���Ч
	Sleep(800);

	//ж�������ļ�
	memset(parameter, 0, MAX_PATH*sizeof(TCHAR));
	_sntprintf(parameter, MAX_PATH-1, _T("UNLOAD \"%s\""), keyName);
	ShellExecute(NULL, _T("open"), _T("REG"), parameter, NULL, SW_HIDE);

	return ret;
}