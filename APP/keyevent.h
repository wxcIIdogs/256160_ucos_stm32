
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
extern void register_key_event(int id,void *func,int flag);

typedef void (*key_evnet_func)(int id,int event);
typedef struct key_event_t
{	
	int id;
	int keymark;
	key_evnet_func func;
	struct key_event_t *next;
}*struct_key_event;

extern int scanKeyEvent(void);
extern void setKeyEvent(int key);
extern void main_menu_keyEvent(int id,int event);


