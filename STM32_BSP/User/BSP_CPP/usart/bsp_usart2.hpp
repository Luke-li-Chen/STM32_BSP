#ifndef __BSP_USART2_HPP
#define __BSP_USART2_HPP

#include "stm32f4xx.h"
#include "bsp_usart.hpp"

// Usart2 ��ʹ�ð��� RS232 ��ʱ������ָ�λʱ���� 0xFF �� 0x00 ������
// ���������ǵ�Դ���Ż��Դ�ϵ��ٶ�̫��������


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
