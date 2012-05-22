//#include "Options.h"
#include "EvryThng.h"
#include <stdarg.h>

DWORD Options (int argc, LPCTSTR argv [], LPCTSTR OptStr, ...)
{
	va_list pFlagList;
	LPBOOL pFlag;
	int iFlag = 0, iArg;

	va_start (pFlagList, OptStr);
	while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL
				&& iFlag < (int)_tcslen (OptStr)) {
		*pFlag = FALSE;
		for (iArg = 1; !(*pFlag) && iArg < argc && argv [iArg] [0] == '-'; iArg++)
			*pFlag = _memtchr (argv [iArg], OptStr [iFlag],
					_tcslen (argv [iArg])) != NULL;
		iFlag++;
	}
	va_end (pFlagList);
	for (iArg = 1; iArg < argc && argv [iArg] [0] == '-'; iArg++);
	return iArg;
}