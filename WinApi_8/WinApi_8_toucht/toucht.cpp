#include <tchar.h>
#include <windows.h>
#include "..\..\FilesCPP\EvryThng.h"

int _tmain (int argc, LPCTSTR argv[])
{
	FILETIME newFileTime;
	LPFILETIME pAccessTime = NULL, pModifyTime = NULL;
	HANDLE hFile;
	BOOL setAccessTime, setModTime, notCreateNew, maFlag;
	DWORD CreateFlag;
	int i, FileIndex;
	
	if (argc < 2)
	{
		_tprintf(_T("Usage: touch [-a] [-m] [-c] files"));
		return 1;
	}
	FileIndex = Options(argc, argv, _T ("amc"), &setAccessTime, &setModTime, &notCreateNew, NULL);

	maFlag = setAccessTime || setModTime;
	CreateFlag = notCreateNew ? OPEN_EXISTING : OPEN_ALWAYS;

	for (i = FileIndex; i < argc; i++)
	{
		hFile = CreateFile(argv[i], GENERIC_READ | GENERIC_WRITE, 0, NULL,
				CreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			if (!notCreateNew) ReportError (_T ("touch error: Cannot open file."), 0, TRUE);
			continue;
		}
		GetSystemTimeAsFileTime(&newFileTime);
		if (setAccessTime || !maFlag) pAccessTime = &newFileTime;
		if (setModTime || !maFlag) pModifyTime = &newFileTime;
		if (!SetFileTime(hFile, NULL, pAccessTime, pModifyTime))
		{
			ReportError(_T ("Failure setting file times."), 2, TRUE);
		} else
		{
			_tprintf(_T("Modify time successfully changed for file %s\n"), argv[i]);
		}
		CloseHandle(hFile);
	}
	return 0;
}
