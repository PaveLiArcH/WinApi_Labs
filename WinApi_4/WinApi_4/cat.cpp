#include <tchar.h>
#include <windows.h>

#include "..\..\WinApi_2\WinApi_2\PrintMsg.h"
#include "..\..\WinApi_3\WinApi_3\ReportError.h"

#include "..\..\FilesCPP\Options.h"

#define BUF_SIZE 256

VOID CatFile(HANDLE hInFfile, HANDLE hOutFile)
{
	DWORD _nIn,_nOut;
	TCHAR _buf[BUF_SIZE];
	while (ReadFile(hInFfile, _buf, BUF_SIZE, &_nIn, NULL) && _nIn)
	{
		if (!WriteConsole(hOutFile, _buf, _nIn, &_nOut, NULL) && !WriteFile(hOutFile, _buf, _nIn, &_nOut, NULL))
		{
			_tprintf(_T("Error while writing to output. Error: %x\n"), GetLastError());
			exit(3);
		}
		if (_nIn!=_nOut)
		{
			_tprintf(_T("Error while writing to output. Error: %x\n"), GetLastError());
			exit(4);
		}
	}
}

int _tmain(int argC, LPCTSTR argV[])
{
	BOOL _skip=FALSE;
	int _firstName=Options(argC, argV, _T("-s"), &_skip);

	HANDLE _hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);

	if (_firstName<argC)
	{
		for (int i=0; i<_firstName; i++)
		{
			HANDLE _hIn=CreateFile(argV[_firstName+i], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (_hIn==INVALID_HANDLE_VALUE)
			{
				if (_skip)
				{
					continue;
				}
				_tprintf(_T("Unable to open input file. Error: %x\n"), GetLastError());
				return 2;
			}
			CatFile(_hIn, _hStdOut);
			CloseHandle(_hIn);
		}
	} else
	{

	}
}