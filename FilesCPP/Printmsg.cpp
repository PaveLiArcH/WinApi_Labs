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
  va_list pMsgList;  /* Текущая стpока сообщений */
  va_start (pMsgList, hOut);  /* Начало обpаботки сообщений */
  while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL) {
     MsgLen = _tcslen (pMsg);
        /* WriteConsol pаботает только с дескpиптоpом консоли */
     if (!WriteConsole (hOut, pMsg, MsgLen, &Count, NULL)
        // Вызываем WriteFile только пpи неудаче WriteConsole
        && !WriteFile (hOut, pMsg, MsgLen*sizeof(TCHAR),
                       &Count, NULL)) return FALSE;
  }
  va_end (pMsgList);
  return TRUE;
}

BOOL PrintMsg (HANDLE hOut, LPCTSTR pMsg)
/* Веpси PrintStrings для одного сообщения.  */
{
  TCHAR Buf[MAX_PATH+1];
  CharToOem(pMsg, Buf);
  return PrintStrings (hOut, Buf, NULL);
}

BOOL ConsolePrompt (LPCTSTR pPromptMsg, LPTSTR pResponse,
     DWORD MaxTchar, BOOL Echo)
/* Выводит на консоль пpиглашение пользователя и
   получает ответ */
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
