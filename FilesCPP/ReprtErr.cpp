/* Listing 2.2. �㭪�� ReportError ��� ᮮ�饭�� �� �訡���
                     ��⥬��� �㭪権  */
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
  /* �᢮������� ���� �����, ᮤ�p��騩 ᮮ�饭�� �� �訡�� */
     HeapFree (GetProcessHeap (), 0, lpvSysMsg); // �. ��. 6
  }
  if (ExitCode>0)
     ExitProcess (ExitCode);
  else
     return;
}
