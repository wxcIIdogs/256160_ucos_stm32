
#include "MeterArea.h"


GPS_METERING GPS_MeteringData  = {0};	//init area struct
GPS_STATUS		GPS_Status = {0};

void GPS_StartMetering(void)
{	
	GPS_MeteringData.bMetering = 1;
}

void GPS_StopMetering(void)
{
	if(GPS_MeteringData.bMetering)
	{
		GPS_MeteringData.bMetering = 0;
	}
}
void GPS_ClearMetering(void)
{
	//LogStr("clear metering");
	GPS_MeteringData.dwLogPtCount = 0;
	GPS_MeteringData.Area = 0.0;
	GPS_MeteringData.PeriMeter = 0.0;
	GPS_MeteringData.bInited = 0;
	GPS_MeteringData.bHasWayPt = 0;	
	GPS_MeteringData.runArea = 0;
	GPS_MeteringData.runEthdis = 0;
	GPS_MeteringData.EtherDis = 0;
	GPS_MeteringData.Distance = 0;	
}
double rad(double d)
{
	return d*_PI/ 180.0;
}
double RRPI(double x)
{
	return (x * _PI * EARTH_RADIUS * EARTH_RADIUS / 360.0); //(pi * R * R)/360
}
double averagerad(double x0, double x1)
{
	return (((double)(x0 + x1)) * _PI / 180.0 / 2.0); //两点平均弧度
}

//计算面积   传入base    第二个，   last
double CalcArea(double lat0, double lng0, double lat1, double lng1, double lat2, double lng2)
{
	double radlng0 = rad(lng0);
	double radlng1 = rad(lng1);
	double radlng2 = rad(lng2);
	double avrageradlat0 = averagerad(lat0, lat1);
	double lng10 = (radlng1 - radlng0) * cos(avrageradlat0);
	double lng20 = (radlng2 - radlng0) * cos(avrageradlat0);
	double area = RRPI(lng10 * (lat2 - lat0) - lng20 * (lat1 - lat0));
	return area;
}
double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double a = radLat1 - radLat2;
	double b = rad(lng1) - rad(lng2);
	double s = 2.0 * asin(sqrt(pow(sin(a/2.0), 2.0) + cos(radLat1)*cos(radLat2)*pow(sin(b/2.0), 2.0)));
	s *= EARTH_RADIUS;
	return s;
}
void GetEtherDistance(double nowH,double aveH,double speed,double widgth)
{
	double diffH = nowH - aveH;
	if(diffH > 0)
	{	//只算挖的土
		double getArea = widgth*(speed*0.1);   //0.1  10hz
		double ethdis = getArea*diffH;
		GPS_MeteringData.runArea += getArea;
		GPS_MeteringData.runEthdis += ethdis;	
		GPS_MeteringData.EtherDis = (GPS_MeteringData.Area/GPS_MeteringData.runArea)*GPS_MeteringData.runEthdis;
	}
}
void GPS_InsertMeteringPoint(double latitude, double longitude, double speed, double hdop)
{
	// 参数赋值
	GPS_MeteringData.dwLogPtCount ++;		
	GPS_MeteringData.LastPt.latitude = latitude;
	GPS_MeteringData.LastPt.longitude = longitude;
	GPS_MeteringData.altitude = GPS_Status.altitude;
	
	if (GPS_MeteringData.bHasWayPt == 0)
	{// 初始化之后的第一个点   三个点开始计算，
		GPS_MeteringData.WayPt = GPS_MeteringData.LastPt;
		GPS_MeteringData.bHasWayPt = 1;
	}	
	else
	{//正常插入
		double ar = CalcArea(GPS_MeteringData.BasePt.latitude, GPS_MeteringData.BasePt.longitude,
		GPS_MeteringData.WayPt.latitude, GPS_MeteringData.WayPt.longitude,				
		GPS_MeteringData.LastPt.latitude, GPS_MeteringData.LastPt.longitude);	
		GPS_MeteringData.Area += ar;		
		GPS_MeteringData.WayPt = GPS_MeteringData.LastPt;
	}
	
	//
	// 计算周长
	//	
	if (1)
	{
		double add = GetDistance(GPS_MeteringData.WayPtForPeriMeter.latitude, GPS_MeteringData.WayPtForPeriMeter.longitude,
			GPS_MeteringData.LastPt.latitude, GPS_MeteringData.LastPt.longitude);			
		if(add > 0.1)
		{
//			gps_data.speed = add/0.1;
			GPS_MeteringData.PeriMeter += add;	
			GPS_MeteringData.WayPtForPeriMeter= GPS_MeteringData.LastPt;
		}
	}
	
	if(GPS_MeteringData.maxLatitude < latitude)
	{
		GPS_MeteringData.maxLatitude = latitude;
	}
	else if(GPS_MeteringData.minLatitude > latitude)
	{
		GPS_MeteringData.minLatitude = latitude;
	}
	if(GPS_MeteringData.maxLongitude < longitude)
	{
		GPS_MeteringData.maxLongitude = longitude;
	}
	else if(GPS_MeteringData.minLongitude > longitude)
	{
		GPS_MeteringData.minLongitude = longitude;
	}
	GPS_MeteringData.endLatitude = latitude;
	GPS_MeteringData.endLongitude = longitude;
}

//初始化测量函数，参数    
void GPS_InitMeteringData(double latitude, double longitude, time_t utc)
{
	GPS_MeteringData.LastPt.latitude = latitude;
	GPS_MeteringData.LastPt.longitude = longitude;
	GPS_MeteringData.BasePt = GPS_MeteringData.LastPt;
	GPS_MeteringData.WayPtForPeriMeter = GPS_MeteringData.LastPt;
	GPS_MeteringData.utcStart = utc;
	GPS_MeteringData.bInited = 1;

	GPS_MeteringData.maxLatitude = latitude;
	GPS_MeteringData.minLatitude = latitude;
	GPS_MeteringData.maxLongitude = longitude;
	GPS_MeteringData.minLongitude = longitude;

	GPS_MeteringData.startLatitude = latitude;
	GPS_MeteringData.endLatitude = latitude;
	GPS_MeteringData.startLongitude = longitude;
	GPS_MeteringData.endLongitude = longitude;
	GPS_MeteringData.altitude = GPS_Status.altitude;
}
//测量面积，同步更新数据
void GPS_UpdateMeteringData()
{
	// 面积测量
	if (GPS_MeteringData.bMetering && GPS_Status.state == SOLQ_FIX)  // 
	{//开始测量
		if (!GPS_MeteringData.bInited)
		{//没有初始化
			GPS_InitMeteringData(GPS_Status.latitude, GPS_Status.longitude, GPS_Status.utc);
		}
		else
		{//已经有数据了
			GPS_InsertMeteringPoint(GPS_Status.latitude, GPS_Status.longitude, GPS_Status.speed, GPS_Status.hdop);
		}
	}
}

void initMeter()
{	
	GPS_StopMetering();
	GPS_ClearMetering();
	GPS_StartMetering();
	// init 周长测量
	GPS_Status.hdop = 0.7;	
}
void insertDataToMeter(double lat,double lot,double speed,char fixstate)
{		
	GPS_Status.latitude = lat;
	GPS_Status.longitude = lot;

	GPS_Status.speed = speed;
	GPS_Status.state = fixstate;
	GPS_UpdateMeteringData();
}


