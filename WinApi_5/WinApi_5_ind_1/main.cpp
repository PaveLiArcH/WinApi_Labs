#include <tchar.h>
#include <windows.h>
#include "..\WinApi_5\StrSort.h"

int _tmain(int argC, LPCTSTR argV[])
{
	LPCTSTR _array[]={
		_T("First string"),
		_T("Second string"),
		_T("Third string"),
		_T("Fourth string"),
		_T("Fifth string"),
		_T("Fif-th string"),
		_T("Se_cond-th string"),
		_T("Thir'd string"),
		_T("billet"),
		_T("bills"),
		_T("bill's"),
	};

	_tprintf(_T("%s\n"),_T("Before"));

	for(int i=0; i<sizeof(_array)/sizeof(LPCTSTR*); i++)
	{
		_tprintf(_T("%d\t%s\n"), i, _array[i]);
	}

	strSort(sizeof(_array)/sizeof(LPCTSTR*), _array);

	_tprintf(_T("%s\n"),_T("After"));

	for(int i=0; i<sizeof(_array)/sizeof(LPCTSTR*); i++)
	{
		_tprintf(_T("%d\t%s\n"), i, _array[i]);
	}
}