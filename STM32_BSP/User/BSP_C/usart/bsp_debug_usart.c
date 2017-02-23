/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  陈立，fire
  * @version V1.0
  * @date    2017-01-19
  * @brief   提供调试用串口配置功能，重定向 C 库 printf 函数到 usart 端口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 STM32 F429 开发板
  *
  ******************************************************************************
  */ 
  
#include "bsp_debug_usart.h"


  /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* 配置中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  DEBUG_USART GPIO 配置。工作模式配置为8-N-1
  * @param  波特率
  * @retval 无
  */
void Debug_USART_Config(int baud)
{
    GPIO_InitTypeDef gpioIni;
    USART_InitTypeDef usartIni;

    // 使能时钟
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);
    
    // TODO: 此句并不通用
    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

    // 连接 PXx 到 USARTx_Tx
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

    // 连接 PXx 到 USARTx_Rx
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

    // 配置Tx引脚为复用功能
    gpioIni.GPIO_Pin    = DEBUG_USART_TX_PIN;
    gpioIni.GPIO_Mode   = GPIO_Mode_AF;
    gpioIni.GPIO_Speed  = GPIO_Speed_50MHz;
    gpioIni.GPIO_OType  = GPIO_OType_PP;
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &gpioIni);

    // 配置Rx引脚为复用功能
    gpioIni.GPIO_Pin    = DEBUG_USART_RX_PIN;
    //gpioIni.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &gpioIni);

    // 配置串口模式
    usartIni.USART_BaudRate             = baud;
    usartIni.USART_WordLength           = USART_WordLength_8b;
    usartIni.USART_StopBits             = USART_StopBits_1;
    usartIni.USART_Parity               = USART_Parity_No ;
    usartIni.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    usartIni.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USART, &usartIni);

    NVIC_Configuration();
    /*配置串口接收中断*/
    USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);

    USART_Cmd(DEBUG_USART, ENABLE);
}



/**
* @brief    串口发送一个字节
* @param    pUSARTx: 使用的串口
* @param    ch: 要发送的字节
* @retval   无
*/
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
    // 发送一个字节数据到USART1
    USART_SendData(pUSARTx, ch);

    // 等待发送完毕
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/**
* @brief    串口发送指定长度的字符串
* @param    pUSARTx: 使用的串口
* @param    str: 要发送的字符串
* @param    strlen: 要发送的长度
* @retval   无
*/
void Usart_SendnStr(USART_TypeDef * pUSARTx, uint8_t *str, uint32_t strlen)
{
    for (uint32_t i = 0; i < strlen; i++, str++)
    {
        Usart_SendByte(pUSARTx, *str);
    }
}


/**
* @brief    串口发送字符串
* @param    pUSARTx: 使用的串口
* @param    str: 要发送的字符串
* @retval   无
*/
void Usart_SendStr(USART_TypeDef * pUSARTx, const uint8_t *str)
{
    for (; *str != '\0'; str++)
    {
        Usart_SendByte(pUSARTx, *str);
    }
}


/**
* @brief    重定向 c 库函数 fputc 到串口 DEBUG_USART，重定向后可使用 printf 函数
* @param    ch: 要发送的字符
* @retval   发送的字符
*/
int fputc(int ch, FILE *f)
{
    // 发送一个字节数据到串口DEBUG_USART
    USART_SendData(DEBUG_USART, (uint8_t)ch);

    // 等待发送完毕
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);
    // 或者
    // while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TC) == RESET);
    return (ch);
}


/**
* @brief    重定向 c 库函数 fgetc 到串口 DEBUG_USART，重写向后可使用 scanf、getchar 等函数
* @retval   接收的字符
*/
int fgetc(FILE *f)
{
    // 等待串口输入数据
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USART);
}
