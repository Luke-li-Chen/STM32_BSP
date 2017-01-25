/**
  ******************************************************************************
  * @file    bsp_led.cpp
  * @author  ����
  * @version V1.0
  * @date    2017-01-26
  * @brief   led Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨�� �ɰ���� STM32 F429 ������
  *
  ******************************************************************************
  */

#include "bsp_led.hpp"


Led::Led()
{
    Init();
    m_rgb = red;
}

Led::~Led()
{
}

/**
* @brief  ��ʼ������ LED �� IO
* @param  ��
* @retval ��
*/
void Led::Init(void)
{
    GPIO_InitTypeDef gpioIni;

    // ���� LED ��ص� GPIO ����ʱ��
    RCC_AHB1PeriphClockCmd(
        LED_R_GPIO_CLK
        | LED_G_GPIO_CLK
        | LED_B_GPIO_CLK
        | LED_P_GPIO_CLK,
        ENABLE);

    gpioIni.GPIO_Mode = GPIO_Mode_OUT;    // ��������ģʽΪ���ģʽ
    gpioIni.GPIO_OType = GPIO_OType_PP;    // �������ŵ��������Ϊ�������
    gpioIni.GPIO_PuPd = GPIO_PuPd_DOWN;   // ��������Ϊ����ģʽ��Ĭ�� LED ��
    gpioIni.GPIO_Speed = GPIO_Speed_2MHz;  // ������������

                                           // ��ʼ�� GPIO
    gpioIni.GPIO_Pin = LED_R_PIN;
    GPIO_Init(LED_R_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED_G_PIN;
    GPIO_Init(LED_G_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED_B_PIN;
    GPIO_Init(LED_B_GPIO_PORT, &gpioIni);

    gpioIni.GPIO_Pin = LED_P_PIN;
    GPIO_Init(LED_P_GPIO_PORT, &gpioIni);

    // �ر�RGB��
    AllOff();
}

void Led::Red(LedStatus status)
{
    if (status == on)
    {
        GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_PIN);
    }
    else if (status == off)
    {
        GPIO_SetBits(LED_R_GPIO_PORT, LED_R_PIN);
    }
    else
    {
        GPIO_ToggleBits(LED_R_GPIO_PORT, LED_R_PIN);
    }
}

void Led::Green(LedStatus status)
{
    if (status == on)
    {
        GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_PIN);
    }
    else if (status == off)
    {
        GPIO_SetBits(LED_G_GPIO_PORT, LED_G_PIN);
    }
    else
    {
        GPIO_ToggleBits(LED_G_GPIO_PORT, LED_G_PIN);
    }
}

void Led::Blue(LedStatus status)
{
    if (status == on)
    {
        GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_PIN);
    }
    else if (status == off)
    {
        GPIO_SetBits(LED_B_GPIO_PORT, LED_B_PIN);
    }
    else
    {
        GPIO_ToggleBits(LED_B_GPIO_PORT, LED_B_PIN);
    }
}

void Led::Pilot(LedStatus status)
{
    if (status == on)
    {
        GPIO_ResetBits(LED_P_GPIO_PORT, LED_P_PIN);
    }
    else if (status == off)
    {
        GPIO_SetBits(LED_P_GPIO_PORT, LED_P_PIN);
    }
    else
    {
        GPIO_ToggleBits(LED_P_GPIO_PORT, LED_P_PIN);
    }
}

void Led::RgbOff(void)
{
    Red(off);
    Green(off);
    Blue(off);
}

void Led::AllOff(void)
{
    Red(off);
    Green(off);
    Blue(off);
    Pilot(off);
}

void Led::Red(void)
{
    Red(on);
    Green(off);
    Blue(off);
}

void Led::Green(void)
{
    Red(off);
    Green(on);
    Blue(off);
}

void Led::Blue(void)
{
    Red(off);
    Green(off);
    Blue(on);
}

void Led::Yellow(void)
{
    Red(on);
    Green(on);
    Blue(off);
}

void Led::Purple(void)
{
    Red(on);
    Green(off);
    Blue(on);
}

void Led::Cyan(void)
{
    Red(off);
    Green(on);
    Blue(on);
}

void Led::White(void)
{
    Red(on);
    Green(on);
    Blue(on);
}

void Led::Black(void)
{
    Red(off);
    Green(off);
    Blue(off);
}

void Led::RgbRotate(void)
{
    int rgb = m_rgb;
    rgb++;
    if (rgb > 2)
    {
        rgb = 0;
    }
    m_rgb = (RGBStatus)rgb;

    switch (m_rgb)
    {
    case red:
        Red();
        break;
    case green:
        Green();
        break;
    case blue:
        Blue();
        break;
    default:
        break;
    }
}

