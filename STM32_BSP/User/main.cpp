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
#include "BSP_C/led/bsp_led.h"


void Delay(__IO uint32_t nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    LED_GPIO_Config();


    while (1)
    {
        LED1(ON);
        Delay(0xFFFFFF);
        LED1(OFF);

        LED2(ON);
        Delay(0xFFFFFF);
        LED2(OFF);

        LED3(ON);
        Delay(0xFFFFFF);
        LED3(OFF);

        LED4(ON);
        Delay(0xFFFFFF);
        LED4(OFF);
    }
}


void Delay(__IO uint32_t nCount)     //简单的延时函数
{
    for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

