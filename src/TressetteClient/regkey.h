// regkey.h


#ifndef _REGKEY_H_
#define _REGKEY_H_

#include "win_type_global.h"
#include <string>

#include <assert.h>


class RegistryKey
{
public:
	RegistryKey();
	~RegistryKey();

// Attributes
public:
	operator HKEY() const;

protected:  
  HKEY m_hKey;

// Operations
public:
	LONG SetValue  (DWORD   dwValue,   LPCTSTR lpszValueName);
	LONG SetValue  (LPCTSTR lpszValue, LPCTSTR lpszValueName);
	LONG SetValue  (const std::string&,    LPCTSTR lpszValueName);
	LONG SetValue  (LPBYTE  lpValue,   DWORD len, LPCTSTR lpszValueName = NULL);

	LONG QueryValue(DWORD&  dwValue,   LPCTSTR lpszValueName);
	LONG QueryValue(LPTSTR  szValue,   LPCTSTR lpszValueName, DWORD* pdwCount);
	LONG QueryValue(LPBYTE  lpValue,   DWORD& len, LPCTSTR lpszValueName);
	LONG QueryValue(std::string& szValue,  LPCTSTR lpszValueName);

    BOOL    getRegBoolValue(BOOL aValue, const TCHAR* aValName);
    DWORD   getRegDWordValue(DWORD aValue, const TCHAR* aValName);
    std::string getRegStringValue(const TCHAR* aValue, const TCHAR* aValName);
    void    setRegBoolValue(BOOL aValue, const TCHAR* aValName);
    void    setRegDWordValue(DWORD aValue, const TCHAR* aValName);
    void    setRegStringValue(const TCHAR* aValue, const TCHAR* aValName);

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	LONG Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		REGSAM samDesired = KEY_ALL_ACCESS,
		LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		LPDWORD lpdwDisposition = NULL);
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,REGSAM samDesired = KEY_ALL_ACCESS);
	LONG Close();
	HKEY Detach();
	void Attach(HKEY hKey);
	LONG DeleteSubKey(LPCTSTR lpszSubKey);
	LONG RecurseDeleteKey(LPCTSTR lpszKey);
	LONG DeleteValue(LPCTSTR lpszValue);
	LONG Flush();
};

inline RegistryKey::RegistryKey()
{
	m_hKey = NULL;
}

inline RegistryKey::~RegistryKey()
{
	Close();
}

inline RegistryKey::operator HKEY() const
{
	return m_hKey;
}

inline HKEY RegistryKey::Detach()
{
	HKEY hKey = m_hKey;
	m_hKey = NULL;
	return hKey;
}

inline void RegistryKey::Attach(HKEY hKey)
{
	assert(m_hKey == NULL);
	m_hKey = hKey;
}

inline LONG RegistryKey::DeleteSubKey(LPCTSTR lpszSubKey)
{
	assert(m_hKey != NULL);
	return RegDeleteKey(m_hKey, lpszSubKey);
}

inline LONG RegistryKey::DeleteValue(LPCTSTR lpszValue)
{
	assert(m_hKey != NULL);
	return RegDeleteValue(m_hKey, (LPTSTR)lpszValue);
}

inline LONG RegistryKey::Flush()
{
	assert(m_hKey != NULL);
  return RegFlushKey(m_hKey);
}

#endif
