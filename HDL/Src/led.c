#include "led.h"


void led_Water(void)   // 流水灯
{
    LED_ON(1);
    HAL_Delay(200U);
    LED_OFF(1);
    HAL_Delay(200U);
    LED_ON(2);
    HAL_Delay(200U);
    LED_OFF(2);
    HAL_Delay(200U);
}