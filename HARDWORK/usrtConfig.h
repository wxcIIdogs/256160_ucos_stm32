#ifndef __USARTCONFIG_H
#define	__USARTCONFIG_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

 void USART1_Config(int baud);
 void NVIC_Configuration1(void);
 void USART2_Config(void);
 void NVIC_Configuration2(void);
 int fputc(int ch, FILE *f);
 void setBaudRate_Usart1(uint32_t buad);
 void sendUsartDate(char *date,int size);
 void setUSART1Enable(int flag);
#endif /* __USARTCONFIG_H */
