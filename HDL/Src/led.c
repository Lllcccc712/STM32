#include "led.h"


void led_Water(void)
{
    LED_ON(1);
    HAL_Delay(200U);
    LED_OFF(1);
    HAL_Delay(200U);
    LED_ON(2);
    HAL_Delay(200U);
    LED_OFF(2);
    HAL_Delay(200U);
    LED_ON(3);
    HAL_Delay(200U);
    LED_OFF(3);
    HAL_Delay(200U);
    LED_ON(4);
    HAL_Delay(200U);
    LED_OFF(4);
    HAL_Delay(200U);
}