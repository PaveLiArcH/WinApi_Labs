#include "StrSort.h"

#define IGNORE_CASE

int internalCmp(const void *a_first, const void *a_second)
{
	#ifdef IGNORE_CASE
	return lstrcmp((*(LPCTSTR *)a_first), (*(LPCTSTR *)a_second));
	#else
	return _tcscmp((*(LPCTSTR *)a_first), (*(LPCTSTR *)a_second));
	#endif
}

void strSort(int a_count, LPCTSTR *a_array)
{
	qsort(a_array, a_count, sizeof(LPCTSTR), internalCmp);
}