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

#include "GPS_M.h"

void GPS_M::init()
{
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
	
	switch (this->serialSelect)
	{
	case 0:
		Serial.begin(this->baudRate);
		break;
	
	case 1:
		Serial1.begin(this->baudRate);
		break;
		
	case 2:
		Serial2.begin(this->baudRate);	
		break;
		
	case 3:
		Serial3.begin(this->baudRate);
		break;
		
	default:
		NMEAstring = "manual feeding mode selected...";
		break;	
	}//end switch
}

void GPS_M::update()
{
	char inChar;
	String NMEASentence = "";
	
	switch (this->serialSelect)
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
		
		case 1:
		while (Serial1.available())
		{
			char inChar = (char)Serial1.read();
			NMEASentence += inChar;
			if (inChar == '\n' || inChar == '\0' || inChar == '\r')
			{
				this->update(NMEASentence);
				return;
			}
		}
		break;

		case 2:
		while (Serial2.available())
		{
			char inChar = (char)Serial2.read();
			NMEASentence += inChar;
			if (inChar == '\n' || inChar == '\0' || inChar == '\r')
			{
				this->update(NMEASentence);
				return;
			}
		}
		break;
		
		case 3:
		while (Serial3.available())
		{
			char inChar = (char)Serial3.read();
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
}

void GPS_M::update(String sentence)
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

//GPS_M GPS_MBody;

