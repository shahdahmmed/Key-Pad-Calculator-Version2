/*
 * Key_int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: dell
 */

#include "../../MCAL/DIO.h"
#include "../../LIB/STD_TYPES.h"

#ifndef KEY_INT_H_
#define KEY_INT_H_

#define KPD_PORT PORTC

#define RowNumber 4
#define ColNumber 4

u8 G_u8PortNum;


void HKPD_voidInit(u8 A_u8PortNum);
u8 HKPD_u8GetKeyPressed();

#endif /* KEY_INT_H_ */
