#include <stdio.h>
#include "stm32f4xx.h"

#define DEBUG_USART                             USART1

/**
* @brief    �ض��� c �⺯�� fputc ������ DEBUG_USART���ض�����ʹ�� printf ����
* @param    ch: Ҫ���͵��ַ�
* @retval   ���͵��ַ�
*/
int fputc(int ch, FILE *f)
{
    // ����һ���ֽ����ݵ�����DEBUG_USART
    USART_SendData(DEBUG_USART, (uint8_t)ch);

    // �ȴ��������
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);
    // ����
    // while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TC) == RESET);
    return (ch);
}


/**
* @brief    �ض��� c �⺯�� fgetc ������ DEBUG_USART����д����ʹ�� scanf��getchar �Ⱥ���
* @retval   ���յ��ַ�
*/
int fgetc(FILE *f)
{
    // �ȴ�������������
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USART);
}

