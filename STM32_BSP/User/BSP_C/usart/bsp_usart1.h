#ifndef __USART1_H
#define __USART1_H

#include "stm32f4xx.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// 引脚定义
/*******************************************************/
#define USART_1_CLK                         RCC_APB2Periph_USART1

#define USART_1_RX_GPIO_PORT                GPIOA
#define USART_1_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_1_RX_PIN                      GPIO_Pin_10
#define USART_1_RX_AF                       GPIO_AF_USART1
#define USART_1_RX_SOURCE                   GPIO_PinSource10

#define USART_1_TX_GPIO_PORT                GPIOA
#define USART_1_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_1_TX_PIN                      GPIO_Pin_9
#define USART_1_TX_AF                       GPIO_AF_USART1
#define USART_1_TX_SOURCE                   GPIO_PinSource9
/************************************************************/



/**************************USART参数定义********************************/
#define             macUSART_BAUD_RATE                       115200

#define             macUSARTx                                USART1
#define             macUSART_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define             macUSART_CLK                             RCC_APB2Periph_USART1
#define             macUSART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macUSART_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define             macUSART_TX_PORT                         GPIOA   
#define             macUSART_TX_PIN                          GPIO_Pin_9
#define             macUSART_RX_PORT                         GPIOA 
#define             macUSART_RX_PIN                          GPIO_Pin_10
#define             macUSART_IRQ                             USART1_IRQn
#define             macUSART_INT_FUN                         USART1_IRQHandler






void USART1_Config(void);
void UsartReceive(void);


void NVIC_Configuration(void);
void Usart_SendStr_length(uint8_t *str,uint32_t strlen);
void Usart_SendString(uint8_t *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);


#ifdef __cplusplus
}
#endif

#endif  /* __USART1_H */
