#include "bsp_usart3.hpp"


Usart3::Usart3(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
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
* @param    txPin: ���͹ܽţ�Ĭ��Ϊ B10
* @param    rxPin: ���չܽţ�Ĭ��Ϊ B11
* @retval   ��
*/
void Usart3::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_usart = USART3;
    m_usartClk = RCC_APB1Periph_USART3;
    m_gpioAF = GPIO_AF_USART3;
    m_irq = USART3_IRQn;

    if (txPin == B10)
    {
        m_txClk     = RCC_AHB1Periph_GPIOB;
        m_txPort    = GPIOB;
        m_txPin     = GPIO_Pin_10;
        m_txSource  = GPIO_PinSource10;
    }
    else if (txPin == C10)
    {
        m_txClk = RCC_AHB1Periph_GPIOC;
        m_txPort = GPIOC;
        m_txPin = GPIO_Pin_10;
        m_txSource = GPIO_PinSource10;
    }
    else
    {
        m_txClk = RCC_AHB1Periph_GPIOD;
        m_txPort = GPIOD;
        m_txPin = GPIO_Pin_8;
        m_txSource = GPIO_PinSource8;
    }

    if (rxPin == B11)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOB;
        m_rxPort    = GPIOB;
        m_rxPin     = GPIO_Pin_11;
        m_rxSource  = GPIO_PinSource11;
    }
    else if (txPin == C11)
    {
        m_rxClk = RCC_AHB1Periph_GPIOC;
        m_rxPort = GPIOC;
        m_rxPin = GPIO_Pin_11;
        m_rxSource = GPIO_PinSource11;
    }
    else
    {
        m_txClk = RCC_AHB1Periph_GPIOD;
        m_txPort = GPIOD;
        m_txPin = GPIO_Pin_9;
        m_txSource = GPIO_PinSource9;
    }

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Usart3::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Usart3::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB1PeriphClockCmd(rcc, newState);
}

