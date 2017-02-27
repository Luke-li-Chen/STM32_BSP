#ifndef __BSP_USART2_HPP
#define __BSP_USART2_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"

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
        bool useInterrupt = true, TxPin txPin = A2, RxPin rxPin = A3);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = A2, RxPin rxPin = A3);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_USART2_HPP
