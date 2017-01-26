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
#include "BSP_C/usart/bsp_debug_usart.h"


void Delay(__IO uint32_t nCount);

byte g_UartTmp;
bool g_bUartFlag = false;

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


void Delay(__IO uint32_t nCount)     //简单的延时函数
{
    for(; nCount != 0; nCount--);
}

