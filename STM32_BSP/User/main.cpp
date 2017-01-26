/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Chen Li
  * @version V1.0
  * @date    2017-01-26
  * @brief   BSP ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨: ���� �ɰ� STM32 F429 ������
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "util.h"
#include "BSP_CPP/led/bsp_led.hpp"
#include "BSP_C/usart/bsp_debug_usart.h"


void Delay(__IO uint32_t nCount);

byte g_UartTmp;
bool g_bUartFlag = false;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    Led led;
    led.Green(on);
    Delay(0xFFFFFF);

    Debug_USART_Config(115200);

    printf("Test of usart\n");
    DEBUG("hhh");

    while (true)
    {
        if (!g_bUartFlag)
        {
            continue;
        }

        g_bUartFlag = false;
        led.RgbRotate();

        Usart_SendByte(DEBUG_USART, g_UartTmp);
    }


}


void Delay(__IO uint32_t nCount)     //�򵥵���ʱ����
{
    for(; nCount != 0; nCount--);
}

