/* ���⨭� 2.5. �㭪権 Asc2Un */
//--------------------------------------------------------------

//#include "stdafx.h"
#include "EvryThng.h"
#define BUF_SIZE 256

BOOL Asc2Un (LPCTSTR fIn, LPCTSTR fOut, BOOL bFailIfExists)
/* ����p㥬 䠩� ASCII � Unicode �� ���� CopyFile */
{
  HANDLE hIn, hOut;
  DWORD fdwOut, nIn, nOut, iCopy;
  CHAR aBuffer [BUF_SIZE];
  WCHAR uBuffer [BUF_SIZE];
  BOOL WriteOk = TRUE;

  hIn = CreateFile (fIn, GENERIC_READ, 0, NULL,
       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  /* ��p����塞 ����⢨� CreateFile, �᫨ ��室��� 䠩� 㦥
     ������� */
  fdwOut = bFailIfExists ? CREATE_NEW : CREATE_ALWAYS;
  hOut = CreateFile (fOut, GENERIC_WRITE, 0, NULL,
         fdwOut, FILE_ATTRIBUTE_NORMAL, NULL);
  while (ReadFile (hIn, aBuffer, BUF_SIZE, &nIn, NULL)
         && nIn > 0 && WriteOk ) {
     for (iCopy = 0; iCopy < nIn; iCopy++)
        /* �p���p������� ������� ᨬ���� */
        uBuffer [iCopy] = (WCHAR) aBuffer [iCopy];
     WriteOk = WriteFile (hOut, uBuffer, 2*nIn, &nOut, NULL);
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  return WriteOk;
}
