/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  陈立，fire
  * @version V1.0
  * @date    2017-01-19
  * @brief   重现c库printf函数到usart端口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板
  *
  ******************************************************************************
  */ 

#include "bsp_usart1.h"



 /**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */
void USART1_Config(int baud)
{
    GPIO_InitTypeDef gpioIni;
    USART_InitTypeDef usart_Ini;

    // 使能时钟
    RCC_AHB1PeriphClockCmd(USART_1_RX_GPIO_CLK | USART_1_TX_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(USART_1_CLK, ENABLE);

    gpioIni.GPIO_OType  = GPIO_OType_PP;
    gpioIni.GPIO_PuPd   = GPIO_PuPd_UP;
    gpioIni.GPIO_Speed  = GPIO_Speed_50MHz;
    gpioIni.GPIO_Mode   = GPIO_Mode_AF;

    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
    gpioIni.GPIO_Pin = USART_1_TX_PIN;
    GPIO_Init(USART_1_TX_GPIO_PORT, &gpioIni);

    /* Configure USART1 Rx (PA.10) as input floating */
    gpioIni.GPIO_Pin = USART_1_RX_PIN;
    GPIO_Init(USART_1_RX_GPIO_PORT, &gpioIni);

    GPIO_PinAFConfig(USART_1_RX_GPIO_PORT, USART_1_RX_SOURCE, USART_1_RX_AF);
    GPIO_PinAFConfig(USART_1_TX_GPIO_PORT, USART_1_TX_SOURCE, USART_1_TX_AF);

    /* USART1 mode config */
    usart_Ini.USART_BaudRate              = baud;
    usart_Ini.USART_WordLength            = USART_WordLength_8b;
    usart_Ini.USART_StopBits              = USART_StopBits_1;
    usart_Ini.USART_Parity                = USART_Parity_No ;
    usart_Ini.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    usart_Ini.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &usart_Ini);
#if 0
    USART_Cmd(USART1, ENABLE);
#elif 1
    /* 使能串口1接收中断 */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    /* 配置串口中断优先级 */
    //NVIC_Configuration();

    /* 
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    注意: 不要在此处打开发送中断
    发送中断使能在SendUart()函数打开
    */
    USART_Cmd(USART1, ENABLE);      /* 使能串口 */
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
    USART1_NVIC_Config();
#endif
}


/// 配置USART1接收中断
static void USART1_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


uint8_t recv_char = 0;

///**
//  * @brief  UsartReceive 串口接收中断服务函数，用来控制音量
//  * @param  无
//  * @retval 无
//  */
//void UsartReceive(void)
//{
//	//char  text[40];
//	vu16 i=0;
//
//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
//	{	 
//		USART_ClearFlag(USART1, USART_FLAG_RXNE | USART_FLAG_ORE);
//	    //读数据并清 RXNE、ORE位      
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
//  * @brief  UsartReceive 串口接收中断服务函数，用来控制音量
//  * @param  无
//  * @retval 无
//  */
//void UsartReceive(void)
//{
//
//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
//	{	 
//		USART_ClearFlag(USART1, USART_FLAG_RXNE | USART_FLAG_ORE);
//	   
//		//读数据并清 RXNE、ORE位      
//		recv_char = USART_ReceiveData(USART1);
//		printf("%c",recv_char);
//		
//		
//	}
//}


//
///**
//  * @brief  USART1 TX DMA 配置，内存到外设(USART1->DR)
//  * @param  无
//  * @retval 无
//  */
//uint8_t SendBuff[SENDBUFF_SIZE];
//void USART1_DMA_Config(void)
//{
//		DMA_InitTypeDef DMA_InitStructure;
//	
//		/*开启DMA时钟*/
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//		/*设置DMA源：串口数据寄存器地址*/
//		DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
//
//		/*内存地址(要传输的变量的指针)*/
//		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
//
//		/*方向：从内存到外设*/		
//		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
//
//		/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
//		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
//
//		/*外设地址不增*/	    
//		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//
//		/*内存地址自增*/
//		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
//
//		/*外设数据单位*/	
//		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//
//		/*内存数据单位 8bit*/
//		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
//
//		/*DMA模式：不断循环*/
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
//
//		/*优先级：中*/	
//		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
//
//		/*禁止内存到内存的传输	*/
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//
//		/*配置DMA1的4通道*/		   
//		DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
//		
//		/*使能DMA*/
//		DMA_Cmd (DMA1_Channel4,ENABLE);					
//		//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
//}

/*********************************************END OF FILE**********************/
