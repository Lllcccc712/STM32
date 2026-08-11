
#include "led.h"
#include "gpio.h"

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
void led_off_all(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}