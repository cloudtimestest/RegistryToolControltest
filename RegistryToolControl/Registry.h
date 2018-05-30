/*****************************************************************************
Copyright: 2013-, Beijing Cloud Times Technology Co., Ltd.
File name: Registry.h
Description:  Encapsulate the access of registry
Author: sunlei
Version: 1.0.0
Date: 2013.12.04
History: 
*****************************************************************************/
#ifndef _REGISTRY_HEADER_

#define _REGISTRY_HEADER_

#include <windows.h>

class Registry
{
public:
	//Check if the registry key exists.
	BOOL RegKeyExists(const HKEY hRootKey, LPCTSTR lpSubKey);

	//Check if the value name exists
	BOOL RegValueExists(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const DWORD valueType);

	//Get the string value for the specified value name 
	BOOL RegQueryStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPTSTR lpData);

	//Get value of the 32-bit number for the specified value name 
	BOOL RegQueryDwordValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD& lpData);

	//Get value of the sequence of string for the specified value name 
	BOOL RegQueryMultiStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);

	//Set the string value to the specified value name
	BOOL RegWriteStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);

	//Set value of the 32-bit number to the specified value name
	BOOL RegWriteDwordValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const DWORD lpData);

	//Set string that contains unexpanded references to environment variables to the specified value name
	BOOL RegWriteExpStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);

	//Set binary data to the specified value name
	BOOL RegwriteBinaryValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPBYTE lpData, DWORD length);

	////Set the sequence of string to the specified value name
	BOOL RegWriteMultiStringValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);

	//Removes the specified value 
	BOOL RegDeleteValue(const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName);

	//Deletes a subkey and its values
	BOOL RegDeleteKey(const HKEY hRootKey, LPCTSTR lpSubKey);

	//Creates the specified registry key
	BOOL RegCreateKey(const HKEY hRootKey, LPCTSTR lpSubKey);

	//obsoleted
	//BOOL RegWriteUserStringValue(LPCTSTR mUser, const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);
	//BOOL RegDeleteUserValue(LPCTSTR mUser, const HKEY hRootKey, LPCTSTR lpSubKey, LPCTSTR lpValueName);
protected:
private:
	//obsoleted
	//BOOL RegWriteNoCurUserStringValue(LPCTSTR mUser, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpData);
	//BOOL RegDeleteNoCurUserValue(LPCTSTR mUser, LPCTSTR lpSubKey, LPCTSTR lpValueName);
};
#endif //_REGISTRY_HEADER_