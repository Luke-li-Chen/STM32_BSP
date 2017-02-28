#ifndef __BSP_USART2_HPP
#define __BSP_USART2_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"

// Usart2 在使用板上 RS232 口时，会出现复位时发送 0xFF 或 0x00 的现象
// 初步怀疑是电源干扰或电源上电速度太慢所导致


class Usart2 : public Usart
{
public:
    enum TxPin
    {
        A2,
        D5
    };
    enum RxPin
    {
        A3,
        D6
    };
    Usart2(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = D5, RxPin rxPin = D6);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = D5, RxPin rxPin = D6);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_USART2_HPP
