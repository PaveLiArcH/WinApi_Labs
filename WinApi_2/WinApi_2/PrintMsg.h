#pragma once
#include <windows.h>

BOOL PrintStrings(HANDLE hOut, ...);

BOOL PrintMsg(HANDLE hOut, const wchar_t *pMsg);

BOOL ConsolePrompt(const wchar_t *pPromptMsg, wchar_t *pResponse, DWORD MaxTchar, BOOL Echo);