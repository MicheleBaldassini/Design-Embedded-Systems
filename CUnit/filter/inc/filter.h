#ifndef FILTERH
#define FILTERH
#include "cclass.h"

/* Default timeout pulses */
#ifndef HYSR05_TIMEOUT
#define HYSR05_TIMEOUT			1000000
#endif
/* Low Pass Filter Factor */
#define LPF_Beta 				 0.050 // 0<ß<1
/* Default Maximum Distance Detected in cm */
#ifndef HYSR05_DMAX
#define HYSR05_DMAX				200 // cm
/* Time to read DMAX */
#define HYSR05_TMAX				HYSR05_DMAX*58 //us
#endif

/**
 * @brief  Time in microseconds to centimeters conversion
 */
#define HYSR05_NUMBER			((float)0.017)

extern unsigned int time;//= 0;

CLASS(Filter)
	float distance;
METHODS
	void Filter_init(Filter *f, float dis);
	float Filter_GetRawData(Filter *f);
	float Filter_Read(Filter *f);
END_CLASS

#endif // FILTERH
