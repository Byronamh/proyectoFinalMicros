// Universidad del Valle de Guatemala
// CC3056
// Christian Medina
// Ana lucia Diaz y Byron Mota
// compile with:
// g++ main.cpp bme280.cpp bme280.h -lwiringPi -o bme280


#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <wiringPiI2C.h>
#include "bme280.h"
#include <pthread.h>
#include "sensores.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;


char* intprkey(int ch);
void *thread_function_statuts(void*);
void *thread_function_print(void*)
#define SLEEPTIME 1
  
  float temperatura = 0;
  float humedad = 0;
  float presion =0;
  pthread_mutex_t lock;

int main(int argv, char* argc[]){
  int fd = wiringPiI2CSetup(BME280_ADDRESS);
  
  if(fd < 0){
    printf("Device not found");
    return -1;
  }

  bme280_calib_data cal;
  readCalibrationData(fd, &cal);

  wiringPiI2CWriteReg8(fd, 0xf2, 0x01);   // humidity oversampling x 1
  wiringPiI2CWriteReg8(fd, 0xf4, 0x25);   // pressure and temperature oversampling x 1, mode normal

  bme280_raw_data raw;
  getRawData(fd, &raw);

  int32_t t_fine = getTemperatureCalibration(&cal, raw.temperature);

  float t = compensateTemperature(t_fine); // C
  float p = compensatePressure(raw.pressure, &cal, t_fine) / 100; // hPa
  float h = compensateHumidity(raw.humidity, &cal, t_fine);       // %
  float a = getAltitude(p);                         // meters
  
  // output data to screen
  cout<<t<<"\t"<<p<<"\t"<<h<<endl;
  return 0;
}
