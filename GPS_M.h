// GPS_M.h

#ifndef _GPS_M_h
#define _GPS_M_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>
#include "GPS.h"

class GPS_M : public GPS
{
 private:
	short serialSelect;
	int baudRate;
 
 public:
	GPS_M() : serialSelect(-1), baudRate(9600) {};
	GPS_M(int bRate) : serialSelect(0), baudRate(bRate) {};
	GPS_M(short sSelect, int bRate) : serialSelect(sSelect), baudRate(bRate) {};
		//@Override..
	void init();
	void update();
	void update(String sentence);
};

//extern GPS_M GPS_MBody;

#endif

