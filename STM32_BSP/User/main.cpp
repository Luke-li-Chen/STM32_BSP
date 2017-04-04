/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Chen Li
  * @version V1.0
  * @date    2017-01-26
  * @brief   BSP 测试
  ******************************************************************************
  * @attention
  *
  * 实验平台: 秉火 旧版 STM32 F429 开发板
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "util.h"
#include "BSP_CPP/led/bsp_led.hpp"
#include "BSP_CPP/usart/bsp_usart2.hpp"
#include "BSP_CPP/usart/bsp_usart_debug.h"

void Delay(__IO uint32_t nCount);

byte g_UartTmp;
bool g_bUartFlag = false;
Usart2 usart2(115200);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    Led led;
    led.Green(on);
    Delay(0xFFFFFF);

    //Usart2 usart2(115200, 0, 0, true, Usart2::D5, Usart2::D6);
    

    usart2.SendStr("Hello ");
    usart2.SendnStr("World!", 2);
    usart2.SendByte('\n');

    for (int i = 0; i < 2; i++)
    {
        usart2.SendByte(0xAA);
    }

    printf("%u\n", sizeof(Usart2));

    debug("hhh - %d", 42);

    while (true)
    {
        if (!usart2.GetItFlag())
        {
            continue;
        }

        usart2.ResetItFlag();
        led.RgbRotate();

        usart2.SendByte(usart2.GetReceivedData() + 1);
    }
}


void Delay(__IO uint32_t nCount)     //简单的延时函数
{
    for(; nCount != 0; nCount--);
}

