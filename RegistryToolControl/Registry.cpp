/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: Registry.cpp
Description:  Encapsulate the access of registry
Author: sunlei
Version: 1.0.0
Date: 2013.12.04
History: 
*****************************************************************************/
#include "stdafx.h"
#include "Registry.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
#pragma comment(lib, "Advapi32.lib")

/*************************************************
Function: RegKeyExists
Description: Check if the registry key exists.
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be checked
Output: Return nonzero if the subkey not exist. Otherwise, zero.
*************************************************/
BOOL Registry::RegKeyExists(const HKEY hRootKey, LPCTSTR lpSubKey)
{
	BOOL ret = FALSE;
	HKEY hKey = NULL;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_QUERY_VALUE , &hKey) == ERROR_SUCCESS )
	{
		ret = TRUE;
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

/*************************************************
Function: RegValueExists
Description: Check if the value name exists
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be opened
			 lpValueName:	The name of the registry value
			 valueType:		The type of data to be checked
Output: Return nonzero if the value exists. Otherwise, zero.
*************************************************/
BOOL Registry::RegValueExists(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const DWORD valueType)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = valueType;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_QUERY_VALUE , &hKey) == ERROR_SUCCESS )
	{
		if (RegQueryValueEx(hKey, lpValueName, NULL, &valType, NULL, NULL) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

/*************************************************
Function: RegQueryStringValue
Description: Get the string value for the specified value name 
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be opened
			 lpValueName:	The name of the registry value
			 lpData:		A pointer to a buffer that receives the value's data
Output: Return nonzero if the date of value got. Otherwise, zero.
*************************************************/
BOOL Registry::RegQueryStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPTSTR lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_SZ;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_QUERY_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = MAX_PATH;
		if (RegQueryValueEx(hKey, lpValueName, NULL, &valType, (LPBYTE )lpData, &retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

//Get value of the 32-bit number for the specified value name 
BOOL Registry::RegQueryDwordValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD& lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_DWORD;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_QUERY_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = sizeof(REG_DWORD);
		if (RegQueryValueEx(hKey, lpValueName, NULL, &valType, (LPBYTE)(&lpData), &retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

/*************************************************
Function: RegWriteStringValue
Description: Set the string value to the specified value name 
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be opened
			 lpValueName:	The name of the registry value
			 lpData:		The data to be stored
Output: Return nonzero if the date of value setted. Otherwise, zero.
*************************************************/
BOOL Registry::RegWriteStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_SZ;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_SET_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = _tcslen(lpData)*sizeof(TCHAR);
		if (RegSetValueEx(hKey, lpValueName, NULL, valType, (LPBYTE)(lpData), retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

//Set value of the 32-bit number to the specified value name
BOOL Registry::RegWriteDwordValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const DWORD lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_DWORD;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_SET_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = sizeof(REG_DWORD);
		if (RegSetValueEx(hKey, lpValueName, NULL, valType, (LPBYTE)(&lpData), retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

/*************************************************
Function: RegDeleteValue
Description: Removes the specified value  
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be opened
			 lpValueName:	The name of the registry value is to delete
Output: Return nonzero if the date of value deleted. Otherwise, zero.
*************************************************/
BOOL Registry::RegDeleteValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName)
{
	BOOL ret = FALSE;

	if (SHDeleteValue(hRootKey, lpSubKey, lpValueName) == ERROR_SUCCESS)
	{
		ret = TRUE;
	}

	return ret;
}

//Deletes a subkey and its values
BOOL Registry::RegDeleteKey(const HKEY hRootKey, LPCTSTR lpSubKey)
{
	BOOL ret = FALSE;

	if (SHDeleteKey(hRootKey, lpSubKey) == ERROR_SUCCESS)
	{
		ret = TRUE;
	}

	return ret;
}

/*************************************************
Function: RegCreateKey
Description: Creates the specified registry key  
Parameters:  hRootKey:		A handle to an open registry key
		     lpSubKey:		The name of the registry subkey to be created
Output: Return nonzero if the subkey created. Otherwise, zero.
*************************************************/
BOOL Registry::RegCreateKey(const HKEY hRootKey, LPCTSTR lpSubKey)
{
	BOOL ret = FALSE;
	HKEY hKey = NULL;
	DWORD lpdwDisposition = 0;

	if (RegCreateKeyEx(hRootKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, &lpdwDisposition) == ERROR_SUCCESS)
	{
		ret = TRUE;
		
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

//Set string that contains unexpanded references to environment variables to the specified value name
BOOL Registry::RegWriteExpStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_EXPAND_SZ;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_SET_VALUE , &hKey) == ERROR_SUCCESS )
	{
		//TCHAR dstStr[MAX_PATH];
		//memset(dstStr, 0, MAX_PATH*sizeof(TCHAR));
		//DWORD retLength = ExpandEnvironmentStrings(lpData, dstStr, MAX_PATH);
		//retLength = retLength * sizeof(TCHAR);

		DWORD retLength = _tcslen(lpData) * sizeof(TCHAR);
		if (RegSetValueEx(hKey, lpValueName, NULL, valType, (LPBYTE)(lpData), retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

//Set binary data to the specified value name
BOOL Registry::RegwriteBinaryValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPBYTE lpData, DWORD length)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_BINARY;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_SET_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = length;
		if (RegSetValueEx(hKey, lpValueName, NULL, valType, (LPBYTE)(lpData), retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

////Set the sequence of string to the specified value name
BOOL Registry::RegWriteMultiStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_MULTI_SZ;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_SET_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = _tcslen(lpData) * sizeof(TCHAR);
		if (RegSetValueEx(hKey, lpValueName, NULL, valType, (LPBYTE)(lpData), retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}

//Get value of the sequence of string for the specified value name
BOOL Registry::RegQueryMultiStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData)
{
	BOOL ret = FALSE;

	HKEY hKey = NULL;
	DWORD valType = REG_MULTI_SZ;

	if (RegOpenKeyEx(hRootKey, lpSubKey, 0, KEY_QUERY_VALUE , &hKey) == ERROR_SUCCESS )
	{
		DWORD retLength = MAX_PATH;
		if (RegQueryValueEx(hKey, lpValueName, NULL, &valType, (LPBYTE )lpData, &retLength) == ERROR_SUCCESS)
		{
			ret = TRUE;
		}

		RegCloseKey(hKey);
		hKey = NULL;
	}

	return ret;
}