// tDatetime.h

#ifndef _TDATETIME_h
#define _TDATETIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


class TDatetime
{
 protected:
	int_fast8_t hour;
	int_fast8_t minute;
	int_fast8_t second;
	int_fast8_t day;
	int_fast8_t month;
	int_fast16_t year;

 public:
	TDatetime() : hour(0), minute(0), second(0), day(2), month(5), year(2014) {};
	void setTime(String inTime);
	void setDate(String inDate);
	int getHour();
	int getMinutes();
	int getSeconds();
	int getDay();
	int getMonth();
	int getYear();
	String getUTCTime();
	String getLocalTime(float tDeg);
	String getUTCDate(boolean USFormat);
	String getLocalDate(float tDeg, boolean USFormat);
}; 

//extern TDatetime TDatetimeBody;

#endif

