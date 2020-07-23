/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "stm32f4_hysr05.h"

void delayus(volatile uint32_t nCount) {
	volatile uint32_t index = 0;
	for (index = (5 * nCount); index != 0; index--)
		;
}

void delayums(volatile uint32_t nCount) {
	volatile uint32_t index = 0;
	for (index = (5000 * nCount); index != 0; index--)
		;
}

float HYSR05_GetRawData(HYSR05_t* HYSR05) {
	uint32_t time, timeout;
	float distance;

	/* Trigger low */
	GPIO_ResetBits(HYSR05->TRIGGER_GPIOx, HYSR05->TRIGGER_GPIO_Pin);
	/* Delay 2 us */
	delayus(2);
	/* Trigger high for 10us */
	GPIO_SetBits(HYSR05->TRIGGER_GPIOx, HYSR05->TRIGGER_GPIO_Pin);
	/* Delay 10 us */
	delayus(10);
	/* Trigger low */
	GPIO_ResetBits(HYSR05->TRIGGER_GPIOx, HYSR05->TRIGGER_GPIO_Pin);

	/* Give some time for response */
	timeout = HYSR05_TIMEOUT;
	while (!GPIO_ReadInputDataBit(HYSR05->ECHO_GPIOx, HYSR05->ECHO_GPIO_Pin)) {
		if (timeout-- == 0x00) {
			return -1;
		}
	}

	if (GPIO_ReadInputDataBit(HYSR05->ECHO_GPIOx, HYSR05->ECHO_GPIO_Pin)) {
		/* Start time */
		time = 0;
		/* Wait till signal is low */
		while (GPIO_ReadInputDataBit(HYSR05->ECHO_GPIOx, HYSR05->ECHO_GPIO_Pin)
				&& time < HYSR05_TMAX) {
			/* Increase time */
			time++;
			/* Delay 1us */
			delayus(1);
		}
	}
	/* Convert us to cm */
	distance = (float) time * HYSR05_NUMBER;
	/* Return distance */
	return distance;
}

uint8_t HYSR05_Init(HYSR05_t* HYSR05, GPIO_TypeDef* ECHO_GPIOx,
		uint16_t ECHO_GPIO_Pin, GPIO_TypeDef* TRIGGER_GPIOx,
		uint16_t TRIGGER_GPIO_Pin) {

	GPIO_InitTypeDef GPIO_InitStruct;
	/* Save everything */
	HYSR05->ECHO_GPIOx = ECHO_GPIOx;
	HYSR05->ECHO_GPIO_Pin = ECHO_GPIO_Pin;
	HYSR05->TRIGGER_GPIOx = TRIGGER_GPIOx;
	HYSR05->TRIGGER_GPIO_Pin = TRIGGER_GPIO_Pin;
	HYSR05->distance = HYSR05_DMAX;
	/* Initialize pins */
	/* Echo pin */
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = ECHO_GPIO_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(ECHO_GPIOx, &GPIO_InitStruct);
	/* Trigger pin */
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = TRIGGER_GPIO_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(TRIGGER_GPIOx, &GPIO_InitStruct);
	/* Trigger set to low */
	GPIO_ResetBits(TRIGGER_GPIOx, TRIGGER_GPIO_Pin);
	/* Start measurement, check if sensor is working */
	if (HYSR05_GetRawData(HYSR05) >= 0) {
		/* Sensor OK */
		return 1;
	}
	/* Sensor error */
	return 0;
}

float HYSR05_Read(HYSR05_t* HYSR05) {
	float RawData;
	// LPF: Y(n) = (1-ß)*Y(n-1) + (ß*X(n))) = Y(n-1) - (ß*(Y(n-1)-X(n)));
	// Function that brings Fresh Data into RawData
	RawData = HYSR05_GetRawData(HYSR05);
	HYSR05->distance = HYSR05->distance
			- (LPF_Beta * (HYSR05->distance - RawData));
	return HYSR05->distance;
}
