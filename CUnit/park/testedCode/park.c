#include "park.h"
#include "types.h"
#include "globals.h"

void EE_lcd_putc (char);

//static 
enum State {FREE, ACCEPT_ARRIVALS, BUSY, ACCEPT_DEPARTURES};

//static 
enum Signal {ACCEPT, TOFREE, TOBUSY, ABSENT};

void ParkDisplay(bool busy){
	if (busy)
		EE_lcd_putc( '0' );
	else 
		EE_lcd_putc( 'L' );
}

void ParkInit(Park *me) {
	me->state_ = FREE;
	isbusy = 0; 
	ParkDisplay(isbusy);							
}

void ParkTran_(Park *me, unsigned int dest) {
	me->state_ = dest;
}

enum Signal ParkGetSignals(Park *me){
	switch (me->state_){
	case FREE:
		if (occupato)
			return TOBUSY;
		else
			return ABSENT;
		break;
	case ACCEPT_ARRIVALS:
		if(accetto && occupato)
			return ACCEPT;
		else if (libero)
			return TOFREE;
		else
			return ABSENT;	
		break;
	case BUSY:
		if (libero)
			return TOFREE;
		else
			return ABSENT;
		break;
	case ACCEPT_DEPARTURES:
		if(accetto && occupato)
			return TOBUSY;
		else if (accetto)
			return ACCEPT;		
		else
			return ABSENT;
		break;
	}
	return ABSENT;
}

void ParkDispatch(Park *me){
	enum Signal s = ParkGetSignals(me);
	switch (me->state_) {
	case FREE:
		switch(s) {
		case TOBUSY:
			ParkTran_(me, ACCEPT_ARRIVALS);
			break;
		}
		break;	
	case ACCEPT_ARRIVALS: 						
		switch(s) {
		case ACCEPT:
			isbusy = 1;
			ParkTran_(me, BUSY);
			ParkDisplay(isbusy);
			break;
		case TOFREE:
			isbusy = 0;
			ParkTran_ (me, FREE);
			ParkDisplay(isbusy);
			break;
		}
		break;
	case BUSY:
		switch (s) {
		case TOFREE:
			ParkTran_ (me, ACCEPT_DEPARTURES);
			break;
		}
		break;
	case ACCEPT_DEPARTURES:							
		switch (s) {
		case ACCEPT:
			isbusy = 0;
			ParkTran_ (me, FREE);
			ParkDisplay(isbusy);
			break;
		case TOBUSY:
			isbusy = 1;
			ParkTran_ (me, BUSY);
			ParkDisplay(isbusy);
			break;		
		}
	}
}



					

