//#include "Envirmnt.h"
//#undef UNICODE
//#undef _UNICODE

#include "EvryThng.h"
/* PrintMsg.c : ConsolPrompt, PrintStrings, PrintMsg */

#include <stdarg.h>

BOOL PrintStrings (HANDLE hOut, ...)
{
  DWORD MsgLen, Count;
  LPCTSTR pMsg;
  va_list pMsgList;  /* ������ ��p��� ᮮ�饭�� */
  va_start (pMsgList, hOut);  /* ��砫� ��p���⪨ ᮮ�饭�� */
  while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL) {
     MsgLen = _tcslen (pMsg);
        /* WriteConsol p���⠥� ⮫쪮 � ���p���p�� ���᮫� */
     if (!WriteConsole (hOut, pMsg, MsgLen, &Count, NULL)
        // ��뢠�� WriteFile ⮫쪮 �p� ��㤠� WriteConsole
        && !WriteFile (hOut, pMsg, MsgLen*sizeof(TCHAR),
                       &Count, NULL)) return FALSE;
  }
  va_end (pMsgList);
  return TRUE;
}

BOOL PrintMsg (HANDLE hOut, LPCTSTR pMsg)
/* ��p� PrintStrings ��� ������ ᮮ�饭��.  */
{
  TCHAR Buf[MAX_PATH+1];
  CharToOem(pMsg, Buf);
  return PrintStrings (hOut, Buf, NULL);
}

BOOL ConsolePrompt (LPCTSTR pPromptMsg, LPTSTR pResponse,
     DWORD MaxTchar, BOOL Echo)
/* �뢮��� �� ���᮫� �p����襭�� ���짮��⥫� �
   ����砥� �⢥� */
{
   HANDLE hStdIn, hStdOut;
   DWORD TcharIn, EchoFlag;
   BOOL Success;
   hStdIn = CreateFile ( _T ("CONIN$"),
        GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   hStdOut = CreateFile (_T ("CONOUT$"), GENERIC_WRITE, 0,
        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   EchoFlag = Echo ? ENABLE_ECHO_INPUT : 0;
   Success =
      SetConsoleMode (hStdIn, ENABLE_LINE_INPUT |
        EchoFlag | ENABLE_PROCESSED_INPUT)
        && SetConsoleMode ( hStdOut,
        ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_PROCESSED_OUTPUT)
        && PrintStrings (hStdOut, pPromptMsg, NULL)
        && ReadConsole (hStdIn, pResponse,
        MaxTchar, &TcharIn, NULL);
   if (Success) pResponse [TcharIn - 2] = '\0';
   CloseHandle (hStdIn);
   CloseHandle (hStdOut);
   return Success;
}
