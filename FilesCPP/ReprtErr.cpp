/* Listing 2.2. Функция ReportError для сообщения об ошибках
                     системных функций  */
#include "EvryThng.h"
// #include <stdlib.h>

VOID ReportError (LPCTSTR UserMessage, DWORD ExitCode,
                  BOOL PrintErrorMsg)
{
  DWORD eMsgLen, LastErr = GetLastError ();
  LPTSTR lpvSysMsg;
  TCHAR Buf[MAX_PATH];
//  LPTSTR WBuf; 

  HANDLE hStdErr = GetStdHandle (STD_ERROR_HANDLE);
  PrintMsg (hStdErr, UserMessage);
  if (PrintErrorMsg) {
     eMsgLen = FormatMessage
        (FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM, NULL, LastErr,
        MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
//        MAKELANGID (LANG_RUSSIAN, SUBLANG_NEUTRAL),
        (LPTSTR) &lpvSysMsg, 0, NULL);
     //CharToOem(lpvSysMsg, lpvSysMsg);
     CharToOem(lpvSysMsg, (char *)&Buf[0]);
//     WBuf = (LPTSTR)malloc(256);
//	   CharToOem(lpvSysMsg, WBuf);
//     PrintMsg (hStdErr, WBuf);
//     PrintStrings (hStdErr, _T ("\n"), lpvSysMsg,
     PrintStrings (hStdErr, _T ("\n"), Buf,
        _T ("\n"), NULL);
  /* Освобождаем блок памяти, содеpжащий сообщение об ошибке */
     HeapFree (GetProcessHeap (), 0, lpvSysMsg); // см. гл. 6
  }
  if (ExitCode>0)
     ExitProcess (ExitCode);
  else
     return;
}
