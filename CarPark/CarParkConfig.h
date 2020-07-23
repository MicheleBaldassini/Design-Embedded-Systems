#ifndef CARPARKCONFIG_H_
#define CARPARKCONFIG_H_

#include "defines.h"
#include "Widget.h"
#include "stm32f4_hysr05.h"


#define MAXNPARK	6
#define NPARK 		2

#define NEWCAR(i)	Button __car_##i##_button__;\
					Park __car_##i##__ = {FREE ,\
							(const unsigned char*)&car##i##free_ImageBuffer, \
							(const unsigned char*)&car##i##red_ImageBuffer, \
							(const unsigned char*)&car##i##green_ImageBuffer}

extern Widget MyCarParkScr[MAXNPARK];
extern const Widget MyCarParkBtn[MAXNPARK];
extern const Widget background;
extern HYSR05_t MyCarParkSen[NPARK];

extern void initSensors();
extern void myCarParkInit();

#endif /* CARPARKCONFIG_H_ */
