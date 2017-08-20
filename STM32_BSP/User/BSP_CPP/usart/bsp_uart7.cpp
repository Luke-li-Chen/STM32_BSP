#include "bsp_uart7.hpp"


Uart7::Uart7(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
    : Usart()
{
    Init(baud, prePriority, subPriority, useInterrupt, txPin, rxPin);
}

/**
* @brief    串口初始化
* @param    baud: 波特率
* @param    prePriority: 抢占优先级；若 useInterrupt 为 false，则该参数无效
* @param    subPriority: 响应优先级；若 useInterrupt 为 false，则该参数无效
* @param    useInterrupt: 是否使用接收中断，默认为 true
* @param    txPin: 发送管脚，默认为 F7
* @param    rxPin: 接收管脚，默认为 F6
* @retval   无
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

