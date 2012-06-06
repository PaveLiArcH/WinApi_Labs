#include <windows.h>
#include <stdio.h>
#include "..\..\FilesCPP\EvryThng.h"

void toupper(char * buf, int len)
{
	while(len--){
		if(*buf >= 'a' && *buf <= 'z') *buf = *buf + 'A' - 'a';
		buf++;
	}
}

int main(int argc, char ** argv)
{
	char * buf = NULL;
	char msg[0x100];
	char * cpInFile, * cpOutFile = (char*)malloc(0x100);
	int iCurrLenFilename = 0;
	HANDLE hInFile, hOutFile;
	for(int iArg = 1; iArg < argc; iArg++)
	{
		__try
		{
			__try
			{
				cpInFile = argv[iArg];
				strcpy(cpOutFile, "UC_");
				strcat(cpOutFile, cpInFile);
				hInFile = CreateFile(cpInFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
				if(hInFile == INVALID_HANDLE_VALUE){
					sprintf(msg, "File `%s' not found\n", cpInFile);
					ReportException(msg, EXCEPTION_INVALID_HANDLE);
				}
				hOutFile = CreateFile(cpOutFile, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
				if(hOutFile == INVALID_HANDLE_VALUE){
					sprintf(msg, "File `%s' already exist\n", cpOutFile);
					ReportException(msg, EXCEPTION_INVALID_HANDLE);
				}
				if(!LockFile(hInFile, 0, 0, 0, 0)){
					sprintf(msg, "Locked file `%s' error\n", cpInFile);
					ReportException(msg, EXCEPTION_INVALID_HANDLE);
				}
				if(!LockFile(hOutFile, 0, 0, 0, 0)){
					sprintf(msg, "Locked file `%s' error\n", cpOutFile);
					ReportException(msg, EXCEPTION_INVALID_HANDLE);
				}
				DWORD dwFileSize = GetFileSize(hInFile, NULL);
				DWORD nIn, nOut;
				buf = (char*)malloc(dwFileSize);
				//if(!buf)
					ReportException("Alloc error\n", EXCEPTION_INVALID_HANDLE);
				if(!ReadFile(hInFile, buf, dwFileSize, &nIn, NULL))
					ReportException("Read error\n", EXCEPTION_INVALID_HANDLE);
				toupper(buf, dwFileSize);
				if(!WriteFile(hOutFile, buf, dwFileSize, &nOut, NULL))
					ReportException("Write error\n", EXCEPTION_INVALID_HANDLE);
			} __finally
			{
				if (buf)
				{
					free(buf);
				}
				if (hInFile)
				{
					UnlockFile(hInFile, 0, 0, 0, 0);
					CloseHandle(hInFile);
				}
				if (hOutFile)
				{
					UnlockFile(hOutFile, 0, 0, 0, 0);
					CloseHandle(hOutFile);
				}
			}
		}__except(EXCEPTION_EXECUTE_HANDLER)
		{
			printf("Except\n");
		}
	}
	return 0;
}
