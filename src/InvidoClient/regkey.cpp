// regkey.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include "regkey.h"

/////////////////////////////////////////////////////////////////////////////
// RegistryKey

LONG RegistryKey::Close()
{
    LONG lRes = ERROR_SUCCESS;
    if (m_hKey != NULL)
    {
        lRes = RegCloseKey(m_hKey);
        m_hKey = NULL;
    }
    return lRes;
}

LONG RegistryKey::Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
                         LPTSTR lpszClass, DWORD dwOptions, REGSAM samDesired,
                         LPSECURITY_ATTRIBUTES lpSecAttr, LPDWORD lpdwDisposition)
{
    assert(hKeyParent != NULL);
    DWORD dw;
    HKEY hKey = NULL;
    LONG lRes = RegCreateKeyEx(hKeyParent, 
        lpszKeyName, 
        0,
        lpszClass, 
        dwOptions, 
        samDesired, 
        lpSecAttr, 
        &hKey, 
        &dw);
    if (lpdwDisposition != NULL)
        *lpdwDisposition = dw;
    if (lRes == ERROR_SUCCESS)
    {
        lRes = Close();
        m_hKey = hKey;
    }
    return lRes;
}

LONG RegistryKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired)
{
    assert(hKeyParent != NULL);
    HKEY hKey = NULL;
    LONG lRes = RegOpenKeyEx(hKeyParent, 
                             lpszKeyName, 
                             0, 
                             samDesired, 
                             &hKey);
    if (lRes == ERROR_SUCCESS)
    {
        lRes = Close();
        assert(lRes == ERROR_SUCCESS);
        m_hKey = hKey;
    }
    return lRes;
}

LONG RegistryKey::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
{
    DWORD dwType = NULL;
    DWORD dwCount = sizeof(DWORD);
    LONG lRes = RegQueryValueEx(m_hKey, 
        (LPTSTR)lpszValueName, 
                                NULL, 
                                &dwType,
                                (LPBYTE)&dwValue, 
                                &dwCount);
    assert((lRes!=ERROR_SUCCESS) || 
        (dwType == REG_DWORD));
    assert((lRes!=ERROR_SUCCESS) || 
        (dwCount == sizeof(DWORD)));
    return lRes;
}

LONG RegistryKey::QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount)
{
    assert(pdwCount != NULL);
    DWORD dwType = NULL;
    LONG lRes = RegQueryValueEx(m_hKey, 
        (LPTSTR)lpszValueName, 
                                NULL, 
                                &dwType,
                                (LPBYTE)szValue, 
                                pdwCount);
    assert((lRes!=ERROR_SUCCESS) || 
        (dwType == REG_SZ) ||
        (dwType == REG_MULTI_SZ) || 
        (dwType == REG_EXPAND_SZ));
    return lRes;
}

LONG RegistryKey::QueryValue(std::string& szValue, LPCTSTR lpszValueName)
{
    DWORD dwType = NULL;
    DWORD dwLen  = 80;
    char buffer[80];
    LONG lRes = RegQueryValueEx(m_hKey, 
                        (LPTSTR)lpszValueName, 
                        NULL, 
                        &dwType,
                        (LPBYTE)buffer, 
                        &dwLen);
    szValue = buffer;
    assert((lRes!=ERROR_SUCCESS) || 
        (dwType == REG_SZ) ||
        (dwType == REG_MULTI_SZ) || 
        (dwType == REG_EXPAND_SZ));
    return lRes;
}

LONG RegistryKey::QueryValue(LPBYTE lpValue, DWORD& len, LPCTSTR lpszValueName)
{
    DWORD dwType = NULL;
    LONG lRes = RegQueryValueEx(m_hKey, 
        (LPTSTR)lpszValueName, 
        NULL, 
        &dwType,
        lpValue, 
        &len);
    assert((lRes!=ERROR_SUCCESS) || 
        (dwType == REG_BINARY));
    return lRes;
}

LONG WINAPI RegistryKey::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    assert(lpszValue != NULL);
    RegistryKey key;
    LONG lRes = key.Create(hKeyParent, lpszKeyName);
    if (lRes == ERROR_SUCCESS)
        lRes = key.SetValue(lpszValue, lpszValueName);
    return lRes;
}

LONG RegistryKey::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    assert(lpszValue != NULL);
    RegistryKey key;
    LONG lRes = key.Create(m_hKey, lpszKeyName);
    if (lRes == ERROR_SUCCESS)
        lRes = key.SetValue(lpszValue, lpszValueName);
    return lRes;
}

LONG RegistryKey::SetValue(DWORD dwValue, LPCTSTR lpszValueName)
{
    assert(m_hKey != NULL);
    return RegSetValueEx(m_hKey, 
        lpszValueName, 
        NULL, 
        REG_DWORD,
        (LPBYTE)&dwValue, 
        sizeof(DWORD));
}

LONG RegistryKey::SetValue(LPBYTE lpValue, DWORD len, LPCTSTR lpszValueName)
{
    assert(m_hKey != NULL);
    return RegSetValueEx( m_hKey, 
        lpszValueName, 
        NULL, 
        REG_BINARY,
        lpValue, 
        len);
}

LONG RegistryKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    assert(lpszValue != NULL);
    assert(m_hKey != NULL);
    return RegSetValueEx( m_hKey, 
        lpszValueName, 
        NULL, 
        REG_SZ,
        (LPBYTE)lpszValue, 
        (lstrlen(lpszValue)+1)*sizeof(TCHAR));
}

LONG RegistryKey::SetValue(const std::string& aString, LPCTSTR lpszValueName)
{
    return RegSetValueEx( m_hKey, 
        lpszValueName, 
        NULL, 
        REG_SZ,
        (const unsigned char *)aString.c_str() , 
        (DWORD)aString.size());
}

//RecurseDeleteKey is necessary because on NT RegDeleteKey doesn't work if the
//specified key has subkeys
LONG RegistryKey::RecurseDeleteKey(LPCTSTR lpszKey)
{
    RegistryKey key;
    LONG lRes = key.Open(m_hKey, lpszKey);
    if (lRes != ERROR_SUCCESS)
        return lRes;
    FILETIME time;
    TCHAR szBuffer[256];
    DWORD dwSize = 256;
    while (RegEnumKeyEx(key.m_hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
        &time)==ERROR_SUCCESS)
    {
        lRes = key.RecurseDeleteKey(szBuffer);
        if (lRes != ERROR_SUCCESS)
            return lRes;
        dwSize = 256;
    }
    key.Close();
    return DeleteSubKey(lpszKey);
}

// new addition:

BOOL RegistryKey::getRegBoolValue(BOOL aValue, const TCHAR* aValName)
{
    DWORD dwValue;
    LONG result = QueryValue(dwValue, aValName);
    if (result != ERROR_SUCCESS)
    {
        SetValue(aValue ? 1 : 0, aValName);
    }
    return dwValue != 0;
}


DWORD RegistryKey::getRegDWordValue(DWORD aValue, const TCHAR* aValName)
{
    LONG result = QueryValue(aValue, aValName);
    if (result != ERROR_SUCCESS)
    {
        SetValue(aValue, aValName);
    }
    return aValue;
}


////////////////////////////////////////
//       getRegStringValue
/*! provides the string value  of a key
// \param const TCHAR* aValue : eventual new value
// \param const TCHAR* aValName : value to be queried
*/
std::string RegistryKey::getRegStringValue(const TCHAR* aValue, const TCHAR* aValName)
{
    DWORD size;
    TCHAR buffer[80];
    strcpy(buffer, aValue);
    size = 80;
    
    LONG result = QueryValue(buffer, aValName, &size);
    if (result != ERROR_SUCCESS)
    {
        SetValue(aValue, aValName);
    }
    return std::string(buffer);
}

void RegistryKey::setRegBoolValue(BOOL aValue, const TCHAR* aValName)
{
    SetValue(aValue ? 1 : 0, aValName);
}

void RegistryKey::setRegDWordValue(DWORD aValue, const TCHAR* aValName)
{
    SetValue(aValue, aValName);
}

void RegistryKey::setRegStringValue(const TCHAR* aValue, const TCHAR* aValName)
{
    SetValue(aValue, aValName);
}


