#include "CarParkConfig.h"
#include "pictures.h"
#include <stdio.h>

Image backg = { ImageBuffer };
const Widget background = { 0, 0, 320, 240, IMAGE, (void *) &backg };

NEWCAR(1);
NEWCAR(2);
NEWCAR(3);
NEWCAR(4);
NEWCAR(5);
NEWCAR(6);

Widget MyCarParkScr[MAXNPARK] = {
		{ 54, 1, 58, 106, PARK, (void *) &__car_1__ },
		{ 126, 1, 58, 106, PARK, (void *) &__car_2__ },
		{ 199, 1, 58, 106, PARK, (void *) &__car_3__ },
		{ 54, 133, 58, 106, PARK, (void *) &__car_4__ },
		{ 126, 133, 58, 106, PARK, (void *) &__car_5__ },
		{ 199, 133, 58, 106, PARK, (void *) &__car_6__ }
};

const Widget MyCarParkBtn[MAXNPARK] = {
		{ 54, 1, 58, 106, BUTTON,(void *) &__car_1_button__ },
		{ 126, 1, 58, 106, BUTTON,(void *) &__car_2_button__ },
		{ 199, 1, 58, 106, BUTTON,(void *) &__car_3_button__ },
		{ 54, 133, 58, 106, BUTTON,(void *) &__car_4_button__ },
		{ 126, 133, 58, 106, BUTTON,(void *) &__car_5_button__ },
		{ 199, 133, 58, 106, BUTTON,(void *) &__car_6_button__ }
};

HYSR05_t MyCarParkSen[NPARK] = {
		//{ HYSR05_DMAX, GPIOC, GPIO_Pin_14, GPIOC, GPIO_Pin_15 },
		//{ HYSR05_DMAX, GPIOE, GPIO_Pin_6, GPIOC, GPIO_Pin_13 },
		{ HYSR05_DMAX, GPIOE, GPIO_Pin_4, GPIOE, GPIO_Pin_5 },
		//{ HYSR05_DMAX, GPIOE, GPIO_Pin_2, GPIOE, GPIO_Pin_3 },
		{ HYSR05_DMAX, GPIOE, GPIO_Pin_0, GPIOE, GPIO_Pin_1 }
};


void initSensors() {
	int i,j;
	int init[5] = { 0, 0, 0, 0, 0 };
	uint32_t RCCs = 0;
	for (i = 0; i < NPARK; i++) {
		j = GPIOtoI(MyCarParkSen[i].TRIGGER_GPIOx);
		if (init[j] == 0)
			init[j] = 1;
		j = GPIOtoI(MyCarParkSen[i].ECHO_GPIOx);
		if (init[j] == 0)
			init[j] = 1;
	}
	for (i = 0; i < 5; i++) {
		if (init[i] == 1) {
			RCCs |= ItoRCC(i);
		}
	}
	RCC_AHB1PeriphClockCmd(RCCs, ENABLE);
	for (i = 0; i < NPARK; i++) {
		HYSR05_Init(&(MyCarParkSen[i]), MyCarParkSen[i].ECHO_GPIOx,
				MyCarParkSen[i].ECHO_GPIO_Pin, MyCarParkSen[i].TRIGGER_GPIOx,
				MyCarParkSen[i].TRIGGER_GPIO_Pin);
	}
}

void myCarParkInit() {
	int i;
	PState ps;
	ps = FREE;
	WPrint(&background, null);
	for (i = 0; i < NPARK; i++)
		WPrint(&MyCarParkScr[i], &ps);
}
