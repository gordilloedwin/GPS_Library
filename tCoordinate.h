// tCoordinate.h

#ifndef _TCOORDINATE_h
#define _TCOORDINATE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#pragma once

class TCoordinate
{
 protected:
	char axis;
	float decimal;
	float holder;
	int_fast8_t degree;
	int_fast8_t minutes;
	int_fast8_t seconds;
	
 public:
	TCoordinate() : axis('X'), decimal(0.00), holder(0.0), degree(0), minutes(0), seconds(0) {};
	void setDegrees(String parser);
	void setMinutes(String parser);
	void setAxis(char p);
	char getAxis();
	int_fast8_t getDegrees();
	float getDecimalFormat();
	String getSphericalFormat1();
	String getSphericalFormat2();
};

//extern TCoordinate TCoordinateBody;

#endif

