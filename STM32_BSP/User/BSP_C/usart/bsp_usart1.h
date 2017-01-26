#ifndef __USART1_H
#define __USART1_H

#include "stm32f4xx.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// 引脚定义
/*******************************************************/

//#define USART_1_TX_A9
#define USART_1_TX_B6

#define USART_1_RX_A10
//#define USART_1_RX_B7


#define USART_1_CLK                         RCC_APB2Periph_USART1
#define USART_1_TX_AF                       GPIO_AF_USART1
#define USART_1_RX_AF                       GPIO_AF_USART1

#ifdef USART_1_TX_A9

#define USART_1_TX_GPIO_PORT                GPIOA
#define USART_1_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_1_TX_PIN                      GPIO_Pin_9
#define USART_1_TX_SOURCE                   GPIO_PinSource9

#elif defined USART_1_TX_B6

#define USART_1_TX_GPIO_PORT                GPIOB
#define USART_1_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define USART_1_TX_PIN                      GPIO_Pin_6
#define USART_1_TX_SOURCE                   GPIO_PinSource6

#endif // USART_1_TX_A9

#ifdef USART_1_RX_A10

#define USART_1_RX_GPIO_PORT                GPIOA
#define USART_1_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USART_1_RX_PIN                      GPIO_Pin_10
#define USART_1_RX_SOURCE                   GPIO_PinSource10

#elif defined USART_1_RX_B7

#define USART_1_RX_GPIO_PORT                GPIOB
#define USART_1_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define USART_1_RX_PIN                      GPIO_Pin_7
#define USART_1_RX_SOURCE                   GPIO_PinSource7

#endif // USART_1_RX_A10







/************************************************************/



/**************************USART参数定义********************************/
#define             macUSART_BAUD_RATE                       115200

#define             macUSARTx                                USART1
#define             macUSART_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define             macUSART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macUSART_IRQ                             USART1_IRQn
#define             macUSART_INT_FUN                         USART1_IRQHandler






void USART1_Config(int baud);
//void UsartReceive(void);
static void USART1_NVIC_Config(void);


#ifdef __cplusplus
}
#endif

#endif  /* __USART1_H */
