#ifndef __COMMON_H__
#define __COMMON_H__
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "minmea.h"
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


//flash鐨勬暟鎹?
typedef struct flash_info
{

	//度量单位
	double areaunit;
	double lengthunit;
	double volumeunit;
	//电台频道
	double MaxChannel;
	double channel;
	double MinChannel;
	//铲斗宽度
	double bucketwidgth;//BUCKETWIDGTH
	
	double antlocal;
	
	double timesetlocal;
	
	double timesetXia;
	
	double langselect;
	
	double dataCount;
	
	double dataAdress;
	
}FlashInfo;

typedef struct plane
{	

	int direc;	
}structPlane;

typedef struct xieMenu
{
	double startH;
	double endH;
	double stat2endDiffH;
	double stat2endDiffdis;
	double stat2endDiffpitch;	
	int direc;
}xiePlan;
typedef struct parcelsurvey
{	
	double area;
	double maxH;
	double averH;
	double minH;
	double PeriMeter;		
	double EtherDis;	
}PareclSurvey;
//瀛樻斁涓�浜涚郴缁熸暟鎹?


struct nodenmea_time {
    int hours;
    int minutes;
    int seconds;
    int microseconds;
};
struct nodenmea_date {
    int day;
    int month;
    int year;
};

typedef struct inode
{
	struct nodenmea_time time;
	struct nodenmea_date date;
	int stat;
	int delayTime;
	int Channel;
	int fixMode;
	double lat;
	double lot;
	double nowH;
	double aimH;
	double Distance[2];
	double speed;
	double diffH;
	int action;
	int workMode;
	int autoMode;
	int dataType;	
	int isConnect;
	FlashInfo *flashData;
	struct parcelsurvey *parcelData;
	structPlane *PlaneData;
	xiePlan *xieData; 
	void *data;	
}Inode;

typedef struct list_pro
{
	struct face_info *pro;
	struct face_info *next;
}*list_t;

//鑿滃崟鐨勫垪琛?
typedef struct _menu
{
	int id;
	char * title;
	char data[30];
	double num;
	char x;
	char y;
	char select;
}structMenu;

typedef enum 
{
	none = -1,
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


//鐣岄潰淇℃伅锛?鐢ㄦ潵缁存姢涓�涓猺oot鍜屼竴涓綋鍓嶈妭鐐?
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

//测量数据存储结构体
typedef struct _structCeData
{
	double id;
	double zhouc;
	double dhigh;
	double area;
	int year;
	int mon;	
	int day;
	int hour;
	int min;
	
	double tufl;
	double dis[2];
	double high;
	double low;
}structCeData;
#define ceDataStartAdress  0x08060800
#define ceDataStartAdressInfo  0x08060000
typedef struct _structCeDatainfo
{
	uint32_t startAdress;
	uint32_t count;
}structCeDataInfo;


typedef enum 
{
	BU_NO_CONTROL = 0,
	BU_CANCEL_CONTROL = 1,
	BU_DOWN_CONTROL = 2,
	BU_RAISE_CONTROL = 3,
}enumBUCK_STATUS;

typedef enum
{
	HAND_MODE = 0,
	AUTO_MODE = 1,
	AUTO_HAND_MODE = 2,
}enumAUTO_MODE;
typedef enum
{
	CLOSE_WORK = 0,
	SETUP_WORK = 1,
	WORKING = 2,
}enumWorkMode;

typedef enum
{
	VERSION = 0,
	RADIO = 1,
	CONTROL = 2,
	MOED = 3,
	STATUS = 4,
	GRADER = 5,
	MACH_OK = 6,
	MACH_ERROR = 7,
	MACH_UNLINK = 8,
}enumMACH_TYPE;



extern structFaceInfo g_arrayface[];
extern Inode g_node;
extern FlashInfo g_initFlashStruct;
extern structFaceInfo *g_currentFace;
extern structFaceInfo g_headFace;
extern structCeDataInfo g_ceDataFlash;

//测量数据
extern u8 g_area_unit[6];
extern u8 g_len_unit[6];
extern u8 g_tiji_unit[6];

extern double g_area_unit_num ;
extern double g_len_unit_num;
extern double g_volue_unit_num;
/*****************************/




#define StartAdress   0x08058000
extern volatile FLASH_Status wxcFLASHStatus;

//
extern GPS_DATA gps_data;




extern void main_menu_keyEvent(int id,int event);
extern void draw_menu(structFaceInfo *info);
extern void draw_menu_data(structFaceInfo *info);

extern void draw_menu_cedata(structFaceInfo *info,int index,structCeData *data);
extern int getLocalId(void);
extern void setMenuLen(int len);
extern int getEndflag(void);
extern int getEvent(void);

extern void draw_line_y(int y);

extern void draw_title(void );

extern FACE_ENUM Draw_face(int index);
extern void setLocalId(int id);

extern void draw_set_menu(u8 temp[][30],int len);
extern void draw_set_num_menu(char * num,int flag ,int x,int y,int addindex);
extern void draw_show_num_menu(int index,char num[][10],int addindex,unsigned char arrSet[][30],int len);


extern void draw_set_low_title_menu(u8 *title,int x,int y);
extern void draw_StatTitle_menu(int gps,int beid,int glonass);
extern void draw_stat_stren_num_menu(int index,int len,int x,int y);
extern void draw_title_data_menu(u8 *data,int x,int y);
extern void setReturnFACE_ENUM(int id);
extern FACE_ENUM getReturnFACE_ENUM(void);
extern void draw_clean_show(int y);
extern void readFlashStruct(void);
extern void writeFlashStruct(void);
extern void incodeing_return_ok(void);
extern void setUnit(void);


#endif

