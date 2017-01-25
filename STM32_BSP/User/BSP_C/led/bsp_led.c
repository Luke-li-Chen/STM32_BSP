/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire, 陈立
  * @version V1.1
  * @date    2017-01-16
  * @brief   led 应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台： 旧版秉火 STM32 F429 开发板
  *
  ******************************************************************************
  */

#include "bsp_led.h"

 /**
  * @brief  初始化控制 LED 的 IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef gpioIni;               // GPIO 初始化结构体

    RCC_AHB1PeriphClockCmd(
          LED1_GPIO_CLK
        | LED2_GPIO_CLK
        | LED3_GPIO_CLK
        | LED4_GPIO_CLK,
        ENABLE);                            // 开启 LED 相关的 GPIO 外设时钟

    gpioIni.GPIO_Mode   = GPIO_Mode_OUT;    // 设置引脚模式为输出模式
    gpioIni.GPIO_OType  = GPIO_OType_PP;    // 设置引脚的输出类型为推挽输出
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;     // 设置引脚为上拉模式，默认 LED 亮
    gpioIni.GPIO_Speed  = GPIO_Speed_2MHz;  // 设置引脚速率为 50MHz

    gpioIni.GPIO_Pin = LED1_PIN;            // 选择要控制的 GPIO 引脚
    GPIO_Init(LED1_GPIO_PORT, &gpioIni);    // 初始化相应 GPIO

    gpioIni.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED3_PIN;
    GPIO_Init(LED3_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED4_PIN;
    GPIO_Init(LED4_GPIO_PORT, &gpioIni);

    LED_RGBOFF;     // 关闭RGB灯
    LED4(ON);       // 指示灯默认开启
}
