#ifndef __BSP_H
#define	__BSP_H

void SysTick_init(void);
void BSP_Init(void);



#define SIZE_SERIAL 1024
extern void callback_rev_data(unsigned char data);


#endif // __BSP_H
