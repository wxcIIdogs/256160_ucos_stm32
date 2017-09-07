#include "commom.h"
#include "256160.h"
#include "drawFace.h"
#include "includes.h"
static int isEnd = 0;
static int localId = 0;
static int menuLen = 0;
void draw_title(structFaceInfo *info)
{
	
}
void draw_menu(structFaceInfo *info)
{
	structMenu *menu = info->menu;
	menuLen = info->len;
	for(int i = 0 ; i < info->len ;i++)
	{
		setBackColor(BACK_WHITE);
		if(i == localId)
		{
			setBackColor(BACK_BLACK);
		}
		setCurrentIndex( menu->x , menu->y);
		printf(menu->title,menu->type,menu->num );
		menu++;
	}
}

void main_menu_keyEvent(int id,int event)
{
	switch(event & KEY_ALL)
	{
		case KEY_ENTER:
			isEnd &= KEY_ENTER;
			break;
		case KEY_TOP:
			localId --;
			break;
		case KEY_BOTTON:
			localId ++;
			break;
		case KEY_LEFT:
			localId -= 3;
			break;
		case KEY_RIGHT:
			localId += 3;
			break;
		case KEY_CANCEL:
			isEnd &= KEY_CANCEL;
			break;
		default : break;
	}
	if(localId < 0)
	{
		localId = menuLen -1;
	}
	localId %= menuLen;		
}

FACE_ENUM draw_main_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title(info);  //显示开头
	}	
	while(1)
	{
		draw_menu(info);
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(isEnd & KEY_CANCEL)
		{
			return MAINMENU;
		}
		if(isEnd & KEY_ENTER)
		{
			break;
		}
	}	
	return info->menu[localId].id;
}









