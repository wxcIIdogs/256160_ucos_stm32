#include "commom.h"
#include "256160.h"
static struct list_pro list = {0};

structFaceInfo g_headFace = {
	0,
	.list = &list,
	0,
};
structFaceInfo *g_currentFace = &g_headFace;
FlashInfo g_initFlashStruct = {0};
Inode g_node = {0};


static int isEnd = 0;
static int localId = 0;
static int menuLen = 0;

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
	return isEnd;
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
void draw_menu_cedata(structFaceInfo *info,int index,structCeData *data)
{
	structMenu *menu = info->menu;
	menuLen = info->len;
	for(int i = 0 ; i < info->len ;i++)
	{
		setCurrentIndex( menu->x , menu->y);
		if(i == 4)
		{
			char print[100] = {0};			
			sprintf(print,"%s%04d-%02d-%02d %02d:%02d",menu->title,data->year,data->mon,data->day,data->hour,data->min );
			printf("%s",print);
			
		}else
		if(i == 7)
		{
			char print[100] = {0};
			sprintf(print,"%s%.2lf/%.2lf",menu->title,data->high,data->low);
			printf("%s",print);
		}
		else
		{
			menu->num = data->id;			
			printf(menu->title,menu->type,menu->num );
		}
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
	int hou = (localNote.time/3600)%24;
	int min = (localNote.time/60)%60;
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
void draw_set_num_menu(double num,int flag ,int x,int y)
{
	setCurrentIndex(x,y);
	if(flag == 1)
	{
		printf("【%.3lfm】",num);	
	}
	else
	{
		printf("%.3lfm",num);	
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


