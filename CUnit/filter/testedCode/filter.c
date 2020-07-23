#include "filter.h"
#include "types.h"
#include "globals.h"

void Filter_init(Filter *f, float initial_distance) {
	f->distance = initial_distance;
}	

float Filter_GetRawData(Filter* f) {
	unsigned int timeapp;
	float dist;
	timeapp = (time < HYSR05_TMAX) ? time : HYSR05_TMAX;
	dist = (float) timeapp * HYSR05_NUMBER; 	// Convert us to cm 
	return dist; 			     	// Return distance 
}

float Filter_Read(Filter* f) {
	float RawData;
	/* LPF: Y(n) = (1-ß)*Y(n-1) + (ß*X(n))) = Y(n-1) - (ß*(Y(n-1)-X(n)));
	   Function that brings Fresh Data into RawData */
	RawData = Filter_GetRawData(f);
	if (RawData < 0){
		return -1;			//There is an error
	} else {
		f->distance = f->distance - (LPF_Beta * (f->distance - RawData));
	}
	return f->distance;
}
