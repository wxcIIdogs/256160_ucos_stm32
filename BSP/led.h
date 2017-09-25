#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */

#define PAout(__X__,pin)    (__X__) == 0?GPIO_ResetBits(GPIOA,pin):GPIO_SetBits(GPIOA,pin)   
#define PAin(pin)           GPIO_ReadInputDataBit(GPIOA,pin)
#define PBout(__X__,pin)     (__X__) == 0?GPIO_ResetBits(GPIOB,pin):GPIO_SetBits(GPIOB,pin)
#define PBin(pin)			GPIO_ReadInputDataBit(GPIOB,pin)
#define PCout(__X__,pin)     (__X__) == 0?GPIO_ResetBits(GPIOC,pin):GPIO_SetBits(GPIOC,pin)
#define PCin(pin)			GPIO_ReadInputDataBit(GPIOC,pin)
#define PDout(__X__,pin)     (__X__) == 0?GPIO_ResetBits(GPIOD,pin):GPIO_SetBits(GPIOD,pin)
#define PDin(pin)   		GPIO_ReadInputDataBit(GPIOD,pin)

#define ON  0
#define OFF 1

#define cs1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#define lcd_reset(a) 	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_5)				
					
#define rs(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_8)		
#define rd(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_7)	
#define wr(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_6)	


#define P1(__X__) 							PAout(((__X__) & 0x80),GPIO_Pin_11);\
																PAout(((__X__) & 0x40),GPIO_Pin_12);\
																PAout(((__X__) & 0x20),GPIO_Pin_15);\
																PCout(((__X__) & 0x10),GPIO_Pin_10);\
																PCout(((__X__) & 0x08),GPIO_Pin_11);\
																PCout(((__X__) & 0x04),GPIO_Pin_12);\
																PDout(((__X__) & 0x02),GPIO_Pin_2);\
																PBout(((__X__) & 0x01),GPIO_Pin_3)
#define GETKEYEVENT     !PBin(GPIO_Pin_14) << 5 |    \
												!PBin(GPIO_Pin_15) << 4 |    \
												!PCin(GPIO_Pin_6) << 3 |		\
												!PCin(GPIO_Pin_7) << 2 |		\
												!PCin(GPIO_Pin_8) << 1 |		\
												!PCin(GPIO_Pin_9) << 0

void LED_GPIO_Config(void);

#endif /* __LED_H */
