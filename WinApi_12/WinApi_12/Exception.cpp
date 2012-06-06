#include <windows.h>
#include <stdio.h>
#include <float.h>
#include "..\..\FilesCPP\EvryThng.h"

static DWORD filter(LPEXCEPTION_POINTERS pExP, LPDWORD eCategory)
{
	DWORD exCode, readWrite, virtAddr;
	exCode = pExP->ExceptionRecord->ExceptionCode;
	printf("Filter except code: %x\n", exCode);
	if(0x20000000 & exCode){
		*eCategory = 10;
		return EXCEPTION_EXECUTE_HANDLER;
	}
	switch(exCode){
		case EXCEPTION_ACCESS_VIOLATION:
			readWrite = pExP->ExceptionRecord->ExceptionInformation[0];
			virtAddr = pExP->ExceptionRecord->ExceptionInformation[1];
			printf("Access violation Read/Write/Exec: %d. Addres: %x\n", readWrite, virtAddr);
			*eCategory = 1;
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
		case EXCEPTION_INT_OVERFLOW:
			*eCategory = 2;
			_clearfp();
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		case EXCEPTION_FLT_OVERFLOW:
			printf("Flt Exception - large result.\n");
			*eCategory = 3;
			_clearfp();
			return EXCEPTION_EXECUTE_HANDLER;
		default:
			*eCategory = 0;
			return EXCEPTION_CONTINUE_SEARCH;
	}
}



int main(int argc, char ** argv)
{
	double x = 1.0, y = 0.0;
	DWORD eCategory, i = 0, ix, iy = 0;
	LPDWORD pNull = NULL;
	BOOL done = FALSE;
	DWORD fpOld, fpNew;
	fpOld = _controlfp(0, 0);
	fpNew = fpOld & ~(EM_OVERFLOW | EM_UNDERFLOW | EM_INEXACT |
		EM_ZERODIVIDE | EM_DENORMAL | EM_INVALID);
	_controlfp(fpNew, MCW_EM);
	while(!done) __try{
		printf("Enter exception type: ");
		printf(" 1: Mem, 2: Int, 3: Flt, 4: User, 5: __leave\n");
		scanf("%d", &i);
		__try{
			switch(i){
				case 1:
					ix = *pNull; *pNull = 5; break;
				case 2:
					ix = ix / iy; break;
				case 3:
					x = x / y;
					printf("x = %20e=n", x); break;
				case 4:
					ReportException("User exception", 1); break;
				case 5:
					__leave;
				default:
					done = TRUE;
			}
		}
		__except(filter(GetExceptionInformation(), &eCategory)){
			switch(eCategory){
				case 0:
					printf("Unknown exception\n"); break;
				case 1:
					printf("Memory ref exception\n"); continue;
				case 2:
					printf("Integer exception\n"); break;
				case 3:
					printf("Floating-point exception\n");
					_clearfp();
					break;
				case 10:
					printf("User exception"); break;
				default:
					printf("Unknown exception\n"); break;
			}
			printf("End of handler\n");
		}
	}
	__finally{
		printf("Abnormal terminate?: %d\n", AbnormalTermination());
	}
	_controlfp(fpOld, 0xFFFFFFFF);
	return 0;
}
