#ifndef __COMMON_H__
#define __COMMON_H__
#include  "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define BACK_WHITE   1
#define BACK_BLACK   0

typedef enum
{
	KEY_ENTER = 0x01,
	KEY_TOP  = 0x02,
	KEY_BOTTON = 0x04,
	KEY_LEFT = 0x08,
	KEY_RIGHT = 0x10,
	KEY_CANCEL = 0x20,
	KEY_ALL = 0x3F,
}enum_KEY_EVENT;


//flash的数据
typedef struct flash_info
{
	void *data;
}FlashInfo;

//存放一些系统数据
typedef struct inode
{
	void *data;
}Inode;

typedef struct list_pro
{
	struct face_info *pro;
	struct face_info *next;
}*list_t;

//菜单的列表
typedef struct _menu
{
	int id;
	char * title;
	char type;
	double num;
	char x;
	char y;
	char select;
}structMenu;

typedef enum 
{
	MAINMENU = 0,
	SYSSETMENU,
	PARCELMENU,
	PANELMENU,
	XIEMENU,
	MEASEMENU = 5,
	SETPANELHIGHT,
	SETXIESTARTHIGH,
	SETXIEENDHIGH,
	STATSIGN,
	UNITMEASURE  = 10,
	BOARDCHANNEL,
	BUCKETWIDGTH,
	ANTLOCAL,
	ROISEDOWNADJ,
	TIMESET = 15,
	LANGSELECT,
	CLEANMEM,
	ABOUT,
	faceNull = 255,
}FACE_ENUM;


//界面信息， 用来维护一个root和一个当前节点
typedef FACE_ENUM (*facefunc)(struct inode *info , struct face_info *node);
typedef struct face_info
{
	int id;	
	char ishead;
	char *title;
	list_t list;
	facefunc func;
	structMenu *menu;
	int len;
	void *data;
}structFaceInfo;





extern structFaceInfo g_arrayface[];
extern Inode g_node;
extern FlashInfo g_initFlashStruct;
extern structFaceInfo *g_currentFace;
extern structFaceInfo g_headFace;


extern void register_key_event(int id,void *func,int flag);
extern FACE_ENUM Draw_face(int index);
FACE_ENUM draw_main_face(Inode *node, structFaceInfo *info);

#endif

