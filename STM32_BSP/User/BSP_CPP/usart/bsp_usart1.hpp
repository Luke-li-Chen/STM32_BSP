#ifndef __BSP_USART1_HPP
#define __BSP_USART1_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"

class Usart1 : public Usart
{
public:
    enum TxPin
    {
        A9,
        B6
    };
    enum RxPin
    {
        A10,
        B7
    };
    Usart1(int baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = A9, RxPin rxPin = A10);
    void Init(int baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = A9, RxPin rxPin = A10);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_USART1_HPP
