#include "commom.h"
#include "256160.h"
#include "calcuFace.h"
static struct list_pro list = {0};

structFaceInfo g_headFace = {
	0,
	.list = &list,
	0,
};
structFaceInfo *g_currentFace = &g_headFace;
FlashInfo g_initFlashStruct = {0};
Inode g_node = {0};
structCeDataInfo g_ceDataFlash={0};

const char wxcbuff[2048]          __attribute__((at(StartAdress)))   = {0};
const char wxcCebuff[2048]          __attribute__((at(ceDataStartAdressInfo)))   = {0};



static int isEnd = 0;
static int localId = 0;
static int menuLen = 0;
static int g_event = 0;
int getLocalId()
{
	return localId;
}
void setLocalId(int id)
{
	localId = id;
}
void setMenuLen(int len)
{
	menuLen = len;
}
int getEndflag()
{
	int temp = isEnd;	
	isEnd = 0;
	return temp;
}
int getEvent()
{
	int event = g_event;
	g_event = 0;
	return event;
}
void draw_menu(structFaceInfo *info)
{
	structMenu *menu = info->menu;
	menuLen = info->len;
	for(int i = 0 ; i < info->len ;i++)
	{
		setCurrentIndex( menu->x , menu->y);
		printf("%d.",i+1);
		if(i == localId)
		{
			setBackColor(BACK_BLACK);
		}
		printf(menu->title);
		menu++;
		setBackColor(BACK_WHITE);
	}
}
void draw_menu_data(structFaceInfo *info)
{
	structMenu *menu = info->menu;
	for(int i = 0 ; i < info->len ;i++)
	{
		setCurrentIndex( menu->x+strlen(menu->title)*8+5 , menu->y);	
		printf("%s",menu->data);
		menu++;
	}
}
void main_menu_keyEvent(int id,int event)
{
	g_event = event;
	switch(event & KEY_ALL)
	{
		case KEY_ENTER:
			isEnd &= KEY_ENTER;
			break;
		case KEY_TOP: 
			isEnd &= KEY_TOP;
			localId --;
			break;
		case KEY_BOTTON:
			isEnd &= KEY_BOTTON;
			localId ++;
			break;
		case KEY_LEFT:
			isEnd &= KEY_LEFT;
			localId -= (menuLen+1)/2;
			break;
		case KEY_RIGHT:
			isEnd &= KEY_RIGHT;
			localId += (menuLen+1)/2;
			break;
		case KEY_CANCEL:
			isEnd &= KEY_CANCEL;
			localId = 0;
			menuLen = 0;
			break;
		default : break;
	}
	if(localId < 0)
	{
		localId = menuLen -1;
	}
	localId %= menuLen;
	//sendmem
}






char fixModeArray[][5] = {"未定","差分","浮点","什么","啥事","单点"};


void _draw_title()
{
	int x = 1,y = 1;
	Inode localNote = g_node;
	
	setCurrentIndex(x,y);
	printf("卫星:%02d",localNote.stat);	
	x += 58;
	setCurrentIndex(x,y);
	printf("%s",fixModeArray[localNote.fixMode]);

	x += 38;
	setCurrentIndex(x,y);
	int hou = localNote.time.hours;
	int min = localNote.time.minutes;
	printf("%02d:%02d",hou,min);

	x += 48;
	setCurrentIndex(x,y);
	printf("频道:%d",localNote.Channel);

	x+=50;
	setCurrentIndex(x,y);
	printf("延时:%02d",localNote.delayTime);

	draw_line_y(3);
	
	draw_line_y(6);

}


void draw_title()
{
	_draw_title();
}

void draw_set_menu(u8 temp[][30],int len)
{
	int x = 1,y = 7;
	
	for(int i = 0; i < len ; i ++)
	{
		setCurrentIndex(x,y);
		printf("%s",temp[i]);
		y += 2;
	}

}
void draw_show_num_menu(int index,char num[][10],int addindex,uchar arrSet[][30],int len)
{
	int x = 0;
	int y = 7;
	for(int i = 0 ;i < len; i ++)
	{	
		x = strlen((char *)arrSet[i])*8 + 5;
		if(index == i)
			draw_set_num_menu(num[i], 1,x,y,addindex);
		else
			draw_set_num_menu(num[i], 0,x,y,addindex);
		y += 2;
	}
}

void draw_set_num_menu(char * num,int flag ,int x,int y,int addindex)
{
	setCurrentIndex(x,y);
	disp_clean(x,y,7,2);
	if(flag == 1)
	{
		printf("【");
		for(int i = 0;i < strlen(num) ; i++)		
		{
			if(addindex == i)
			{
				setBackColor(BACK_BLACK);
			}
			printf("%c",num[i]);
			setBackColor(BACK_WHITE);
		}
		printf("】");
	}
	else
	{
		printf("%s",num);	
	}
}

void draw_set_low_title_menu(u8 *title,int x,int y)
{
	setCurrentIndex(x,y);
	printf("%s",title);
}
void draw_StatTitle_menu(int gps,int beid,int glonass)
{
	int x = 1;
	int y = 1;
	setCurrentIndex(x,y);
	printf("GPS:%d",gps);
	x += 60;
	setCurrentIndex(x,y);
	printf("beid:%d",beid);	
	x+= 60;
	setCurrentIndex(x,y);
	printf("Glonass:%d",glonass);		
}

void draw_stat_stren_num_menu(int index,int len,int x,int y)
{
	setCurrentIndex(x,y);
	printf("%02d",index);
	draw_line_stat_sign(len);
}
void draw_title_data_menu(u8 *data,int x,int y)
{
	setCurrentIndex(x,y);
	printf("%s",data);
}

FACE_ENUM g_return_FACE_ENUM = faceNull;
void setReturnFACE_ENUM(int id)
{
	if(g_return_FACE_ENUM == faceNull)
	{
		g_return_FACE_ENUM = (FACE_ENUM)(id -1);
	}
}
FACE_ENUM getReturnFACE_ENUM()
{
	FACE_ENUM temp = g_return_FACE_ENUM; 
	g_return_FACE_ENUM = faceNull;
	return temp;
}


void draw_clean_show(int y)
{
	disp_clean(1,y,16,21-y);
}

void incodeing_return_ok()
{
	char buff[100];
	sprintf(buff,"$ICEGPS,OK");
	sendIcegpsData(buff);
}

