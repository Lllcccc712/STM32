#include "CAN_IRQHandler.h"

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
extern Mode State;
extern uint8_t led_flag;

// 用来回复CAN消息的函数
// 参数：hcan, 回复ID, 数据指针, 数据长度
void CAN_Send_Response(CAN_HandleTypeDef *hcan, uint32_t resp_id, uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailBox;

    TxHeader.StdId = 0;        
    TxHeader.ExtId = resp_id;    // 把要回复的ID传进来
    TxHeader.IDE = CAN_ID_EXT;   // 扩展帧
    TxHeader.RTR = CAN_RTR_DATA; // 数据帧
    TxHeader.DLC = len;          // 数据长度
    TxHeader.TransmitGlobalTime = DISABLE;

    HAL_CAN_AddTxMessage(hcan, &TxHeader, data, &TxMailBox);
}

/*void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    // 确保是CAN1触发的中断
    if(hcan->Instance == CAN1)
    {
        // 从FIFO 0 把数据捞出来，存到RxData数组里
        if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            if(RxHeader.StdId == 0x201)
            {
                Beep_Trigger = 1;

                CAN_TxHeaderTypeDef TxHeader;
                uint32_t TxMailBox; // 用于记录这次发送用掉了哪个邮箱
                uint8_t TxData[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}; // 要发送的数据

                // TxHeader.StdId = 0x102; // 输入11位标准ID
                TxHeader.ExtId = 0;     // 扩展ID
                TxHeader.IDE = CAN_ID_STD; // CAN_ID_EXT 标准帧
                TxHeader.RTR = CAN_RTR_DATA; // 数据帧
                TxHeader.DLC = 8;   // 数据长度（0-8）
                TxHeader.TransmitGlobalTime = DISABLE; // 禁用时间戳

                HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, &TxMailBox);
            }
            else if(RxHeader.StdId == 0x202)
            {
                // 这是2号电机发来的反馈
            }
        }
    }
    else if(hcan->Instance == CAN2)
    {
        if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            // 处理CAN2的消息
        }
    }
}*/

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN1)
    {
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            // 判断扩展帧
            if (RxHeader.IDE == CAN_ID_EXT)
            {
                if (RxHeader.ExtId == 0x01020101)
                {
                    Beep_Trigger = RxData[0];
                    State = BUZZER;
                }
                else if (RxHeader.ExtId == 0x01020201)
                {
                    led_flag = RxData[0];
                    State = LED_WATER;
                }
            }
        }
    }
}