#pragma once
#include <windows.h>

BOOL PrintStrings(HANDLE hOut, ...);

BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg);

BOOL ConsolePrompt(LPCTSTR pPromptMsg, LPTSTR pResponse, DWORD MaxTchar, BOOL Echo);