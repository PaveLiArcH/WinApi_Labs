#include <Windows.h>
#include <tchar.h>
#include "..\..\FilesCPP\EvryThng.h"
#include <clocale>

#define BUF_SIZE 256

void printUsage()
{
	_tprintf(_T("Usage: getn file.ext [line [count]]\n"));
}

int _tmain(int argC, LPCTSTR *argV)
{
	setlocale(LC_ALL, "");
	if (argC<2)
	{
		printUsage();
	} else
	{
		long _line, _count;
		bool _lineSet=false, _countSet=false;
		if (argC>=3)
		{
			_line=_tstol(argV[2]);
			_lineSet=_line>0;
		}
		if (argC>=4)
		{
			_count=_tstol(argV[3]);
			_countSet=_count>0;
		}
		HANDLE hFile=CreateFile(argV[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hFile!=INVALID_HANDLE_VALUE)
		{
			char Buf[BUF_SIZE];
			DWORD bufSize=BUF_SIZE, nIn=0;
			BOOL lfFound=TRUE;
			while (ReadFile(hFile, Buf, bufSize, &nIn, NULL) && nIn)
			{
				for(DWORD i=0; i<nIn; i++)
				{
					if (lfFound==TRUE)
					{
						if (_lineSet)
						{
							_line--;
							_lineSet=_line>0;
						} else
						{
							if (_countSet)
							{
								_count--;
								_countSet=_count>0;
								if (!_countSet)
								{
									return -1;
								}
							}
						}
					}
					lfFound=Buf[i]=='\n';
					if (!_lineSet)
					{
						printf("%c", Buf[i]);
					}
				}
			}
		} else
		{
			ReportError(_T("Не удалось открыть файл: "), 1, TRUE);
		}
	}
}