#ifndef __COMMON_H__
#define __COMMON_H__
#include  "stm32f10x.h"

typedef enum
{
	KEY_ENTER = 0x01,
	KEY_TOP  = 0x02,
	KEY_BOTTON = 0x04,
	KEY_LEFT = 0x08,
	KEY_RIGHT = 0x10,
	KEY_CANCEL = 0x20,
}enum_KEY_EVENT;


//flash的数据
typedef struct flash_info
{

}FlashInfo;

//存放一些系统数据
typedef struct inode
{
	
}Inode;

typedef struct list_pro
{
	struct face_info *pro;
	struct face_info *next;
}*list_t;


//界面信息， 用来维护一个root和一个当前节点
typedef void(*facefunc)(struct inode *info , struct face_info *node);
typedef struct face_info
{
	int id;	
	char ishead;
	char *title;
	list_t list;
	facefunc func;
	void *data;
}structFaceInfo;



//菜单的列表
typedef struct _menu
{
	int id;
	char * title;
	char type;
	double num;
	char type;
	char x;
	char y;
	char select;
}structMenu;







extern Inode g_node;
extern FlashInfo g_initFlashStruct;
extern structFaceInfo g_currentFace;
extern structFaceInfo g_headFace;

#endif

