#include "UART_IRQHandler.h"
#include "EXTI_IRQHandler.h"
#include <string.h>

uint8_t rx_buffer[5] = {0};
uint8_t tx_buffer[100] = {0};
uint8_t vofa_tail[4] = {0x00, 0x00, 0x80, 0x7F};

// 定长中断接收

void UART_Start_Recieve() // 开启接受
{
    HAL_UART_Receive_IT(&huart1, rx_buffer, 5);   // 收到消息进下面的中断回调,定长接收，每收5个字节触发一次中断
    // HAL_UARTEx_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));
    // HAL_UART_Receive_DMA(&huart1, rx_buffer, 5);
    // HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
}

void HAL_UART_RxcpltCallback(UART_HandleTypeDef *huart) // 定长中断回调
{
    if (huart->Instance == USART1)
    {
        if (rx_buffer[0] == 0xFF)
        {
            for (uint8_t i = 0; i < 5; i++)
            {
                if (rx_buffer[i] == 1)
                {
                    Beep_Trigger++;
                }
            }
        }

        HAL_UART_Receive_IT(&huart1, rx_buffer, 5); // 重启接受
    }
}

// 空闲中断回调
// void HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
// {
//     if (huart->Instance == USART1)  // 作用：传多少个"1" 响几下
//     {
//         if (rx_buffer[0] == 0xAA)
//         {
//             memcpy(tx_buffer, rx_buffer, sizeof(rx_buffer));
//             for (uint8_t i = 0; i < Size; i++)
//             {
//                 if (rx_buffer[i] == 1)
//                 {
//                     Beep_Trigger++;
//                 }
//             }
//            // 发送消息
//            // HAL_UART_Transmit(&huart1, tx_buffer, Size, 100);  // size ：发送多少个字节 100：超时限制，超过100ms直接退出，不要写进中断
//            // HAL_UART_Transmit_IT(&huart1, tx_buffer, Size); // 接收到消息反馈一个一模一样的
//         }

//         // HAL_UARTEx_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));
//         HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));  // 重启接受
//     }
// }


// 定长中断接收
// 空闲中断接收
// DMA接收
// 空闲中断DMA接收  用这个

// vofa的float包尾：0x00 0x00 0x80 0x7F
// mencpy(tx_buffer, &value, 4): 把value的值复制到数组tx_buffer的首元素位置，4：value的大小，也可以写sizeof(value)