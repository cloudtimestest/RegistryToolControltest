/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: RegistryControl.h
Description:  set the priority to access to registry editing tools.
Author: sunlei
Version: 1.0.0
Date: 2013.12.06
History: 
*****************************************************************************/
#ifndef _REGISTRY_CONTROL_HEADER_

#define _REGISTRY_CONTROL_HEADER_

class RegistryControl
{
public:
	RegistryControl();
	~RegistryControl();

	//����ָ���û��µ�ע���༭����
	BOOL RegistryToolEnable(LPTSTR mUser, BOOL isEnable);
private:
	//���Ƶ�ǰ�û�
	BOOL RegistryToolEnableForCurrentUser(BOOL isEnable);

	//���Ʒǵ�ǰ�û���ʵ�ֿ��û�����
	BOOL RegistryToolEnableForOtherUser(LPTSTR mUser, BOOL isEnable);

private:
	DWORD m_dwOSVersion;
};

#endif