#include <GPS.h>
#include <SoftwareSerial.h>

GPS gps(0); // Esta instruccion inicia el objeto gps, nombralo como quieras pero el argumento es importante
			// el 0 significa que tu vas a manejar el serial por tu cuenta

/*No todos los pines en Leonardo soportan interruptores
 por tanto cuando selecciones el pin RX utiliza solo uno de los siguientes
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI). intenta lo mismo para tu UNO*/
SoftwareSerial sserial(8, 9, false);

String inputString;
char incomingByte;
uint8_t index = 0;

void setup() 
{
	gps.init(); // esta instruccion tambien es importante e inicia todos los parametros en 0 o default y siempre se tiene que usar

	sserial.begin(9600);// esta es parte del software serial, aqui es donde va tu GPS, recuerda que rx a tx t tx a rx ! 
	Serial.println(9600);// inicia el serial para tu software en la computadora
}

void loop() {
	
	while (sserial.available())
	{
		char incomingByte = (char)sserial.read();
		inputString += incomingByte;
		if (incomingByte == '\n') {
			// esta funcion separa la cadena de caracteres y la acomoda realizando todas las actualizaciones necesarias
			// es obviamente la instruccion mas importante y siempre debes incluirla, el argumento es la cadena NMEA
			gps.update(inputString);
		}
	} 
		
	if (gps.dataIsReady())// esta función dataIsReady() es para saber si los datos ya son actuales, utilizala antes de obtener algun
	{					  // parámetro, si regresa como TRUE entonces los datos estan listos
		switch (index)
		{
			case 0:
				Serial.print("cadena NMEA:  ");
				//getNmeaSentenceName() - muestra el nombre de la última cadena que se proceso
				Serial.println(gps.getNmeaSentenceName());
				break;

			case 1:
				Serial.print("hora UTC: ");
				//getTimeUTC() - muestra la hora Universal o GMT en formato HH:MM:SS
				Serial.println(gps.getTimeUTC());
				Serial.print("fecha UTC: ");
				//getDateUTC - muestra la hora universal, el argumento selecciona el formato, utiliza TRUE para mm.dd.yyyy 
				//o FALSE para el formato  dd.mm.yyyy 
				Serial.println(gps.getDateUTC(true));
				break;

			case 2:
				Serial.print("Latitud Decimal: ");
				//getLatitude() - la intrucción regresa la coordenada latitud en su formato decimal
				Serial.println(gps.getLatitude());
				Serial.print("Longitud Decimal: ");
				//getLongitude() - la intrucción regresa la coordenada longitud en su formato decimal
				Serial.println(gps.getLongitude());
				break;
	
			case 3:
				Serial.print("Latitud Formato 1: ");
				// regresa la latitud en el siguiente formato ##º ##.####' N 
				Serial.println(gps.getLatitudeS1());
				Serial.print("Longitud Formato 1: ");
				// regresa la longitud en el siguiente formato ###º ##.####' W 
				Serial.println(gps.getLongitudeS1());
				break;

			case 4:
				Serial.print("Latitud Formato 2: ");
				// regresa la latitud en el siguiente formato ##º ##' ###'' N 
				Serial.println(gps.getLatitudeS2());
				Serial.print("Longitud Formato 2: ");
				// regresa la longitud en el siguiente formato ###º ##' ###'' W 
				Serial.println(gps.getLongitudeS2());
				break;

			case 5:
				Serial.print("Velocidad actual: ");
				// la siguiente instruccion regresa la velocidad en kilometros por hora
				Serial.println((String)gps.getSpeed() + "km/h");
				Serial.print("Velocidad actual: ");
				// la siguiente instruccion regresa la velocidad en nudos por hora
				Serial.println((String)gps.getSpeedKph() + "knt/h");
				Serial.print("Velocidad actual: ");
				// la siguiente instruccion regresa la velocidad en millas por hora
				Serial.println((String)gps.getSpeedMph() + "mph");
				break;


			case 6:
				Serial.print("Altitud:  ");
				/* las siguiente dos funciones trabajan en conjunto y funcionan asi, primero utiliza,
				   la función suspectAltitude() que regresa falso o verdadero, si es verdadero puedes utiliza la 	
				   función getAltitude() para obtener la altulra, si la funcion previa es falso no utilice la altura
				   aun que tengas un dato concreto :)*/
				gps.suspectAltitude() ? Serial.println(gps.getAltitude()) : Serial.println("no geoID");
				Serial.print("Satelites en Vista ");
				// número de satelites que se estan siguiendo 
				Serial.println(gps.getsatellitesTracked());
				Serial.print("Desviacion Magnetica: ");
				// Esta funcion la manejamos para hacer pequeñas correcciones a las coordenadas, si te sirven, ahi esta... 
				Serial.println(gps.getMagneticVariation());
				break;

			case 7:
				Serial.print("Hora Local: ");
				//getTimeLocal() - ¡aun experimental! utiliza la longitud para intentar dar la hora local... pero 
				//					rara vez funciona adecuadamente :) 
				Serial.println(gps.getTimeLocal());
				Serial.print("Fecha Local: ");
				/* getDateUTC - ¡aun experimental! pero pues por la misma naturaleza es correcta casi siempre, regresa la fecha
				actual basado en la locacion actual, argumentos son TRUE o FALSE, al igual que con la funcion utc true regresa 
				el formato en Ingles, falso en Universal, solo recuerda, no creo que sea muy adecuado usarlo cerca de Costa de Marfil
				o viajando cerca del meridiano de Greenwich :P*/
				Serial.println(gps.getDateLocal(true));
				break;
			
			default:
				if (index >= 8)
					index = 0;
			break;
		}
		index++;
	}


}