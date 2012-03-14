/* ���⨭� 4.1. �㭪�� ReportException:
    ᮮ�饭�� �� �᪫�祭�� */
/* ����p���� ReportError, ���p�� �� ����p蠥� �p����, �
   ����p�p�� ���짮��⥫�᪨� ��� �᪫�祭�� */
#include "EvryThng.h"

VOID ReportException (LPCTSTR UserMessage, DWORD ExcetionCode)
    /* ����頥�, ��� � ���⠫쭮� �訡�� */
{
   ReportError(UserMessage, 0, TRUE);
   /* �᫨ �訡�� �⠫쭠, ��뢠�� �᪫�祭�� */
   if (ExcetionCode != 0)
   RaiseException (
      (0x0FFFFFFF & ExcetionCode) | 0xE0000000, 0, 0, NULL);
   return;
}
