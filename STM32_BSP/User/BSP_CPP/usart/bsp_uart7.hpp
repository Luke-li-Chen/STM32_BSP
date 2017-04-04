#ifndef __BSP_UART7_HPP
#define __BSP_UART7_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"



class Uart7 : public Usart
{
public:
    enum TxPin
    {
        F7
    };
    enum RxPin
    {
        F6
    };
    Uart7(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = F7, RxPin rxPin = F6);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = F7, RxPin rxPin = F6);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_UART7_HPP
