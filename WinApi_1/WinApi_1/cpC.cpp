#include <stdio.h>
#include <tchar.h>

#define BUF_SIZE 256

#ifdef _TEST
#include <windows.h>
#endif

int _tmain(int a_argC, wchar_t * a_argV[])
{
	#ifdef _TEST
	//DWORD _startTick=GetTickCount();
	LARGE_INTEGER _startHP;
	LARGE_INTEGER _endHP;
	QueryPerformanceCounter(&_startHP);
	#endif
	FILE *_inFile, *_outFile;
	char _rec[BUF_SIZE];
	size_t _bytesIn,_bytesOut;
	if (a_argC!=3)
	{
		_tprintf(_T("Using: cpC file1 file2\n"));
		return 1;
	}
	_inFile=_tfopen(a_argV[1], _T("rb"));
	if (!_inFile)
	{
		_tperror(a_argV[1]);
		return 2;
	}
	_outFile=_tfopen(a_argV[2],_T("wt"));
	if (!_outFile)
	{
		_tperror(a_argV[2]);
		return 3;
	}

	while (_bytesIn=fread(_rec,sizeof(char),BUF_SIZE,_inFile))
	{
		_bytesOut=fwrite(_rec,sizeof(char),_bytesIn,_outFile);
		if (_bytesIn!=_bytesOut)
		{
			_tperror(_T("Error while copying file"));
			return 4;
		}
	}

	fclose(_inFile);
	fclose(_outFile);

	#ifdef _TEST
	//DWORD _endTick=GetTickCount();
	QueryPerformanceCounter(&_endHP);
	//_tprintf(_T("Ticks spent: %d.\n"),_endTick-_startTick);
	_tprintf(_T("HP Ticks spent: %d.\n"),_endHP.QuadPart-_startHP.QuadPart);
	#endif
	return 0;
}