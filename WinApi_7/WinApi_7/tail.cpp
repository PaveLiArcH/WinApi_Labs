#include <Windows.h>
#include <tchar.h>
#include "..\..\FilesCPP\EvryThng.h"
#include "CyclicBuf.h"
#include <clocale>

#define BUF_SIZE 256

void printUsage()
{
	_tprintf(_T("Usage: tail file.ext\n"));
}

void fastMethod(HANDLE hFile)
{
	LARGE_INTEGER _size;
	if (GetFileSizeEx(hFile, &_size)==TRUE)
	{
		LARGE_INTEGER _startPos;
		_startPos.QuadPart=-(11<<8);
		_startPos.QuadPart+=_size.QuadPart;
		if (_startPos.QuadPart>=0)
		{
			SetFilePointerEx(hFile, _startPos, NULL, FILE_BEGIN);
		} else
		{
			_startPos.QuadPart=0;
			SetFilePointerEx(hFile, _startPos, NULL, FILE_BEGIN);
		}
		char Buf[BUF_SIZE];
		DWORD bufSize=BUF_SIZE, nIn=0;
		BOOL lfFound=FALSE;
		CyclicBuf<LONGLONG> _cyclicBuf(11);
		LARGE_INTEGER _currPos=_startPos;
		_startPos.QuadPart=0;
		_cyclicBuf.cm_Add(_startPos.QuadPart);
		while (ReadFile(hFile, Buf, bufSize, &nIn, NULL) && nIn)
		{
			for(DWORD i=0; i<nIn; i++)
			{
				if (lfFound==TRUE)
				{
					_cyclicBuf.cm_Add(_currPos.QuadPart+i);
				}
				lfFound=Buf[i]=='\n';
			}
			
			if (!SetFilePointerEx(hFile, _startPos, &_currPos, FILE_CURRENT))
			{
				ReportError(_T("Ошибка при получении позиции файла: "), 3, TRUE);
			}
		}
		unsigned int _fill=_cyclicBuf.cm_GetFill();
		if (_fill>0)
		{
			_currPos.QuadPart=_cyclicBuf[0];
			SetFilePointerEx(hFile, _currPos, NULL, FILE_BEGIN);
			while (ReadFile(hFile, Buf, bufSize, &nIn, NULL) && nIn)
			{
				for(DWORD i=0; i<nIn; i++)
				{
					printf("%c", Buf[i]);
				}
			}
		} else
		{
			ReportError(_T("Вероятно файл не содержит знаков перевода строки"), 4, FALSE);
		}
	} else
	{
		ReportError(_T("Ошибка при получении размера файла: "), 2, TRUE);
	}
}

void stableMethod(HANDLE hFile);

int _tmain(int argC, LPCTSTR *argV)
{
	setlocale(LC_ALL, "");
	if (argC!=2)
	{
		printUsage();
	} else
	{
		HANDLE hFile=CreateFile(argV[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hFile!=INVALID_HANDLE_VALUE)
		{
			fastMethod(hFile);
		} else
		{
			ReportError(_T("Не удалось открыть файл: "), 1, TRUE);
		}
	}
}