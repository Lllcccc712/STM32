#include "CAN_IRQHandler.h"

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
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
}