/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  ������fire
  * @version V1.0
  * @date    2017-01-19
  * @brief   �ṩ�����ô������ù��ܣ��ض��� C �� printf ������ usart �˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� STM32 F429 ������
  *
  ******************************************************************************
  */ 
  
#include "bsp_debug_usart.h"


  /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* �����ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  DEBUG_USART GPIO ���á�����ģʽ����Ϊ8-N-1
  * @param  ������
  * @retval ��
  */
void Debug_USART_Config(int baud)
{
    GPIO_InitTypeDef gpioIni;
    USART_InitTypeDef usartIni;

    // ʹ��ʱ��
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);
    
    // TODO: �˾䲢��ͨ��
    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

    // ���� PXx �� USARTx_Tx
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

    // ���� PXx �� USARTx_Rx
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

    // ����Tx����Ϊ���ù���
    gpioIni.GPIO_Pin    = DEBUG_USART_TX_PIN;
    gpioIni.GPIO_Mode   = GPIO_Mode_AF;
    gpioIni.GPIO_Speed  = GPIO_Speed_50MHz;
    gpioIni.GPIO_OType  = GPIO_OType_PP;
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &gpioIni);

    // ����Rx����Ϊ���ù���
    gpioIni.GPIO_Pin    = DEBUG_USART_RX_PIN;
    //gpioIni.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &gpioIni);

    // ���ô���ģʽ
    usartIni.USART_BaudRate             = baud;
    usartIni.USART_WordLength           = USART_WordLength_8b;
    usartIni.USART_StopBits             = USART_StopBits_1;
    usartIni.USART_Parity               = USART_Parity_No ;
    usartIni.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    usartIni.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USART, &usartIni);

    NVIC_Configuration();
    /*���ô��ڽ����ж�*/
    USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);

    USART_Cmd(DEBUG_USART, ENABLE);
}



/**
* @brief    ���ڷ���һ���ֽ�
* @param    pUSARTx: ʹ�õĴ���
* @param    ch: Ҫ���͵��ֽ�
* @retval   ��
*/
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
    // ����һ���ֽ����ݵ�USART1
    USART_SendData(pUSARTx, ch);

    // �ȴ��������
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/**
* @brief    ���ڷ���ָ�����ȵ��ַ���
* @param    pUSARTx: ʹ�õĴ���
* @param    str: Ҫ���͵��ַ���
* @param    strlen: Ҫ���͵ĳ���
* @retval   ��
*/
void Usart_SendnStr(USART_TypeDef * pUSARTx, uint8_t *str, uint32_t strlen)
{
    for (uint32_t i = 0; i < strlen; i++, str++)
    {
        Usart_SendByte(pUSARTx, *str);
    }
}


/**
* @brief    ���ڷ����ַ���
* @param    pUSARTx: ʹ�õĴ���
* @param    str: Ҫ���͵��ַ���
* @retval   ��
*/
void Usart_SendStr(USART_TypeDef * pUSARTx, const uint8_t *str)
{
    for (; *str != '\0'; str++)
    {
        Usart_SendByte(pUSARTx, *str);
    }
}


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
