#include "bsp_usart2.hpp"


Usart2::Usart2(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
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
* @param    txPin: 发送管脚，默认为 D5
* @param    rxPin: 接收管脚，默认为 D6
* @retval   无
*/
void Usart2::Init(uint32_t baud, uint8_t prePriority, uint8_t subPriority,
    bool useInterrupt, TxPin txPin, RxPin rxPin)
{
    m_usart = USART2;
    m_usartClk = RCC_APB1Periph_USART2;
    m_gpioAF = GPIO_AF_USART2;
    m_irq = USART2_IRQn;

    if (txPin == A2)
    {
        m_txClk     = RCC_AHB1Periph_GPIOA;
        m_txPort    = GPIOA;
        m_txPin     = GPIO_Pin_2;
        m_txSource  = GPIO_PinSource2;
    }
    else
    {
        m_txClk     = RCC_AHB1Periph_GPIOD;
        m_txPort    = GPIOD;
        m_txPin     = GPIO_Pin_5;
        m_txSource  = GPIO_PinSource5;
    }

    if (rxPin == A3)
    {
        m_rxClk     = RCC_AHB1Periph_GPIOA;
        m_rxPort    = GPIOA;
        m_rxPin     = GPIO_Pin_3;
        m_rxSource  = GPIO_PinSource3;
    }
    else
    {
        m_rxClk     = RCC_AHB1Periph_GPIOD;
        m_rxPort    = GPIOD;
        m_rxPin     = GPIO_Pin_6;
        m_rxSource  = GPIO_PinSource6;
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

