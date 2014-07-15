/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by Edwin Gordillo  (IPN, Mexico)
 ehernandezg0708@alumno.ipn.mx  
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tDatetime.h"
#include <inttypes.h>

void TDatetime::setTime(String inTime)
{
	hour = (uint_fast8_t) inTime.substring(0,2).toInt();
	minute = (uint_fast8_t) inTime.substring(2,4).toInt();
	second = (uint_fast8_t) inTime.substring(4,6).toInt();
}

void TDatetime::setDate(String inDate)
{
	month = (uint_fast8_t) inDate.substring(0,2).toInt();
	day = (uint_fast8_t) inDate.substring(2,4).toInt();
	year = (uint_fast16_t) inDate.substring(4,6).toInt();
	year += 2000;	
}


int TDatetime::getHour() {
	return hour;
}

int TDatetime::getMinutes() {
	return minute;
}

int TDatetime::getSeconds() {
	return second;
}

int TDatetime::getDay() {
	return day;
}

int TDatetime::getMonth() {
	return month;
}

int TDatetime::getYear() {
	return year;
}

String TDatetime::getUTCTime()
{
	String timest = (String)hour;
	timest += ":";
	timest += (String)minute;
	timest += ":";
	timest += (String)second;
	return timest;
}

String TDatetime::getUTCDate(boolean USFormat)
{
	String timest = "";
	
	if (USFormat)
	{
		timest = (String)month + "/" + (String)day;
	}
	else
	{
		timest = (String)day + "/" + (String)month;
	}
		
	timest+="/"+(String)year;
	return timest;	
}

String TDatetime::getLocalTime(float tDeg)
{
	uint_fast8_t localeGMT = 0;
	String timest = "";
	
	localeGMT = (uint_fast8_t)(tDeg/15.00);
	hour += localeGMT;
	hour < 0 ? hour+=12 : 0 ;
	hour > 23 ? hour-=12 : 0 ;
	
	timest = (String)hour;
	timest += ":";
	timest += (String)minute;
	timest += ":";
	timest += (String)second;
	return timest;
}

String TDatetime::getLocalDate(float tDeg, boolean USFormat)
{
	if (tDeg >= 0)
	{ 
		return getUTCDate(USFormat);
	}
	else
	{
		String timest = "";
		
		if (USFormat)
		{
			timest = (String)month + "/" + (String)(day-1);
		}
		else
		{
			timest = (String)(day-1) + "/" + (String)month;
		}
		
		timest+="/"+(String)year;
		return timest;
	}
	
}


//TDatetime TDatetime;

