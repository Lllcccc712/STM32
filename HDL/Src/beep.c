#include "beep.h"

void Beep_Init(void)
{
    BEEP_ON();
    HAL_Delay(50);
    BEEP_OFF();
    HAL_Delay(50);
    BEEP_ON();
    HAL_Delay(50);
    BEEP_OFF();
    HAL_Delay(50);
}

void Beep_Alarm(uint8_t times)  // 响几下
{
    uint8_t i = 0;
    for(i = 0; i < times; i++)
    {
        BEEP_ON();
        HAL_Delay(50);
        BEEP_OFF();
        HAL_Delay(50);
    }
}