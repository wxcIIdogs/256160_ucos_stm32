#ifndef __COMMON__
#define __COMMON__
#include "stm32f10x.h"



#define EARTH_RADIUS  6378137.0

#ifndef _PI
#define _PI 3.1415926535897932
#endif
#ifndef PI
#define PI 3.1415926535897932
#endif

#define	MAX_ACTIVE_SATELLITE_COUNT		12
#define MAX_SATELLITE_COUNT		36
#define MAX_GNSS_COUNT  3	
typedef	long	time_t;

typedef struct _GPS_POINT
{
	double		latitude;
	double		longitude;
} GPS_POINT;

typedef struct _GPS_METERING_DATA
{
	double		Area;             //面积
	double		PeriMeter;        //周长
	double		Distance;         //距离起点
	double    EtherDis;					//土方量
	double    runArea;					//走过的面积
	double	  runEthdis;        //走过的地方的土方量
	
	
	
	double maxLatitude;
	double maxLongitude;
	double minLatitude;
	double minLongitude;
	double startLatitude;
	double startLongitude;
	double endLatitude;
	double endLongitude;

    //GPS_POINT		StartPt;
    GPS_POINT		LastPt;			// 在定位状态下捕获的最后一个点
    GPS_POINT		BasePt;			// 起点
    GPS_POINT		WayPt;				// 面积计算参考点, 采用当前点以及初始点等三个点来计算一个三角型的面积
    GPS_POINT		WayPtForPeriMeter;	// 周长计算参考点
	double altitude;
	time_t		utcStart;

	unsigned short	bMetering;
	unsigned char		bInited;
	unsigned char		bHasWayPt;

	unsigned int		dwLogPtCount;
//	FS_HANDLE pLogFile;
} GPS_METERING;





typedef struct _SATELLITE_INFO
{
	unsigned char	PRN_Code;
	unsigned char	Active;
	unsigned char	Elevation;
	unsigned char	SNR;
	unsigned int	Azimuth;

}SATELLITE_INFO;


typedef enum _FIX_STATE
{
	NO_SIGNAL	= 0,
	FIX_2D		= 1,
	FIX_3D_20_up= 2,
	FIX_3D_20	= 3,
	FIX_3D_14	= 4,
	FIX_3D_10	= 5,
	UNKOWN_FIX_STATE	= 0xFF,
} FIX_STATE;
typedef struct _GPS_STATUS
{
	time_t		utc;
	double		latitude;
	double		longitude;
	double		altitude;
	double		base_latitude;
	double		base_longitude;
	double		base_altitude;
	double		speed;
	double		vertical_speed;
	double		historySpeed;
	double		azimuth;
	double		hdop;
	double		pdop;
	double		vdop;

	FIX_STATE	state;
//	U8 					fix;
	unsigned char       _35Count;
	unsigned char       _38Count;
	unsigned char       _40Count;
	unsigned char		GnssCount;
	unsigned char		GnssType[MAX_GNSS_COUNT];
	unsigned short		SatsInViewCount[MAX_GNSS_COUNT+1];
	unsigned short		bInfoUsing[MAX_GNSS_COUNT+1];
	SATELLITE_INFO	SatelliteInfo[MAX_GNSS_COUNT+1][MAX_SATELLITE_COUNT];

}GPS_STATUS;
typedef enum _WORKER_MODE {
    NO_MODE = 0,
    HAND_WORK_MODE,
    AUTO_WORK_MODE,
    AUTO_MAN_MODE,
} WORKER_MODE;

typedef enum _SETTING_STATUS{
    NO_SETTING = 0,
    SETTING_READY = 1,
    DOING_SETTING = 2,
    SETTING_DONE = 3,
} SETTING_STATUS;

typedef enum _MOTOR_CONTROL{
    NO_CONTROL = 0,
    MIDDLE_CONTROL,
    LOWER_CONTROL,
    RISE_CONTROL,
} MOTOR_CONTROL;
typedef enum _MEASURING_STATUS{
    NO_MEASURING = 0,		
    MEASURING_READY = 1,
	MEASURING_BEGIN = 2,
	MEASURING_HIGH = 3,
	MEASURING_END_HIGH = 4,
	MEASURING_ROISE = 5,
	MEASURING_END_ROISE = 6,
    MEASURING_WORKING = 7,
    MEASURING_ENDING = 8,
	MEASURING_ENDING_END = 9,
} MEASURING_STATUS;

#define SOLQ_NONE 0   /* solution status: no solution */
#define SOLQ_FIX 1    /* solution status: fix */
#define SOLQ_FLOAT 2  /* solution status: float */
#define SOLQ_SBAS 3   /* solution status: SBAS */
#define SOLQ_DGPS 4   /* solution status: DGPS/DGNSS */
#define SOLQ_SINGLE 5 /* solution status: single */
#define SOLQ_PPP 6    /* solution status: PPP */
#define SOLQ_DR 7     /* solution status: dead reconing */
#define MAXSOLQ 7     /* max number of solution status */




#endif




