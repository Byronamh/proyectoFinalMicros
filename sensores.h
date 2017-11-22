#include <stdio.h>

#include <errno.h>

#include <stdint.h>

#include <time.h>

#include <math.h>

#include <wiringPiI2C.h>

#include "bme280.h"





#ifndef SENSOR_H

#define SENSOR_H



float getTemperatura();

float getHumedad();

float getPresion();



#endif
