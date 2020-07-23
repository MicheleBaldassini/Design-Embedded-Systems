/*
 * defines.h
 *
 *  Created on: 17 feb 2017
 *      Author: Stefano
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define null	((void *)0)

#define GPIOtoI(gpiox)	(gpiox == GPIOA)?0:\
						(gpiox == GPIOB)?1:\
						(gpiox == GPIOC)?2:\
						(gpiox == GPIOD)?3:4

#define ItoGPIO(i)		(i == 0)?GPIOA:\
						(i == 1)?GPIOB:\
						(i == 2)?GPIOC:\
						(i == 3)?GPIOD:GPIOE

#define ItoRCC(i)		(i == 0)?RCC_AHB1Periph_GPIOA:\
						(i == 1)?RCC_AHB1Periph_GPIOB:\
						(i == 2)?RCC_AHB1Periph_GPIOC:\
						(i == 3)?RCC_AHB1Periph_GPIOD:\
								RCC_AHB1Periph_GPIOE

#define RCCtoI(RCC)		(RCC == RCC_AHB1Periph_GPIOA)?0:\
						(RCC == RCC_AHB1Periph_GPIOB)?1:\
						(RCC == RCC_AHB1Periph_GPIOC)?2:\
						(RCC == RCC_AHB1Periph_GPIOD)?3:4

#endif /* DEFINES_H_ */
