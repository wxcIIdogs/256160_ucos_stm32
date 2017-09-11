#ifndef __COMMON_H__
#define __COMMON_H__
#include  "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define BACK_WHITE   1
#define BACK_BLACK   0


#define SOLQ_NONE 0   /* solution status: no solution */
#define SOLQ_FIX 1    /* solution status: fix */
#define SOLQ_FLOAT 2  /* solution status: float */
#define SOLQ_SBAS 3   /* solution status: SBAS */
#define SOLQ_DGPS 4   /* solution status: DGPS/DGNSS */
#define SOLQ_SINGLE 5 /* solution status: single */
#define SOLQ_PPP 6    /* solution status: PPP */
#define SOLQ_DR 7     /* solution status: dead reconing */
#define MAXSOLQ 7     /* max number of solution status */

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
	long time;
	int stat;
	int delayTime;
	int Channel;
	int fixMode;	
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


typedef struct _structCeData
{
	double id;
	double zhouc;
	double dhigh;
	
	int year;
	int mon;	
	int day;
	int hour;
	int min;
	
	double tufl;
	double dis;
	double high;
	double low;
}structCeData;



extern structFaceInfo g_arrayface[];
extern Inode g_node;
extern FlashInfo g_initFlashStruct;
extern structFaceInfo *g_currentFace;
extern structFaceInfo g_headFace;

extern void main_menu_keyEvent(int id,int event);
extern void draw_menu(structFaceInfo *info);
extern void draw_menu_cedata(structFaceInfo *info,int index,structCeData *data);
extern int getLocalId(void);
extern void setMenuLen(int len);
extern int getEndflag(void);
extern void draw_line_y(int y);

extern void draw_title(void );

extern FACE_ENUM Draw_face(int index);
extern void setLocalId(int id);

extern void draw_set_menu(u8 temp[][30],int len);
extern void draw_set_num_menu(double num,int flag ,int x,int y);
extern void draw_set_low_title_menu(u8 *title,int x,int y);
extern void draw_StatTitle_menu(int gps,int beid,int glonass);
extern void draw_stat_stren_num_menu(int index,int len,int x,int y);

#endif

