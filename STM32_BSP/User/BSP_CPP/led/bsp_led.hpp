#ifndef __LED_HPP
#define __LED_HPP

#include "stm32f4xx.h"


/// ���Ŷ���
// R ��ɫ��
#define LED_R_PIN               GPIO_Pin_10
#define LED_R_GPIO_PORT         GPIOH
#define LED_R_GPIO_CLK          RCC_AHB1Periph_GPIOH

// G ��ɫ��
#define LED_G_PIN               GPIO_Pin_11
#define LED_G_GPIO_PORT         GPIOH
#define LED_G_GPIO_CLK          RCC_AHB1Periph_GPIOH

// B ��ɫ��
#define LED_B_PIN               GPIO_Pin_12
#define LED_B_GPIO_PORT         GPIOH
#define LED_B_GPIO_CLK          RCC_AHB1Periph_GPIOH

// Сָʾ�ƣ�Pilot��
#define LED_P_PIN               GPIO_Pin_11
#define LED_P_GPIO_PORT         GPIOD
#define LED_P_GPIO_CLK          RCC_AHB1Periph_GPIOD

enum LedStatus
{
    on,
    off,
    toggle
};

enum RGBStatus
{
    red = 0,
    green,
    blue
};

class Led
{
public:
    Led();
    ~Led();

    void Red(LedStatus status);
    void Green(LedStatus status);
    void Blue(LedStatus status);
    void Pilot(LedStatus status);

    void RgbOff(void);
    void AllOff(void);

    // RGB ������ɫ
    void Red(void);
    void Green(void);
    void Blue(void);
    void Yellow(void);
    void Purple(void);
    void Cyan(void);
    void White(void);
    void Black(void);

    void RgbRotate(void);

private:
    void Init(void);
    RGBStatus m_rgb;
};


#endif  /* __LED_HPP */
