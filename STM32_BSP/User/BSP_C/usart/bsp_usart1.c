/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  ������fire
  * @version V1.0
  * @date    2017-01-19
  * @brief   ����c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������
  *
  ******************************************************************************
  */ 

#include "bsp_usart1.h"

uint8_t recv_char=0;


/// ����USART1�����ж�
static void USART1_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* config USART1 clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USART1 Rx (PA.10) as input floating */
    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    //GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    //GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate              = 115200;
    USART_InitStructure.USART_WordLength            = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits              = USART_StopBits_1;
    USART_InitStructure.USART_Parity                = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
#if 0
    USART_Cmd(USART1, ENABLE);
#elif 1
    /* ʹ�ܴ���1�����ж� */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    /* ���ô����ж����ȼ� */
    //NVIC_Configuration();

    /* 
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    ע��: ��Ҫ�ڴ˴��򿪷����ж�
    �����ж�ʹ����SendUart()������
    */
    USART_Cmd(USART1, ENABLE);		/* ʹ�ܴ��� */ 
    /* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
    �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART1, USART_FLAG_TC);		/* �巢����Ǳ�־��Transmission Complete flag */
    USART1_NVIC_Config();  
#endif
}




///**
//  * @brief  UsartReceive ���ڽ����жϷ�������������������
//  * @param  ��
//  * @retval ��
//  */
//void UsartReceive(void)
//{
//	//char  text[40];
//	vu16 i=0;
//
//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
//	{	 
//		USART_ClearFlag(USART1, USART_FLAG_RXNE | USART_FLAG_ORE);
//	    //�����ݲ��� RXNE��OREλ      
//		i = USART_ReceiveData(USART1);
//			printf("%c",i);
//		if(i == '+')
//		{
//			Volume_Add();
//			//printf("+");
//
//		}else if(i == '-')
//		{
//			Volume_Dec();
//			//printf("-");
//		}	
//		
//	}
//}

///**
//  * @brief  UsartReceive ���ڽ����жϷ�������������������
//  * @param  ��
//  * @retval ��
//  */
//void UsartReceive(void)
//{
//
//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
//	{	 
//		USART_ClearFlag(USART1, USART_FLAG_RXNE | USART_FLAG_ORE);
//	   
//		//�����ݲ��� RXNE��OREλ      
//		recv_char = USART_ReceiveData(USART1);
//		printf("%c",recv_char);
//		
//		
//	}
//}


//
///**
//  * @brief  USART1 TX DMA ���ã��ڴ浽����(USART1->DR)
//  * @param  ��
//  * @retval ��
//  */
//uint8_t SendBuff[SENDBUFF_SIZE];
//void USART1_DMA_Config(void)
//{
//		DMA_InitTypeDef DMA_InitStructure;
//	
//		/*����DMAʱ��*/
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//		/*����DMAԴ���������ݼĴ�����ַ*/
//		DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
//
//		/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
//		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
//
//		/*���򣺴��ڴ浽����*/		
//		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
//
//		/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
//		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
//
//		/*�����ַ����*/	    
//		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//
//		/*�ڴ��ַ����*/
//		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
//
//		/*�������ݵ�λ*/	
//		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//
//		/*�ڴ����ݵ�λ 8bit*/
//		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
//
//		/*DMAģʽ������ѭ��*/
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
//
//		/*���ȼ�����*/	
//		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
//
//		/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//
//		/*����DMA1��4ͨ��*/		   
//		DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
//		
//		/*ʹ��DMA*/
//		DMA_Cmd (DMA1_Channel4,ENABLE);					
//		//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
//}

/*********************************************END OF FILE**********************/
