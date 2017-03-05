#include "bsp_uart4.hpp"


Uart4::Uart4(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
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
* @param    txPin: ���͹ܽţ�Ĭ��Ϊ C10
* @param    rxPin: ���չܽţ�Ĭ��Ϊ C11
* @retval   ��
*/
void Uart4::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_usart = UART4;
    m_usartClk = RCC_APB1Periph_UART4;
    m_gpioAF = GPIO_AF_UART4;
    m_irq = UART4_IRQn;

    if (txPin == A0)
    {
        m_txClk     = RCC_AHB1Periph_GPIOA;
        m_txPort    = GPIOA;
        m_txPin     = GPIO_Pin_0;
        m_txSource  = GPIO_PinSource0;
    }
    else
    {
        m_txClk     = RCC_AHB1Periph_GPIOC;
        m_txPort    = GPIOC;
        m_txPin     = GPIO_Pin_10;
        m_txSource  = GPIO_PinSource10;
    }

    if (rxPin == A1)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOA;
        m_rxPort    = GPIOA;
        m_rxPin     = GPIO_Pin_1;
        m_rxSource  = GPIO_PinSource1;
    }
    else
    {
        m_rxClk     = RCC_AHB1Periph_GPIOC;
        m_rxPort    = GPIOC;
        m_rxPin     = GPIO_Pin_11;
        m_rxSource  = GPIO_PinSource11;
    }

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Usart2::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Usart2::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB1PeriphClockCmd(rcc, newState);
}

