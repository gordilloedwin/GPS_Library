// GPS.h

#ifndef _GPS_h
#define _GPS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "tCoordinate.h"
#include "tDatetime.h"

#pragma once

class GPS
{
	private:
	int baudRate;
	int serialNumber;
	
	protected:
	boolean dataReady[2];
	String NMEAstring;
	TDatetime timestamp;
	char nrw;
	TCoordinate latitude;
	TCoordinate longitude;
	float altitude;
	float speed;
	float heading;
	String MagVariation;
	int signalQuality;
	int satellitesTracked;
	boolean trustAltitude;
	void decodeDataGprmc(String gprmc);
	void decodeDataGpgga(String gpgga);
	boolean checkCRC(String toCheck);	

	public:
	GPS(int Baud) : baudRate(Baud), serialNumber(0) {};
	void init();
	void init(boolean isLeonardo);
	void update();
	void update(String sentence);
	void resetFlags();
	boolean dataIsReady();
	String getNmeaSentenceName();
	char getNavReceiverWarn();
	int getHour();
	int getMinute();
	int getSeconds();
	int getDay();
	int getMonth();
	int getYear();
	String getTimeUTC();
	String getTimeLocal();
	String getDateUTC(boolean USFormat);
	String getDateLocal(boolean USFormat); //this is still experimental, and uses simplified math and original longitudinal divisions of earth, I take no liability if doesn't work for you...
	String getLatitudeS1();
	String getLongitudeS1();
	String getLatitudeS2();
	String getLongitudeS2();	
	float getLatitude();
	float getLongitude();
	char getMeridian();
	char getEquator();
	boolean suspectAltitude();
	float getAltitude();
	int getSignalQuality();
	int getsatellitesTracked();
	float getSpeed();
	float getSpeedMph();
	float getSpeedKph();
	float getCurrentHeading();
	String getMagneticVariation();
};

//extern GPS GPSbody;

#endif

