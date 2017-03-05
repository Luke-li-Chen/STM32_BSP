#ifndef __BSP_UART4_HPP
#define __BSP_UART4_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"


class Uart4 : public Usart
{
public:
    enum TxPin
    {
        A0,
        C10
    };
    enum RxPin
    {
        A1,
        C11
    };
    Uart4(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = C10, RxPin rxPin = C11);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = C10, RxPin rxPin = C11);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_UART4_HPP
