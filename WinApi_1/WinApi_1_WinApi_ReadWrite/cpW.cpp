#include <windows.h>
#include <tchar.h>

#define BUF_SIZE 256

int _tmain(int a_argC, wchar_t * a_argV[])
{
	#ifdef _TEST
	//DWORD _startTick=GetTickCount();
	LARGE_INTEGER _startHP;
	LARGE_INTEGER _endHP;
	QueryPerformanceCounter(&_startHP);
	#endif

	HANDLE _hIn, _hOut;
	DWORD _nIn,_nOut;
	char _rec[BUF_SIZE];
	if (a_argC!=3)
	{
		_tprintf(_T("Using: cpW file1 file2\n"));
		return 1;
	}
	_hIn=CreateFile(a_argV[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (_hIn==INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Unable to open input file. Error: %x\n"), GetLastError());
		return 2;
	}
	_hOut=CreateFile(a_argV[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (_hOut==INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Unable to open output file. Error: %x\n"), GetLastError());
		return 3;
	}

	while (ReadFile(_hIn,_rec,BUF_SIZE,&_nIn,NULL)&&_nIn)
	{
		WriteFile(_hOut,_rec,_nIn,&_nOut,NULL);
		if (_nIn!=_nOut)
		{
			_tprintf(_T("Error while writing to output file. Error: %x\n"), GetLastError());
			return 4;
		}
	}

	CloseHandle(_hIn);
	CloseHandle(_hOut);

	#ifdef _TEST
	//DWORD _endTick=GetTickCount();
	QueryPerformanceCounter(&_endHP);
	//_tprintf(_T("Ticks spent: %d.\n"),_endTick-_startTick);
	_tprintf(_T("HP Ticks spent: %d.\n"),_endHP.QuadPart-_startHP.QuadPart);
	#endif
	return 0;
}