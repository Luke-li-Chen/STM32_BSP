#ifndef __BSP_USART_DEBUG_H
#define __BSP_USART_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define DEBUG_USART     USART2

int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#define debug(format, ...)      printf("File:" __FILE__ ", Line:%03d: " format "\n", __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif  // __BSP_USART_DEBUG_H
