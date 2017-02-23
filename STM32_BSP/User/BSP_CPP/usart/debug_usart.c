#include <stdio.h>
#include "stm32f4xx.h"

#define DEBUG_USART                             USART1

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

