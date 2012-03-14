#include <windows.h>
#include <tchar.h>
#include "ReportError.h"

#include <conio.h>
#include <stdio.h>

#define _REPORT_ERROR

#define _PART_1
//#define _PART_2
//#define _PART_3
//#define _PART_4
//#define _PART_5
//#define _PART_6
#define _PART_7

#ifndef _REPORT_ERROR
#include <io.h>
#endif

int _tmain(int argC, LPCTSTR argV[])
{
	#ifdef _PART_1
		#ifdef _REPORT_ERROR
		HANDLE _handleInvalid=CreateFile(_T("NonExistant.File"), GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleInvalid==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл NonExistant.File"), -1, TRUE);
		}
		CloseHandle(_handleInvalid);
		#else
		FILE *_fileInvalid=_tfopen(_T("NonExistant.File"), _T("rb"));
		if (_fileInvalid == NULL)
		{
			_tperror(_T("Can't open file NonExistant.File"));
		}
		#endif
	#endif

	#ifdef _PART_2
		#ifdef _REPORT_ERROR
		HANDLE _handleOpened=CreateFile(_T("..\\Existant.File"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleOpened==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл Existant.File"), -1, TRUE);
		}
		#else
		FILE *_fileOpened=_tfopen(_T("..\\Existant.File"), _T("wb"));
		if (_fileOpened == NULL)
		{
			_tperror(_T("Can't open file Existant.File"));
		}
		#endif
	#endif

	#ifdef _PART_3
		#ifdef _REPORT_ERROR
		HANDLE _handleReadonly=CreateFile(_T("..\\ReadOnly.File"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleReadonly==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл ReadOnly.File"), -1, TRUE);
		}
		#else
		FILE *_fileReadonly=_tfopen(_T("..\\ReadOnly.File"), _T("wb"));
		if (_fileReadonly == NULL)
		{
			_tperror(_T("Can't open file ReadOnly.File"));
		}
		#endif
	#endif

	#ifdef _PART_4
		#ifdef _REPORT_ERROR
		HANDLE _handleWriteReadonly=CreateFile(_T("..\\WriteReadOnly.File"), GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleWriteReadonly==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл WriteReadOnly.File"), -1, TRUE);
		}
		TCHAR _testString[]=_T("Test string");
		DWORD _written=0;
		if (!WriteFile(_handleWriteReadonly, _testString, sizeof(_testString), &_written, NULL))
		{
			ReportError(_T("Не удалось записать в файл WriteReadOnly.File"), -1, TRUE);
		}
		#else
		FILE *_fileWriteReadonly=_tfopen(_T("..\\WriteReadOnly.File"), _T("rb"));
		if (_fileWriteReadonly == NULL)
		{
			_tperror(_T("Can't open file WriteReadOnly.File"));
		} else
		if (_fputts(_T("Test string"), _fileWriteReadonly)<=0)
		{
			_tperror(_T("Can't write to file WriteReadOnly.File"));
		}
		#endif
	#endif

	#ifdef _PART_5
		#ifdef _REPORT_ERROR
		HANDLE _handleWriteOpened=CreateFile(_T("..\\Write.File"), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleWriteOpened==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл Write.File"), -1, TRUE);
		}

		_tprintf(_T("Open file in another program\n"));
		while (!kbhit())
		{
		}

		TCHAR _testString[]=_T("Test string");
		DWORD _written=0;
		if (!WriteFile(_handleWriteOpened, _testString, sizeof(_testString), &_written, NULL))
		{
			ReportError(_T("Не удалось записать в файл Write.File"), -1, TRUE);
		}
		CloseHandle(_handleWriteOpened);
		#else
		FILE *_fileWriteOpened=_tfopen(_T("..\\Write.File"), _T("wb"));
		if (_fileWriteOpened == NULL)
		{
			_tperror(_T("Can't open file Write.File"));
		} else
		{
			_tprintf(_T("Open file in another program\n"));
			while (!kbhit())
			{
			}

			if (_fputts(_T("Test string"), _fileWriteOpened)<=0)
			{
				_tperror(_T("Can't write to file Write.File"));
			}
		}
		#endif
	#endif

	#ifdef _PART_6
		#ifdef _REPORT_ERROR
		HANDLE _handleReadOpened=CreateFile(_T("..\\Write.File"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleReadOpened==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл Write.File"), -1, TRUE);
		}

		_tprintf(_T("Open file in another program\n"));
		while (!kbhit())
		{
		}

		TCHAR _testString[50];
		DWORD _readed=0;
		if (!ReadFile(_handleReadOpened, _testString, sizeof(_testString), &_readed, NULL))
		{
			ReportError(_T("Не удалось считать из файла Write.File"), -1, TRUE);
		}
		CloseHandle(_handleReadOpened);
		#else
		FILE *_fileReadOpened=_tfopen(_T("..\\Write.File"), _T("rb"));
		if (_fileReadOpened == NULL)
		{
			_tperror(_T("Can't open file Write.File"));
		} else
		{
			_tprintf(_T("Open file in another program\n"));
			while (!kbhit())
			{
			}

			if (_fputts(_T("Test string"), _fileReadOpened)<=0)
			{
				_tperror(_T("Can't read from file Write.File"));
			}
		}
		#endif
	#endif

	#ifdef _PART_7
		#ifdef _REPORT_ERROR
		HANDLE _handleOpened=CreateFile(_T("..\\Write.File"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		if (_handleOpened==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("Не удалось открыть файл Write.File"), -1, TRUE);
		}

		_tprintf(_T("Open file in another program\n"));
		while (!kbhit())
		{
		}

		CloseHandle(_handleOpened);
		#else
		FILE *_fileOpened=_tfopen(_T("..\\Write.File"), _T("rb"));
		if (_fileOpened == NULL)
		{
			_tperror(_T("Can't open file Write.File"));
		} else
		{
			_tprintf(_T("Open file in another program\n"));
			while (!kbhit())
			{
			}

			fclose(_fileOpened);
		}
		#endif
	#endif
}