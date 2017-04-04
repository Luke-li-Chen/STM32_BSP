#include "bsp_uart5.hpp"


Uart5::Uart5(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt)
    : Usart()
{
    Init(baud, prePriority, subPriority, useInterrupt);
}

/**
* @brief    ���ڳ�ʼ��
* @param    baud: ������
* @param    prePriority: ��ռ���ȼ����� useInterrupt Ϊ false����ò�����Ч
* @param    subPriority: ��Ӧ���ȼ����� useInterrupt Ϊ false����ò�����Ч
* @param    useInterrupt: �Ƿ�ʹ�ý����жϣ�Ĭ��Ϊ true
* @param    txPin: ���͹ܽţ�Ϊ C12
* @param    rxPin: ���չܽţ�Ϊ D2
* @retval   ��
*/
void Uart5::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt)
{
    m_usart = UART5;
    m_usartClk = RCC_APB1Periph_UART5;
    m_gpioAF = GPIO_AF_UART5;
    m_irq = UART5_IRQn;

    m_txClk = RCC_AHB1Periph_GPIOC;
    m_txPort = GPIOC;
    m_txPin = GPIO_Pin_12;
    m_txSource = GPIO_PinSource12;

    m_rxClk = RCC_AHB1Periph_GPIOD;
    m_rxPort = GPIOD;
    m_rxPin = GPIO_Pin_2;
    m_rxSource = GPIO_PinSource2;

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Uart5::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Uart5::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB1PeriphClockCmd(rcc, newState);
}

