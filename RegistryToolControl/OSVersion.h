/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: OSVersion.h
Description:  The OSVersion class supply the method to get OS version.
Author: sunlei
Version: 2.0.0
Date: 2013.12.02
History: 
*****************************************************************************/
#ifndef _OS_VERSION_HEADER_

#define _OS_VERSION_HEADER_

#include <Windows.h>

enum OSType
{
	WIN_XP,
	WIN_7,
	WIN_XX
};

class OSVersion
{
public:
	BOOL GetSystemVersion(DWORD &version);
protected:
private:
};
#endif //_OS_VERSION_HEADER_