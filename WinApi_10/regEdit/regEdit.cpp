#include <tchar.h>
#include <windows.h>
#include "..\..\FilesCPP\EvryThng.h"

#define MAX_KEY_LENGTH 255

void ProcessItem(DWORD a_type, LPCTSTR a_path, LPBYTE a_data, DWORD a_dataLen)
{
	switch (a_type)
	{
	case REG_BINARY:
		_tprintf(_T("REG_BINARY %s = "), a_path);
		for (DWORD i = 0; i<a_dataLen; i++)
		{
			_tprintf(_T("%2x "), a_data[i]);
		}
		_tprintf(_T("\n"));
		break;
	case REG_DWORD_LITTLE_ENDIAN:
	case REG_DWORD_BIG_ENDIAN:
		_tprintf(_T("REG_DWORD %s = %d\n"), a_path, *((LPDWORD)a_data));
		break;
	case REG_SZ:
		_tprintf(_T("REG_SZ %s = %s\n"), a_path, a_data);
		break;
	default:
		_tprintf(_T("%d %s = %s\n"), a_type, a_path, a_data);
	}
}

int _tmain(int argc, LPCTSTR argv[])
{
	if (argc<3)
	{
		_tprintf(_T("Usage: regEdit path subKey [value]\n"));
		return 1;
	}
	LPTSTR _key=const_cast<LPTSTR>(argv[1]);
	LPTSTR _path=_key+5;
	LPCTSTR _subKey=argv[2];

	_key[4] = '\0';
	HKEY _hKey;
	if (!_tcscmp(_key, _T("HKCR")))
	{
		_hKey=HKEY_CLASSES_ROOT;
	} else
	{
		if (!_tcscmp(_key, _T("HKCU")))
		{
			_hKey=HKEY_CURRENT_USER;
		} else
		{
			if (!_tcscmp(_key, _T("HKLM")))
			{
				_hKey=HKEY_LOCAL_MACHINE;
			} else
			{
				if (!_tcscmp(_key, _T("HKUR")))
				{
					_hKey=HKEY_USERS;
				} else
				{
					if (!_tcscmp(_key, _T("HKCC")))
					{
						_hKey = HKEY_CURRENT_CONFIG;
					}
				}
			}
		}
	}
	DWORD _type, _dataLen=MAX_KEY_LENGTH*sizeof(TCHAR);
	LPTSTR _data = new TCHAR[_dataLen];

	if (RegGetValue(_hKey, _path, _subKey, RRF_RT_ANY, &_type, _data, &_dataLen)!=ERROR_SUCCESS)
	{
		ReportError(_T("Failed to get value\n"), 2, TRUE);
	}
	
	_tprintf(_T("Old value:\n"));
	ProcessItem(_type, _path, (LPBYTE)_data, _dataLen);
	_dataLen/=sizeof(TCHAR);

	if (argc>3)
	{
		_data=const_cast<LPTSTR>(argv[3]);
	} else
	{
		_tprintf(_T("Enter new value: "));
		_tscanf(_T("%s"), _data);
	}

	DWORD _dword;
	switch (_type)
	{
	case REG_DWORD:
		_dword=_ttoi(_data);
		if (RegSetKeyValue(_hKey, _path, _subKey, _type, &_dword, 4)!=ERROR_SUCCESS)
		{
			delete []_data;
			ReportError(_T("Error while setting value "), 2, TRUE);
		}
		break;
	case REG_SZ:
		_dataLen=_tcslen(_data);
		if (RegSetKeyValue(_hKey, _path, _subKey, _type, _data, _dataLen*sizeof(TCHAR))!=ERROR_SUCCESS)
		{
			delete []_data;
			ReportError(_T("Error while setting string value "), 3, TRUE);
		}
		break;
	default:
		_tprintf(_T("Can't set value of this type"));
		break;
	}
	delete []_data;
	return 0;
}
