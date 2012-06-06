#include "EvryThng.h"

VOID ReportException(LPCTSTR UserMessage, DWORD ExceptionCode)
{
	ReportError(UserMessage, 0, TRUE);
	if (ExceptionCode!=0)
	{
		RaiseException( (0x0fffffff & ExceptionCode) | (0xE0000000), 0, 0, NULL);
	}
}