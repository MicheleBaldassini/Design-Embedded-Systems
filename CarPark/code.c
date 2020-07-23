#include "ee.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f4_hysr05.h"
#include "stm32f4_discovery_lcd.h"
#include "./lcd-touch/Touch.h"
#include "CarParkConfig.h"
#include "Widget.h"
#include "FSM_Park.h"

#define MAX_HEIGHT_CAR			50	//cm

typedef struct {
	boolean_T arrived;
	boolean_T BAccept;
	RT_MODEL_FSM_Park_T SW_State;
	PrevZCX_FSM_Park_T ZCInfo;
	DW_FSM_Park_T DInfo;
	boolean_T free;
	boolean_T accept;
	uint8_t minutes;
	uint8_t hours;
} FSMPark_t;

#define isParkFree(p)	 		(p)->free
#define isParkWaitAccept(p) 	(p)->accept
#define getParkMinutes(p) 		(p)->minutes
#define getParkHours(p) 		(p)->hours
#define clearEvents(p)			(p)->BAccept = false;

FSMPark_t fsmpark[NPARK];
boolean_T tick = false;

/*
 * SysTick ISR2
 */
ISR2(systick_handler) {
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

void int2str(char* str, const int dist, const size_t n) {
	sprintf(str, "%d", dist);
	str[n - 1] = '\0';
}

TASK(TouchTask) {
	int i;
	unsigned int x, y;
	char str[20];
	TPoint p;
	if (GetTouch_SC_Async(&x, &y)) {
	/*  sprintf(str, "x: %d , y: %d", x, y);
		LCD_DisplayStringLine(LINE(0), str);	*/
		p.x = x;
		p.y = y;
		for (i = 0; i < NPARK; i++) {
			if (contains(&MyCarParkBtn[i], &p)) {
				fsmpark[i].BAccept = true;
				break;
			}
		}
	}
}

TASK(SensorsTask) {
	int i;
	float distance;
	char str[10];
	for (i = 0; i < NPARK; i++) {
		distance = HYSR05_Read(&(MyCarParkSen[i]));
		int2str(str, (int) distance, 10);
		LCD_DisplayStringLine(LINE(i), str);
		if (distance < MAX_HEIGHT_CAR) {
			fsmpark[i].arrived = true;
		} else {
			fsmpark[i].arrived = false;
		}
	}
}

TASK(AppTask) {
	int i;
	static unsigned char ostate[NPARK];
	static unsigned char state;
	PState ps;
	FSMPark_t *p;
	char stra[20];
	char strh[20];
	char strm[20];

	if (tick == true)
		tick = false;
	else
		tick = true;

	for (i = 0; i < NPARK; i++) {
		stra[0] = '\0';
		strh[0] = '\0';
		strm[0] = '\0';
		p = &fsmpark[i];
		FSM_Park_step(&(p->SW_State), tick, p->BAccept, p->arrived, &(p->free),
				&(p->accept), &(p->hours), &(p->minutes));
		clearEvents(p);
		//aggiorna ciò che si vede a schermo solo se lo stato è cambiato
		state = 0x00 | (p->free << 1) | (p->accept);
		if (state != ostate[i]) {
			switch (state) {
															//free <-> waitingAccept
			case (0x00): 									//  0		0		the car is parked
				ps = PARKED;
				break;
			case (0x01): 									//	0		1		the car is waiting to accept the departure
				sprintf(strh, "h:%d", p->hours);
				sprintf(strm, "m:%d", p->minutes);
				ps = ACCEPTING;
				break;
			case (0x02): 									//	1		0		the park is free
				ps = FREE;
				break;
			case (0x03): 									//	1		1		the car is waiting to accept the arrival
				sprintf(stra, "A");
				ps = ACCEPTING;
				break;
			}
			WPrint(&MyCarParkScr[i], &ps);
			if (strh[0] != '\0') {
				delay(1);
				LCD_DisplayStringXY(MyCarParkScr[i].xl + MyCarParkScr[i].xw / 8,
						MyCarParkScr[i].yt + MyCarParkScr[i].yh / 3, strh);
				if (strm[0] != '\0') {
					delay(1);
					LCD_DisplayStringXY(MyCarParkScr[i].xl+ MyCarParkScr[i].xw / 8,
							MyCarParkScr[i].yt + MyCarParkScr[i].yh / 2, strm);
				}
			}
			if (stra[0] != '\0') {
				delay(1);
				LCD_DisplayStringXY(MyCarParkScr[i].xl+ MyCarParkScr[i].xw / 3,
						MyCarParkScr[i].yt + MyCarParkScr[i].yh / 2, stra);
			}
			ostate[i] = state;
		}
	}
}

int main(void) {
	int i, ret;
	unsigned int x, y;
	char str[20];

	SystemInit();
	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/* GPIOE Periph clock enable */
	initSensors();

	/* Initializes LCD and touchscreen */
	IOE_Config();
	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();
//	LCD_SetBackColor(Black);
	LCD_SetTextColor(Black);
	InitTouch(-0.09, 0.0656, -353, 10);

	/* Initialize state machines */
	for (i = 0; i < NPARK; i++) {
		fsmpark[i].arrived = false;
		fsmpark[i].BAccept = false;
		fsmpark[i].SW_State.prevZCSigState = &(fsmpark[i].ZCInfo);
		fsmpark[i].SW_State.dwork = &(fsmpark[i].DInfo);
		FSM_Park_initialize(&(fsmpark[i].SW_State), &tick,
				&(fsmpark[i].BAccept), &(fsmpark[i].arrived),
				&(fsmpark[i].free), &(fsmpark[i].accept), &(fsmpark[i].hours),
				&(fsmpark[i].minutes));
	}
	myCarParkInit();

//	/* Program cyclic alarms which will fire after an initial offset,
//	 * and after that periodically
//	 * */
	SetRelAlarm(AlarmTouch, 1000, 50);
	SetRelAlarm(AlarmSensors, 1000, 500);
	SetRelAlarm(AlarmApp, 1000, 1000);
	/* Forever loop: background activities (if any) should go here */
	for (;;) {
	}
}
