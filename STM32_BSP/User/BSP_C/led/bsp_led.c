/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire, ����
  * @version V1.1
  * @date    2017-01-16
  * @brief   led Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨�� �ɰ���� STM32 F429 ������
  *
  ******************************************************************************
  */

#include "bsp_led.h"

 /**
  * @brief  ��ʼ������ LED �� IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef gpioIni;               // GPIO ��ʼ���ṹ��

    RCC_AHB1PeriphClockCmd(
          LED1_GPIO_CLK
        | LED2_GPIO_CLK
        | LED3_GPIO_CLK
        | LED4_GPIO_CLK,
        ENABLE);                            // ���� LED ��ص� GPIO ����ʱ��

    gpioIni.GPIO_Mode   = GPIO_Mode_OUT;    // ��������ģʽΪ���ģʽ
    gpioIni.GPIO_OType  = GPIO_OType_PP;    // �������ŵ��������Ϊ�������
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;     // ��������Ϊ����ģʽ��Ĭ�� LED ��
    gpioIni.GPIO_Speed  = GPIO_Speed_2MHz;  // ������������Ϊ 50MHz

    gpioIni.GPIO_Pin = LED1_PIN;            // ѡ��Ҫ���Ƶ� GPIO ����
    GPIO_Init(LED1_GPIO_PORT, &gpioIni);    // ��ʼ����Ӧ GPIO

    gpioIni.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED3_PIN;
    GPIO_Init(LED3_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED4_PIN;
    GPIO_Init(LED4_GPIO_PORT, &gpioIni);

    LED_RGBOFF;     // �ر�RGB��
    LED4(ON);       // ָʾ��Ĭ�Ͽ���
}
