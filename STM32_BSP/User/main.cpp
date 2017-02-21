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
//#include "BSP_C/usart/bsp_debug_usart.h"
//#include "BSP_C/usart/bsp_usart1.h"
#include "BSP_CPP/usart/bsp_usart2.hpp"
#include <stdio.h>

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

    //Debug_USART_Config(115200);
    //USART1_Config(115200);

    Usart2 usart2(115200, 0, 0, true, Usart2::D5, Usart2::D6);
    //Usart2 usart2(115200);

    usart2.SendStr("Hello ");
    usart2.SendnStr("World!", 2);
    usart2.SendByte('\n');

    printf("Test of usart\n");
    //DEBUG("hhh");

    while (true)
    {
        if (!g_bUartFlag)
        {
            continue;
        }

        g_bUartFlag = false;
        led.RgbRotate();

        usart2.SendByte(g_UartTmp);
    }


}


void Delay(__IO uint32_t nCount)     //�򵥵���ʱ����
{
    for(; nCount != 0; nCount--);
}

