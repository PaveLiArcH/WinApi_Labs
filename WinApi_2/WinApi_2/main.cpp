#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>
#include "PrintMsg.h"

const int c_MaxChar=5;
const int c_PasswMaxChar=10;

int _tmain(int argC, wchar_t *argV[])
{
	wchar_t _buf[c_MaxChar];
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsolePrompt(_T("Enter some text and press Enter: "), _buf, c_MaxChar, true);
	PrintMsg(hOut, _T("Enter was pressed\n"));
	PrintStrings(hOut, _T("Entered text: "), _buf, _T("\n"));
	wchar_t _passwBuf[c_PasswMaxChar];
	ConsolePrompt(_T("Enter secret password: "), _passwBuf, c_PasswMaxChar, false);
	PrintMsg(hOut, _T("\nPassword was entered\n"));
	PrintStrings(hOut, _T("Your secret password: "), _passwBuf, _T("\n"), _T("Never give your pass to other people\n"));
}