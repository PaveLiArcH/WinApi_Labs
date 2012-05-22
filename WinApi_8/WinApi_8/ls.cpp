#include <tchar.h>
#include <windows.h>
#include "..\..\FilesCPP\EvryThng.h"

TCHAR currPath[MAX_PATH_LONG+1];

DWORD FileType(LPWIN32_FIND_DATA pFileData)
{
	DWORD _retType;
	_retType=TYPE_FILE;
	if (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		_retType=(!lstrcmp(pFileData->cFileName, _T("."))||
			!lstrcmp(pFileData->cFileName, _T("..")))? TYPE_DOT: TYPE_DIR;
	}
	return _retType;
}

BOOL ProcessItem(LPWIN32_FIND_DATA pFileData, DWORD NumFlags, LPBOOL Flags)
{
	const TCHAR _fileTypeChar[]={' ', 'd', 'p'};
	DWORD _type=FileType(pFileData);
	BOOL _long=Flags[0];
	SYSTEMTIME _lastWrite;
	_tprintf(_T("\n"));
	if (_long)
	{
		_tprintf(_T("%c"), _fileTypeChar[_type-1]);
		_tprintf(_T("%10d "), pFileData->nFileSizeLow);
		FileTimeToSystemTime(&(pFileData->ftLastWriteTime), &_lastWrite);
		_tprintf(_T("%02d/%02d/%04d %02d:%02d:%02d "),
			_lastWrite.wMonth, _lastWrite.wDay,
			_lastWrite.wYear, _lastWrite.wHour,
			_lastWrite.wMinute, _lastWrite.wSecond);
	}
	_tprintf(_T("%s"), pFileData->cFileName);
	return TRUE;
}

BOOL TraverseDirectory(LPTSTR PathName, DWORD NumFlags, LPBOOL Flags)
{
	HANDLE SearchHandle;
	WIN32_FIND_DATA FindData;
	BOOL Recursive = Flags[1];
	DWORD FType, iPass;
	TCHAR CurrPath [MAX_PATH + 1];

	GetCurrentDirectory (MAX_PATH, CurrPath);

	for (iPass = 1; iPass <= 2; iPass++)
	{
		if (_istalpha(PathName[0]) &&  (PathName[1] == ':') && (_tcslen(PathName) <= 3))
		{
			TCHAR   TempPath[5] = {'\0', '\0' };;
			TempPath[0] = PathName[0];
			_tcscat (TempPath, _T(":\\*"));
			SearchHandle = FindFirstFile(TempPath, &FindData);
		}
		else
			SearchHandle = FindFirstFile(PathName, &FindData);

		SearchHandle = FindFirstFile (PathName, &FindData);
		if (SearchHandle == INVALID_HANDLE_VALUE)
		{
			ReportError (_T("Error opening Search Handle."), 0, TRUE);
			return FALSE;
		}

		do
		{
			FType = FileType (&FindData);
			if (iPass == 1)
			{
				ProcessItem (&FindData, MAX_OPTIONS, Flags);
			}

			if (FType == TYPE_DIR && iPass == 2 && Recursive) {
				_tprintf (_T ("\n%s\\%s:"), CurrPath, FindData.cFileName);
				SetCurrentDirectory (FindData.cFileName);
				TraverseDirectory (_T ("*"), NumFlags, Flags);
				SetCurrentDirectory (_T (".."));
			}
		} while (FindNextFile (SearchHandle, &FindData));

		FindClose (SearchHandle);
	}
	return TRUE;
}

int _tmain(int argc, LPCTSTR argv[])
{
	BOOL flags[MAX_OPTIONS], ok = TRUE;
	TCHAR PathName [MAX_PATH + 1], CurrPath [MAX_PATH + 1], TempPath [MAX_PATH + 1];
	LPTSTR pSlash, pFileName;
	int i, fileIndex;
	DWORD pathLength;

	fileIndex = Options(argc, argv, _T("LR"), &flags[0], &flags[1], NULL);

	pathLength = GetCurrentDirectory(MAX_PATH_LONG, currPath); 
	if (pathLength == 0 || pathLength >= MAX_PATH_LONG)
	{
		ReportError(_T("GetCurrentDirectory failed"), 1, TRUE);
	}
	
	if (argc < fileIndex + 1)
	{
		ok = TraverseDirectory(_T("*"), MAX_OPTIONS, flags);
	}
	else
	{
		for (i = fileIndex; i < argc; i++)
		{
			_tcscpy (PathName, argv [i]);

			pSlash = _tcsrchr (PathName, '\\'); 
			pSlash = _tcsrchr (TempPath, '\\');

			if (pSlash != NULL)
			{
				*pSlash = '\0';
				_tcscat(TempPath, _T("\\"));         
				SetCurrentDirectory (TempPath);
				pSlash = _tcsrchr (PathName, '\\');  
				pFileName = pSlash + 1;
			} else pFileName = PathName;
			ok = TraverseDirectory (pFileName, MAX_OPTIONS, flags) && ok;
			SetCurrentDirectory (CurrPath);
		}
	}
	_tprintf(_T("\n"));
	return ok ? 0 : 1;
}