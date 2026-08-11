#include "TIM_IRQHandler.h"


uint16_t tim_count = 0;
void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        tim_count++;
        if(tim_count == 500)
        {
            Beep_Trigger = 1;
            tim_count = 0;
        }
 
    }
}
