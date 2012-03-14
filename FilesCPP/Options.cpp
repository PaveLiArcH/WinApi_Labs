/* ���⨭� �.7 �㭪�� Options */
/* ��㦥���� �㭪�� ��� �뤥����� 䫠��� ��権 �� ���������
   ��p��� */

#include "EvryThng.h"
#include <stdarg.h>

DWORD Options (int argc, LPTSTR argv[], LPCTSTR OptStr, ...)

/* argv - ��������� ��p���. ��樨, ��稭��騥�� � "-",
          ��������� � argv[1], argv[2], ...

   OptStr - ⥪�⮢�� ��p���, ᮤ�p���� �� �������� ��樨 ��
   �������-�������筮� ᮮ⢥��⢨� � ��p�ᮬ �㫥��� ��p�������
   � ᯨ᪥ ��p����p��-��p������� (...). �� 䫠��
   ��⠭���������� ⮣�� � ⮫쪮 ⮣��, ����� ᨬ���
   ᮮ⢥�����饩 ��樨 ���p�砥��� � argv[1], argv[2], ...
   ����p�頥��� ���祭�� - ������ � argv ��p���� ��p����p�, ��
   �p��������饣� � ����.  */
{
  va_list pFlagList;
  LPBOOL pFlag;
  int iFlag = 0, iArg;

  va_start (pFlagList, OptStr);
  while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL
         && iFlag < (int) _tcslen (OptStr) )  {
     *pFlag = FALSE;
     for (iArg = 1;
          !(*pFlag) && iArg < argc && argv [iArg] [0] == '-';
          iArg++)
       *pFlag = _memtchr (argv [iArg], OptStr [iFlag],
                _tcslen (argv [iArg])) != NULL;
     iFlag++;
  }
  va_end (pFlagList);
  for (iArg = 1; iArg < argc && argv [iArg] [0] == '-'; iArg++);
  return iArg;
}
