/* Листинг 4.1. Функция ReportException:
    сообщение об исключении */
/* Расшиpение ReportError, котоpое не завеpшает пpоцесс, а
   генеpиpует пользовательский код исключения */
#include "EvryThng.h"

VOID ReportException (LPCTSTR UserMessage, DWORD ExcetionCode)
    /* Сообщает, как о нефатальной ошибке */
{
   ReportError(UserMessage, 0, TRUE);
   /* Если ошибка фатальна, вызывает исключение */
   if (ExcetionCode != 0)
   RaiseException (
      (0x0FFFFFFF & ExcetionCode) | 0xE0000000, 0, 0, NULL);
   return;
}
