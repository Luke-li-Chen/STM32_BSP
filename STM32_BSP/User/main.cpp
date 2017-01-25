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
#include "BSP_CPP/led/bsp_led.hpp"


void Delay(__IO uint32_t nCount);

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

    //while (true)
    //{
    //    Delay(0xFFFFFF);
    //    led.RgbRotate();
    //}



//     while (1)
//     {
//         led.Red(on);
//         Delay(0xFFFFFF);
//         led.Red(off);
// 
//         led.Green(on);
//         Delay(0xFFFFFF);
//         led.Green(off);
// 
//         led.Blue(on);
//         Delay(0xFFFFFF);
//         led.Blue(off);
// 
//         led.Pilot(on);
//         Delay(0xFFFFFF);
//         led.Pilot(off);
//     }

    while (1)
    {
        led.Red();
        Delay(0xFFFFFF);
        led.Red();

        led.Green();
        Delay(0xFFFFFF);
        led.Green();

        led.Blue();
        Delay(0xFFFFFF);
        led.Blue();

        led.Yellow();
        Delay(0xFFFFFF);
        led.Yellow();

        led.Purple();
        Delay(0xFFFFFF);
        led.Purple();

        led.Cyan();
        Delay(0xFFFFFF);
        led.Cyan();

        led.White();
        Delay(0xFFFFFF);
        led.White();

        led.Black();
        Delay(0xFFFFFF);
        led.Black();
    }
}


void Delay(__IO uint32_t nCount)     //简单的延时函数
{
    for(; nCount != 0; nCount--);
}

