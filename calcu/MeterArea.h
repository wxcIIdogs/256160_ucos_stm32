#ifndef __METERAREA__
#define __METERAREA__
#include "math.h"
#include "common.h"
extern GPS_STATUS		GPS_Status;
extern GPS_METERING	GPS_MeteringData;
extern void initMeter(void);
extern void insertDataToMeter(double lat,double lot ,double speed,char fixstate);
extern void GetEtherDistance(double nowH,double aveH,double speed,double widgth);

extern double GetDistance(double lat1, double lng1, double lat2, double lng2);
extern void GPS_StopMetering(void);
#endif


