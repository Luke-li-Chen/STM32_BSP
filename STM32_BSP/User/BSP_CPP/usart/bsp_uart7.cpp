#include "bsp_uart7.hpp"


Uart7::Uart7(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
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
* @param    txPin: ���͹ܽţ�Ĭ��Ϊ F7
* @param    rxPin: ���չܽţ�Ĭ��Ϊ F6
* @retval   ��
*/
void Uart7::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_usart = UART7;
    m_usartClk = RCC_APB1Periph_UART7;
    m_gpioAF = GPIO_AF_UART7;
    m_irq = UART7_IRQn;

    if (txPin == F7)
    {
        m_txClk     = RCC_AHB1Periph_GPIOF;
        m_txPort    = GPIOF;
        m_txPin     = GPIO_Pin_7;
        m_txSource  = GPIO_PinSource7;
    }
    else
    {
        
    }

    if (rxPin == F6)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOF;
        m_rxPort    = GPIOF;
        m_rxPin     = GPIO_Pin_6;
        m_rxSource  = GPIO_PinSource6;
    }
    else
    {
        
    }

    InitBase(baud, prePriority, subPriority, useInterrupt);
}


void Uart7::rccGPIOCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_AHB1PeriphClockCmd(rcc, newState);
}

void Uart7::rccUsartCmd(uint32_t rcc, FunctionalState newState)
{
    RCC_APB1PeriphClockCmd(rcc, newState);
}

