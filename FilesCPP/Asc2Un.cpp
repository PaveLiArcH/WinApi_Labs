/* Листинг 2.5. Функций Asc2Un */
//--------------------------------------------------------------

//#include "stdafx.h"
#include "Asc2Un.h"
#define BUF_SIZE 256

//#define SEQSCAN
//#define NOBUFFER

BOOL Asc2Un (LPCTSTR fIn, LPCTSTR fOut, BOOL bFailIfExists)
/* Копиpуем файл ASCII в Unicode на базе CopyFile */
{
  HANDLE hIn, hOut;
  DWORD fdwOut, nIn, nOut, iCopy;
  CHAR aBuffer [BUF_SIZE];
  WCHAR uBuffer [BUF_SIZE];
  BOOL WriteOk = TRUE;

  hIn = CreateFile (fIn, GENERIC_READ, 0, NULL,
	  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL
	#ifdef SEQSCAN
		  | FILE_FLAG_SEQUENTIAL_SCAN
	#endif
	#ifdef NOBUFFER
		  | FILE_FLAG_NO_BUFFERING
	#endif
	  , NULL);

  /* Опpеделяем действие CreateFile, если выходной файл уже
     существует */
  fdwOut = bFailIfExists ? CREATE_NEW : CREATE_ALWAYS;
  hOut = CreateFile (fOut, GENERIC_WRITE, 0, NULL,
         fdwOut, FILE_ATTRIBUTE_NORMAL, NULL);
  while (ReadFile (hIn, aBuffer, BUF_SIZE, &nIn, NULL)
         && nIn > 0 && WriteOk ) {
     for (iCopy = 0; iCopy < nIn; iCopy++)
        /* Пpеобpзование каждого символа */
        uBuffer [iCopy] = (WCHAR) aBuffer [iCopy];
     WriteOk = WriteFile (hOut, uBuffer, 2*nIn, &nOut, NULL);
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  return WriteOk;
}
