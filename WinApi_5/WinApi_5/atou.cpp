#include <tchar.h>
#include <windows.h>

#include "..\..\WinApi_2\WinApi_2\PrintMsg.h"
#include "..\..\WinApi_3\WinApi_3\ReportError.h"

#include "..\..\FilesCPP\Options.h"
#include "..\..\FilesCPP\Asc2Un.h"

#include <io.h>
#include <stdio.h>
#include <conio.h>

int _tmain(int argC, LPCTSTR argV[])
{
	BOOL _askRewrite=FALSE;
	int _firstName=Options(argC, argV, _T("-i"), &_askRewrite);	

	if ((_firstName+2)==argC)
	{
		int _failRead=_taccess(argV[_firstName], 0 | 2);
		int _notExistOut=_taccess(argV[_firstName+1], 0);
		if (!_failRead)
		{
			BOOL _failIfExists=_askRewrite;
			if (!_notExistOut)
				if (_askRewrite)
				{
					_tprintf(_T("Output file exist. Rewrite (Y/N)? "));
					wint_t _char=_gettch();
					if ((_char==_T('Y'))||(_char==_T('y')))
					{
						_failIfExists=FALSE;
						_tprintf(_T("Rewriting\n"));
					}
				} else
				{
					//_tprintf(_T("Output file exist. Use flag -i to rewrite? "));
					//_failIfExists=TRUE;
				}

			#ifdef _TEST
			//DWORD _startTick=GetTickCount();
			LARGE_INTEGER _startHP;
			LARGE_INTEGER _endHP;
			QueryPerformanceCounter(&_startHP);
			#endif

			BOOL _result=Asc2Un(argV[_firstName], argV[_firstName+1], _failIfExists);

			#ifdef _TEST
			//DWORD _endTick=GetTickCount();
			QueryPerformanceCounter(&_endHP);
			//_tprintf(_T("Ticks spent: %d.\n"),_endTick-_startTick);
			_tprintf(_T("HP Ticks spent: %d.\n"),_endHP.QuadPart-_startHP.QuadPart);
			#endif

			if (!_result)
			{
				_tprintf(_T("Errors occuried while writing\n"));
			}
		} else
		{
			_tprintf(_T("Unable to open input file\n"));
			return 2;
		}
	} else
	{
		_tprintf(_T("Using: atou [-i] fileIn fileOut\n"));
		return 1;
	}
}
