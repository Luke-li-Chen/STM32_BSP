#ifndef __BSP_USART6_HPP
#define __BSP_USART6_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"

// Usart6 ���տ� PC7 ʹ��ʱ����ε���������PG9 �ڰ��ϲ���������


class Usart6 : public Usart
{
public:
    enum TxPin
    {
        C6,
        G14
    };
    enum RxPin
    {
        C7,
        G9
    };
    Usart6(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = C6, RxPin rxPin = C7);
    void Init(uint32_t baud, uint8_t prePriority = 0, uint8_t subPriority = 0,
        bool useInterrupt = true, TxPin txPin = C6, RxPin rxPin = C7);

    virtual void rccGPIOCmd(uint32_t, FunctionalState);
    virtual void rccUsartCmd(uint32_t, FunctionalState);
};

#endif  // __BSP_USART6_HPP
