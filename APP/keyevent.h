
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"


typedef void (*key_evnet_func)(int id,int event);
typedef struct key_event
{	
	int id;
	int keymark;
	key_evnet_func func;
	struct key_event *next;
}*struct_key_event;

extern void scanKeyEvent(void);


