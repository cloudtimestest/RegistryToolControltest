/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: OSVersion.cpp
Description:  The OSVersionManager class supply the method to get OS version.
Author: sunlei
Version: 2.0.0
Date: 2013.12.02
History: 
*****************************************************************************/

#include "stdafx.h"
#include "OSVersion.h"

/*************************************************
Function: GetSystemVersion
Description: Get the current os version
Parameters: void
Output: the os version
*************************************************/
BOOL OSVersion::GetSystemVersion(DWORD &version)
{
	BOOL ret = FALSE;

	OSVERSIONINFO osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	ret = GetVersionEx(&osvi);

	if (5 == osvi.dwMajorVersion)
	{
		version = WIN_XP;
	} 
	else if (6 == osvi.dwMajorVersion)
	{
		version = WIN_7;
	} 
	else	//deal as unknown if the current os is not xp or win7.
	{
		version = WIN_XX;
	}


	return ret;
}