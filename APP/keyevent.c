#include "keyevent.h"
#include "commom.h"
#include "led.h"

struct key_event head = {
	.id = 0,
	.func = NULL,
	.next = NULL,
};
static struct_key_event localPoint = &head;



void register_key_event(int id,void *func,int flag)
{
	struct_key_event temp = (struct_key_event)malloc(sizeof(struct key_event));
	temp->func = (key_evnet_func)func;
	temp->id = id;
	temp->keymark = flag;
	localPoint->next = temp;
	localPoint = temp;
	localPoint->next = NULL;
}
struct_key_event getFaceforId(int id)
{
	struct_key_event temp = &head;
	while(temp->next != NULL)
	{
		if(temp->id == id)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void sendEventforID(int id,int key)
{
	struct_key_event temp = getFaceforId(id);
	if(temp->keymark & key)
	{
		temp->func(id,key);
	}
}
void sendKeyEventToFace(int key)
{
	if(key == 0)
		return;
	//从全局宏获取ID
	int id = g_currentFace->id;
	sendEventforID(id,key);
}
void scanKeyEvent()
{
	int key = 0;
	key = GETKEYEVENT;
	sendKeyEventToFace(key);
}















