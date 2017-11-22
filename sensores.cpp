#include <stdint.h>

#include "bme280.h"

#include "sensor.h"

#include <time.h>

#include <math.h>

#include <wiringPiI2C.h>

//Ana lucia Diaz Leppe
//Byron Mota 
//Se implementaron las tres funciones que se necesitaban , siendo estas la presion , la temperatura y el sensor. Todos fueron float y tuvieron el mismo proceso que el 
//anterior simplemente se fueron cambiando en las dos ultimas lineas  finales. todas se realicionaron con el proceso de bme280.cpp  
// se baso en https://github.com/mozilla-b2g/android-device-crespo/blob/master/libsensors/sensors.cpp
float getPresion(){
	//del dato obtenido de Christian en la funcion de read calibration
    	int fd = wiringPiI2CSetup(BME280_ADDRESS); //el fd, BM...
	bme280_calib_data cal;
	readCalibrationData(fd, &cal); //por los parametros obtenidos del anterior
	wiringPiI2CWriteReg8(fd, 0xf4, 0x25); //del wiringPiI2CRReadReg16
	bme280_raw_data raw;
    	getRawData(fd, &raw);
	int32_t t_fine = getTemperatureCalibration(&cal, raw.temperature); //primer parametro del compensate pressure
	float presion = compensatePressure(raw.pressure, &cal, t_fine) / 100;  //
	return presion;
}

float getTemperatura(){
	int fd = wiringPiI2CSetup(BME280_ADDRESS);
	bme280_calib_data cal;
	readCalibrationData(fd, &cal);
	wiringPiI2CWriteReg8(fd, 0xf4, 0x25);   // pressure and temperature oversampling x 1, mode normal
	bme280_raw_data raw;
	getRawData(fd, &raw);
	int32_t t_fine = getTemperatureCalibration(&cal, raw.temperature);
	float temperatura = compensateTemperature(t_fine); // C
	return temperatura;

}



float getHumedad(){
	int fd = wiringPiI2CSetup(BME280_ADDRESS);
	bme280_calib_data cal;
	readCalibrationData(fd, &cal);
	wiringPiI2CWriteReg8(fd, 0xf2, 0x01);
	bme280_raw_data raw;
	getRawData(fd, &raw); 
	int32_t t_fine = getTemperatureCalibration(&cal, raw.temperature);
	float humedad = compensateHumidity(raw.humidity, &cal, t_fine); 
	return humedad;

}
