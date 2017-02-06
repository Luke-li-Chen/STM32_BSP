#include "bsp_usart1.hpp"


Usart1::Usart1(int baud, uint8_t prePriority, uint8_t subPriority,
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
* @param    txPin: ���͹ܽţ�Ĭ��Ϊ A9
* @param    rxPin: ���չܽţ�Ĭ��Ϊ A10
* @retval   ��
*/
void Usart1::Init(int baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_rccGPIOCmd = RCC_AHB1PeriphClockCmd;
    m_rccUsartCmd = RCC_APB2PeriphClockCmd;

    m_usart = USART1;
    m_usartClk = RCC_APB2Periph_USART1;
    m_gpioAF = GPIO_AF_USART1;
    m_irq = USART1_IRQn;

    if (txPin == A9)
    {
        m_txClk     = RCC_AHB1Periph_GPIOA;
        m_txPort    = GPIOA;
        m_txPin     = GPIO_Pin_9;
        m_txSource  = GPIO_PinSource9;
    }
    else
    {
        m_txClk     = RCC_AHB1Periph_GPIOB;
        m_txPort    = GPIOB;
        m_txPin     = GPIO_Pin_6;
        m_txSource  = GPIO_PinSource6;
    }

    if (rxPin == A10)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOA;
        m_rxPort    = GPIOA;
        m_rxPin     = GPIO_Pin_10;
        m_rxSource  = GPIO_PinSource10;
    }
    else
    {
        m_rxClk     = RCC_AHB1Periph_GPIOB;
        m_rxPort    = GPIOB;
        m_rxPin     = GPIO_Pin_7;
        m_rxSource  = GPIO_PinSource7;
    }

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Usart1::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Usart1::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB2PeriphClockCmd(rcc, newState);
}

