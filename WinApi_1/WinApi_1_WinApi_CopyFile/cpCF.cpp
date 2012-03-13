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

	if (a_argC!=3)
	{
		_tprintf(_T("Using: cpCF file1 file2\n"));
		return 1;
	}
	if (!CopyFile(a_argV[1],a_argV[2],FALSE))
	{
		_tprintf(_T("Error while writing to output file. Error: %x\n"), GetLastError());
		return 4;
	}

	#ifdef _TEST
	//DWORD _endTick=GetTickCount();
	QueryPerformanceCounter(&_endHP);
	//_tprintf(_T("Ticks spent: %d.\n"),_endTick-_startTick);
	_tprintf(_T("HP Ticks spent: %d.\n"),_endHP.QuadPart-_startHP.QuadPart);
	#endif
	return 0;
}