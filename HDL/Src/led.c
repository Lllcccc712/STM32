#include "led.h"
#include "tim.h"


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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	
	  HAL_TIM_Base_Stop_IT(&htim2);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);	

//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

