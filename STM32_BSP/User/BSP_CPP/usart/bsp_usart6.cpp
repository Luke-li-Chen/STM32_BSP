#include "bsp_usart6.hpp"


Usart6::Usart6(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
    : Usart()
{
    Init(baud, prePriority, subPriority, useInterrupt, txPin, rxPin);
}

/**
* @brief    ���ڳ�ʼ��
* @param    baud: ������
* @param    prePriority: ��ռ���ȼ����� useInterrupt Ϊ false����ò�����Ч
* @param    subPriority: ��Ӧ���ȼ����� useInterrupt Ϊ false����ò�����Ч
* @param    useInterrupt: �Ƿ�ʹ�ý����жϣ�Ĭ��Ϊ true
* @param    txPin: ���͹ܽţ�Ĭ��Ϊ C6
* @param    rxPin: ���չܽţ�Ĭ��Ϊ C7
* @retval   ��
*/
void Usart6::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_usart = USART6;
    m_usartClk = RCC_APB2Periph_USART6;
    m_gpioAF = GPIO_AF_USART6;
    m_irq = USART6_IRQn;

    if (txPin == C6)
    {
        m_txClk     = RCC_AHB1Periph_GPIOC;
        m_txPort    = GPIOC;
        m_txPin     = GPIO_Pin_6;
        m_txSource  = GPIO_PinSource6;
    }
    else
    {
        m_txClk     = RCC_AHB1Periph_GPIOG;
        m_txPort    = GPIOG;
        m_txPin     = GPIO_Pin_14;
        m_txSource  = GPIO_PinSource14;
    }

    if (rxPin == C7)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOC;
        m_rxPort    = GPIOC;
        m_rxPin     = GPIO_Pin_7;
        m_rxSource  = GPIO_PinSource7;
    }
    else
    {
        m_rxClk     = RCC_AHB1Periph_GPIOG;
        m_rxPort    = GPIOG;
        m_rxPin     = GPIO_Pin_9;
        m_rxSource  = GPIO_PinSource9;
    }

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Usart2::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Usart2::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB2PeriphClockCmd(rcc, newState);
}

