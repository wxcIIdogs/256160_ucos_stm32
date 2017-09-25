//#include "keyevent.h"
#include "commom.h"
#include "led.h"
#include "includes.h"
struct key_event_t head = {
	.id = 0,
	.func = NULL,
	.next = NULL,
};
static struct_key_event localPoint = &head;


void register_key_event(int id,void *func,int flag)
{
	localPoint->func = (key_evnet_func)func;
	localPoint->id = id;
	localPoint->keymark = flag;
}

void sendEventforID(int id,int key)
{
	struct_key_event structTemp = localPoint;	
	structTemp->func(id,key);
}
void sendKeyEventToFace(int key)
{

	int id = g_currentFace->id;
	sendEventforID(id,key);
}
int scanKeyEvent()
{
	int key = 0;
	int temp = 0;
	struct_key_event structTemp = localPoint;		
	OS_ERR err;
	key = GETKEYEVENT;
	temp = key;
	
	while(temp != 0)
	{
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);					
		temp = GETKEYEVENT;
	}
	if(structTemp->keymark & key)
	{
		main_menu_keyEvent(0,key);
	}	
	else
	{
		key = 0;
	}
	return key;
}

void setKeyEvent(int key)
{
	if(key == 0)
	{
		return ;
	}
	sendKeyEventToFace(key);
}














