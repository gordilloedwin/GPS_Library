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

#include "GPS.h"

void GPS::init()
{
	this->init(false);
}

void GPS::init(boolean isLeonardo)
{
	baudRate == 0 ? serialNumber = -1 : serialNumber = 0;

	dataReady[0] = false;
	dataReady[1] = false;
	NMEAstring = "";
	timestamp.setTime("220515");
	timestamp.setDate("050282");
	nrw = 'V';
	speed = 0.000;
	heading = 0.000;
	MagVariation = "0.000W";
	altitude = 0.000;
	signalQuality = 0;
	satellitesTracked = 0;
	trustAltitude = false;
	
	switch (this->serialNumber)
	{
	case 0:
		Serial.begin(this->baudRate);
			if (isLeonardo)
			  while(!Serial){} ;  // horrible coding here but easier to understand for me... 
		break;
		
	default:
		NMEAstring = "manual mode selected...";
		break;	
	}//end switch
}

void GPS::resetFlags() {
	dataReady[0]=false, dataReady[1]=false;
}

void GPS::update()
{
	char inChar;
	String NMEASentence = "";
	
	switch (this->serialNumber)
	{
		case 0:
		while (Serial.available())
		{
			char inChar = (char)Serial.read();
			NMEASentence += inChar; 
			if (inChar == '\n' || inChar == '\0' || inChar == '\r')
			{
				this->update(NMEASentence);
				return;
			}
		}
		break;
		
		default:
		NMEAstring = "CHECK SERIAL NUMBER!";											
		break;		
	}// end switch
}// end update

void GPS::update(String sentence)
{
	if (sentence.startsWith("$GPRMC"))
	{
		decodeDataGprmc(sentence);
	}
	else if (sentence.startsWith("$GPGGA"))
	{
		decodeDataGpgga(sentence);
	}
	else
	{
		NMEAstring = "check sentence type... ";
	}
}

void GPS::decodeDataGpgga(String gpgga)
{
	if (!checkCRC(gpgga))
	{
		dataReady[1] = false;
		return;
	}	
	
	int index = 0;
	int divider = 0;
	String temp = "";
	float holder = 0.0;
	
	while (index <= gpgga.length())
	{
		if (gpgga.charAt(index)==',')
		{
			switch (divider)
			{
				case 0:
				NMEAstring = temp;
				break;
				
				case 2:
				latitude.setDegrees(temp.substring(0,2));
				latitude.setMinutes(temp.substring(2));
				break;

				case 3:
				latitude.setAxis(temp.charAt(0));
				break;

				case 4:
				longitude.setDegrees(temp.substring(0,3));
				longitude.setMinutes(temp.substring(3));
				break;

				case 5:
				longitude.setAxis(temp.charAt(0));
				break;
				
				case 6:
				signalQuality = temp.toInt();
				break;
				
				case 7:
				satellitesTracked = temp.toInt();
				satellitesTracked > 2 ? dataReady[1]=true : dataReady[1]=false;
				break;
				
				case 9:
				altitude = temp.toFloat();
				break;
				
				case 12:
				temp=="" ? trustAltitude=false : trustAltitude=true;
				break;
				
				default: //dump temporary content...
				;
			}//end switch 
			temp = "";
			divider++;
		}
		else if ( gpgga.charAt(index) != ' ' )
		{
			// skip..
		}
		else
		{
			temp += gpgga.charAt(index);
		}//end else

		index++;
	
		
	}// end while	
}

void GPS::decodeDataGprmc(String gprmc)
{
	if (!checkCRC(gprmc))
	{
		dataReady[0] = false;
		return;
	}

	int index = 0;
	int divider = 0;
	String temp = "";
	
	float holder = 0.0;

	while (index <= gprmc.length())
	{
		if (gprmc.charAt(index) == ',')
		{
			switch (divider)
			{
				case 0:
				NMEAstring = temp;
				break;

				case 1:
				this->timestamp.setTime(temp);
				break;

				case 2:
				nrw = temp.charAt(0);
				if ( nrw == 'A' )
				dataReady[0] = true;
				else
				dataReady[0] = false;
				break;

				case 7:
				speed = temp.toFloat();
				break;
				
				case 8:
				heading = temp.toFloat();
				break;
				
				case 9:
				timestamp.setDate(temp);
				break;
				
				case 10:
				MagVariation = temp;				
				break;
				
				default: //dump temp content
				;
			}//end switch
			divider++;
			temp = "";
		}//if comma
		else if ( gprmc.charAt(index) != ' ' )
		{
			// skip..
		}
		else
		{
			temp += gprmc.charAt(index);	
		}//end else

		index++;
	}// end while
}

boolean GPS::dataIsReady() {
	return (dataReady[0] && dataReady[1] ? true : false);
}

String GPS::getNmeaSentenceName() {
	return NMEAstring;
}

int GPS::getHour() {
	return timestamp.getHour();
}

int GPS::getMinute() {
	return timestamp.getMinutes();
}

int GPS::getSeconds() {
	return timestamp.getSeconds();
}

int GPS::getDay() {
	return timestamp.getDay();
}

int GPS::getMonth() {
	return timestamp.getMonth();
}

int GPS::getYear() {
	return timestamp.getYear();
}

char GPS::getNavReceiverWarn() {
	return nrw;
}

String GPS::getTimeUTC() {
	return timestamp.getUTCTime();
}

String GPS::getDateUTC(boolean USFormat) {
	return timestamp.getUTCDate(USFormat);
}

String GPS::getTimeLocal() {
	return timestamp.getLocalTime(longitude.getDegrees());
}

String GPS::getDateLocal(boolean USFormat) {
	return timestamp.getLocalDate(longitude.getDegrees(), USFormat);
}

String GPS::getLatitudeS1() {
	return latitude.getSphericalFormat1();
}

String GPS::getLongitudeS1() {
	return longitude.getSphericalFormat1();
}

String GPS::getLatitudeS2() {
	return latitude.getSphericalFormat2();
}

String GPS::getLongitudeS2() {
	return longitude.getSphericalFormat2();
}

float GPS::getLatitude() {
	return latitude.getDecimalFormat();
}

float GPS::getLongitude() {
	return longitude.getDecimalFormat();
}

char GPS::getEquator() {
	return latitude.getAxis();
}

char GPS::getMeridian() {
	return longitude.getAxis();
}

boolean GPS::suspectAltitude() {
	return trustAltitude;
}

float GPS::getAltitude() {
	return altitude;
}

int GPS::getSignalQuality() {
	return signalQuality;
}

int GPS::getsatellitesTracked() {
	return satellitesTracked;
}

float GPS::getSpeed() {
	return (speed *= 1.852);
}

float GPS::getSpeedKph() {
	return speed;
}

float GPS::getSpeedMph() {
	return (speed *= 1.1507);
}

float GPS::getCurrentHeading() {
	return heading;
}

String GPS::getMagneticVariation() {
	return MagVariation;
}

boolean GPS::checkCRC(String toCheck)
{
	if (toCheck.length() >= 119)
	{
		return false;
	}
	char crcchecksum[5];
	char data[120];
	char buffer[10];

	toCheck.substring(toCheck.length() - 4, toCheck.length()).toCharArray(buffer, 3);
	toCheck.toCharArray(data, toCheck.length());
	
	char *datapointer = &data[1];
	char checksum = 0;
	
	/* Loop through entire string, XORing each character to the next */
	while ( *datapointer != '*' )
	{
		checksum ^= *datapointer;
		datapointer++;
		if (*datapointer == NULL)
			break;
	}
	
	/* Parse out the checksum in ASCII hex nybbles */
	sprintf(crcchecksum, "%X", checksum);

	if (strcasecmp(crcchecksum, buffer) == 0)
	{
		memset(crcchecksum, NULL, 5);
		memset(data, NULL, 120);
		return true;
	}
	else
	{ 
		memset(crcchecksum, NULL, 5);
		memset(data, NULL, 120);
		return false;
	}
}

//GPS GPSbody;

