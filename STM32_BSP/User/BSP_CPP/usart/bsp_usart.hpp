#ifndef __BSP_USART_HPP
#define __BSP_USART_HPP

#include "stm32f4xx.h"
#include "util.h"
//#include <stdio.h>

class Usart
{
public:
    //Usart();

    void InitBase(uint32_t baud, uint8_t prePriority, uint8_t subPriority, bool useInterrupt);

    void SendByte(byte ch);
    void SendnStr(const byte * str, uint32_t strlen);
    void SendStr(const byte * str);

protected:
    void NvicConfig(uint8_t prePriority, uint8_t subPriority);

    USART_TypeDef* m_usart; // 串口名

    uint32_t m_txClk;       // 发送管脚时钟
    uint32_t m_rxClk;       // 接收管脚时钟
    uint32_t m_usartClk;    // 串口时钟
    IRQn m_irq;             // 中断号

    virtual void rccGPIOCmd(uint32_t, FunctionalState) = 0;     // 管脚IO时钟控制函数
    virtual void rccUsartCmd(uint32_t, FunctionalState) = 0;    // 串口时钟控制函数

    GPIO_TypeDef* m_txPort; // 发送管脚PORT
    GPIO_TypeDef* m_rxPort; // 接收管脚PORT

    uint16_t m_txPin;   // 发送管脚PIN
    uint16_t m_rxPin;   // 接收管脚PIN

    uint8_t m_txSource; // 发送管脚SOURCE
    uint8_t m_rxSource; // 接收管脚SOURCE

    uint8_t m_gpioAF;   // GPIO管脚复用目标

};


/*#define DEBUG_USART                             USART1*/
//int fputc(int ch, FILE *f);
//int fgetc(FILE *f);

#endif  // __BSP_USART_HPP



