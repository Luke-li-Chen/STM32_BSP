#ifndef __BSP_USART3_HPP
#define __BSP_USART3_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"


class Usart3 : public Usart
{
public:
    enum TxPin
    {
        B10,
        C10,
        D8
    };
    enum RxPin
    {
        B11,
        C11,
        D9
    };
    Usart3(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = B10, RxPin rxPin = B11);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = B10, RxPin rxPin = B11);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_USART3_HPP
