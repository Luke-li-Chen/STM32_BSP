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
#include "BSP_CPP/usart/bsp_usart1.hpp"
#include "BSP_CPP/usart/bsp_usart_debug.h"

void Delay(__IO uint32_t nCount);

byte g_UartTmp;
bool g_bUartFlag = false;
Usart1 usart1(9600);

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

    //Usart2 usart2(115200, 0, 0, true, Usart2::D5, Usart2::D6);
    

    usart1.SendStr("Hello ");
    usart1.SendnStr("World!", 2);
    usart1.SendByte('\n');

    for (int i = 0; i < 2; i++)
    {
        usart1.SendByte(0xAA);
    }

    //printf("%u\n", sizeof(Usart1));

    //debug("hhh - %d", 42);

    while (true)
    {
        if (!usart1.GetItFlag())
        {
            continue;
        }

        usart1.ResetItFlag();
        led.RgbRotate();

        usart1.SendByte(usart1.GetReceivedData() + 1);
    }
}


void Delay(__IO uint32_t nCount)     //�򵥵���ʱ����
{
    for(; nCount != 0; nCount--);
}

