#include <windows.h>
#include <tchar.h>
#include <conio.h>

//#define _PART_1
//#define _PART_2
//#define _PART_3
//#define _PART_4
#define _PART_5_6_7
//#define _PART_6
//#define _PART_7

int _tmain(int argC, LPCTSTR argV[])
{
	#ifdef _PART_2
	HANDLE _handleInvalid=CreateFile(_T("..\\Existant.File"), GENERIC_READ, 0, NULL, CREATE_ALWAYS, NULL, NULL);
	if (_handleInvalid!=INVALID_HANDLE_VALUE)
	{
		while (!kbhit())
		{
		}
	}
	CloseHandle (_handleInvalid);
	#endif
	#ifdef _PART_5_6_7
	HANDLE _handleWrite=CreateFile(_T("..\\Write.File"), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
	if (_handleWrite!=INVALID_HANDLE_VALUE)
	{
		while (!kbhit())
		{
		}
	}
	CloseHandle (_handleWrite);
	#endif
}