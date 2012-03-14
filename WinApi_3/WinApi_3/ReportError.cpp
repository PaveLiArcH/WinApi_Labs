#include <windows.h>
#include <tchar.h>
#include "..\..\WinApi_2\WinApi_2\PrintMsg.h"
#include "ReportError.h"

VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg)
{
	DWORD eMsgLen, LastErr=GetLastError();
	LPTSTR lpvSysMsg;
	HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
	
	PrintMsg(hStdErr, UserMessage);
	if (PrintErrorMsg)
	{
		eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL, LastErr, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpvSysMsg, 0, NULL);
		PrintStrings(hStdErr, _T("\n"), lpvSysMsg, _T("\n"), NULL);
		HeapFree(GetProcessHeap(), 0, lpvSysMsg);
	}
	if (ExitCode>0)
	{
		ExitProcess(ExitCode);
	} else return;
}