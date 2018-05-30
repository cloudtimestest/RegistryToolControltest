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

	//控制指定用户下的注册表编辑工具
	BOOL RegistryToolEnable(LPTSTR mUser, BOOL isEnable);
private:
	//控制当前用户
	BOOL RegistryToolEnableForCurrentUser(BOOL isEnable);

	//控制非当前用户，实现跨用户操作
	BOOL RegistryToolEnableForOtherUser(LPTSTR mUser, BOOL isEnable);

private:
	DWORD m_dwOSVersion;
};

#endif