#include "bsp_usart.hpp"


//Usart::Usart()
//{
//}

void Usart::InitBase(int baud, uint8_t prePriority, uint8_t subPriority, bool useInterrupt)
{
    GPIO_InitTypeDef gpioIni;
    USART_InitTypeDef usartIni;

    // 使能时钟
    m_rccGPIOCmd(m_txClk | m_rxClk, ENABLE);
    m_rccUsartCmd(m_usartClk, ENABLE);

    gpioIni.GPIO_OType  = GPIO_OType_PP;
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;
    gpioIni.GPIO_Speed  = GPIO_Speed_50MHz;
    gpioIni.GPIO_Mode   = GPIO_Mode_AF;

    gpioIni.GPIO_Pin = m_txPin;
    GPIO_Init(m_txPort, &gpioIni);

    gpioIni.GPIO_Pin = m_rxPin;
    GPIO_Init(m_rxPort, &gpioIni);

    GPIO_PinAFConfig(m_rxPort, m_rxSource, m_gpioAF);
    GPIO_PinAFConfig(m_txPort, m_txSource, m_gpioAF);

    usartIni.USART_BaudRate              = baud;
    usartIni.USART_WordLength            = USART_WordLength_8b;
    usartIni.USART_StopBits              = USART_StopBits_1;
    usartIni.USART_Parity                = USART_Parity_No;
    usartIni.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    usartIni.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(m_usart, &usartIni);

    if (useInterrupt)
    {
        /* 使能串口1接收中断 */
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

        /* 配置串口中断优先级 */
        NvicConfig(prePriority, subPriority);

        /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
        如下语句解决第1个字节无法正确发送出去的问题 */
        USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
    }

    /*
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    注意: 不要在此处打开发送中断
    发送中断使能在SendUart()函数打开
    */

    /* 使能串口 */
    USART_Cmd(m_usart, ENABLE);
}

void Usart::SendByte(uint8_t ch)
{
    // 发送一个字节数据到USART1
    USART_SendData(m_usart, ch);

    // 等待发送完毕
    while (USART_GetFlagStatus(m_usart, USART_FLAG_TXE) == RESET);
}

/**
* @brief    串口中断初始化
* @param    prePriority: 抢占优先级
* @param    subPriority: 响应优先级
* @retval   无
*/
void Usart::NvicConfig(uint8_t prePriority, uint8_t subPriority)
{
    NVIC_InitTypeDef nvicIni;
    nvicIni.NVIC_IRQChannel = m_irq;
    nvicIni.NVIC_IRQChannelPreemptionPriority = prePriority;
    nvicIni.NVIC_IRQChannelSubPriority = subPriority;
    nvicIni.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicIni);
}
