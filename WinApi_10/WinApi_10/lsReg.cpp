#include <tchar.h>
#include <windows.h>
#include "..\..\FilesCPP\EvryThng.h"

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

bool TraverseReg(HKEY a_key, DWORD a_numFlags, LPBOOL a_flags, int a_level = 0)
{
	BOOL Recursive = a_flags[0];
	BOOL List = a_flags[1];

	DWORD _numSubKeys, _maxSubKeyLen, _numValues, _maxValueNameLen, _maxValueLen;
	RegQueryInfoKey(a_key, NULL, NULL, NULL, &_numSubKeys, &_maxSubKeyLen, NULL, &_numValues, &_maxValueNameLen, &_maxValueLen, NULL, NULL);
	DWORD _maxPathLen = max(_maxSubKeyLen, _maxValueNameLen)+1;
	LPTSTR _keyPath = new TCHAR[_maxPathLen+1];

	if (List)
	{
		LPBYTE _data=new BYTE[_maxValueLen];
		for(DWORD i=0; i<_numValues; i++)
		{
			DWORD _pathLen = _maxPathLen;
			DWORD _dataLen = _maxValueLen;
			DWORD _type;
			LONG _res = RegEnumValue(a_key, i, _keyPath, &_pathLen, NULL, &_type, _data, &_dataLen);

			for (int j=0; j<a_level; j++, _tprintf(_T("\t")));

			ProcessItem(_type, _keyPath, _data, _dataLen);
		}
		delete []_data;
	}

	for (DWORD i=0; i<_numSubKeys; i++)
	{
		DWORD _pathLen = _maxPathLen;
		LONG _res = RegEnumKeyEx(a_key, i, _keyPath, &_pathLen, NULL, NULL, NULL, NULL);

		for (int j = 0; j<a_level; j++, _tprintf(_T("\t")));

		_tprintf(_T("%s\n"), _keyPath);
		
		if (Recursive)
		{
			HKEY _subKey;
			if (RegOpenKeyEx(a_key, _keyPath, 0, KEY_ALL_ACCESS, &_subKey)!=ERROR_SUCCESS)
			{
				ReportError(_T("Error while opening registry key"), 0, TRUE);
				delete []_keyPath;
				return false;
			} else
			{
				TraverseReg(_subKey, a_numFlags, a_flags, a_level+1);
			}
		}
	}
	return true;
}

int _tmain(int argc, LPCTSTR argv[])
{
	BOOL flags[MAX_OPTIONS], ok = FALSE;
	int _regKeyIndex=0;

	_regKeyIndex = Options(argc, argv, _T("RL"), &flags[0], &flags[1], NULL);
	
	if (_regKeyIndex < argc)
	{
		HKEY _hkCU=NULL;
		if(RegOpenKeyEx(HKEY_CURRENT_USER, argv[_regKeyIndex], 0, KEY_ALL_ACCESS, &_hkCU)!=ERROR_SUCCESS)
		{
			ReportError(_T("Error while opening registry key"), 3, TRUE);
		} else
		{
			ok = TraverseReg(_hkCU, MAX_OPTIONS, flags);
			RegCloseKey(_hkCU);
		}
	} else
	{
		_tprintf(_T("Usage: lsReg [-R] [-L] target (in HKCU)\n"));
		return 1;
	}
	_tprintf(_T("\n"));
	return ok ? 0 : 2;
}