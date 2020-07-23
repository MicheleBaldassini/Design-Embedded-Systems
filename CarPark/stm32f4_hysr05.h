#ifndef HYSR05_H
#define HYSR05_H

#include "stm32f4xx.h"

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
#define HYSR05_TMAX				HYSR05_DMAX*59 //us
#endif

/**
 * @brief  Time in microseconds to centimeters conversion
 */
#define HYSR05_NUMBER			((float)0.017)

typedef struct {
	float distance; 				/*!< Distance measured from sensor in centimeters last time */
	GPIO_TypeDef* ECHO_GPIOx; 		/*!< Pointer to GPIOx PORT for ECHO pin. Meant for private use only */
	uint16_t ECHO_GPIO_Pin; 		/*!< GPIO Pin for ECHO pin. Meant for private use only */
	GPIO_TypeDef* TRIGGER_GPIOx; 	/*!< Pointer to GPIOx PORT for TRIGGER pin. Meant for private use only */
	uint16_t TRIGGER_GPIO_Pin; 		/*!< GPIO Pin for ECHO pin. Meant for private use only */
} HYSR05_t;

uint8_t HYSR05_Init(HYSR05_t* HYSR05, GPIO_TypeDef* ECHO_GPIOx,
		uint16_t ECHO_GPIO_Pin, GPIO_TypeDef* TRIGGER_GPIOx,
		uint16_t TRIGGER_GPIO_Pin);
float HYSR05_Read(HYSR05_t* HYSR05);

#endif
