#include "commom.h"
#include "uart.h"
#include "includes.h"

extern OS_SEM uartSemEvent;

void input_ublox(u8 ch)
{
	OS_ERR err;
	OSSemPost(&uartSemEvent,OS_OPT_POST_1,&err);
}

void callback_rev_data(u8 ch)
{
	input_ublox(ch);
}

