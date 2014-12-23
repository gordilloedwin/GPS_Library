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

#include "tCoordinate.h"

void TCoordinate::setDegrees(String parser)
{
	degree = (uint_fast8_t)parser.toInt();
	decimal = parser.toFloat();
}

void TCoordinate::setMinutes(String parser)
{
	holder = parser.toFloat();
	decimal += holder / 60.00;
	minutes = (int_fast8_t)parser.substring(0,2).toInt();
	seconds = (int_fast8_t)parser.substring(2).toFloat()*60.00;
}

void TCoordinate::setAxis(char p)
{
	axis = p;
	if (axis == 'S' || axis == 'W')
		decimal = decimal * -1.00;
}

char TCoordinate::getAxis() {
	return axis;
}

int_fast8_t TCoordinate::getDegrees() {
	return degree;
}


float TCoordinate::getDecimalFormat() {
	return decimal;	
}

String TCoordinate::getSphericalFormat1()
{
	String ret = (String)degree;
	ret += "* ";
	ret += (String)holder;
	ret += "' " + axis;
	return ret;
}

String TCoordinate::getSphericalFormat2()
{
	String ret = (String)degree;
	ret += "*";
	ret += (String)minutes;
	ret += "'";
	ret += (String)seconds;
	ret += '"';
	ret += " " + axis;
	return ret;
}


//TCoordinate TCoordinateBody;

