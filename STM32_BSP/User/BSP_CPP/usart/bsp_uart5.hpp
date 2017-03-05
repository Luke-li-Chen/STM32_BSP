#ifndef __BSP_UART5_HPP
#define __BSP_UART5_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"


class Uart4 : public Usart
{
public:
    //enum TxPin
    //{
    //    C12
    //};
    //enum RxPin
    //{
    //    D2
    //};
    Uart4(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_UART5_HPP
