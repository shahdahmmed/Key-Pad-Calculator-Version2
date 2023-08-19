/*
 * Key_prog.c
 *
 *  Created on: Aug 14, 2023
 *      Author: dell
 */

#include "../../MCAL/DIO.h"
#include "../../LIB/STD_TYPES.h"
#include "Key_int.h"
#include <util/delay.h>

#define SIZE 4

u8 G_u8Grid[4][4]={
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'c','0','=','+'}
							};

void HKPD_voidInit(u8 A_u8PortNum)
{
	G_u8PortNum=A_u8PortNum;
	MDIO_voidSetPortDirection(G_u8PortNum,0X0F);
	MDIO_voidSetPortValue(G_u8PortNum,0XFF);
}

u8 HKPD_u8GetKeyPressed()
{
	u8 L_u8PressedKey=' ';
	for(u8 col=0; col<ColNumber; col++)
	{
		MDIO_voidSetPinValue(G_u8PortNum,col,LOW);
		for(u8 row=0; row<RowNumber; row++)
		{
			if(MDIO_U8GetPinValue(G_u8PortNum,row+ColNumber)==LOW)
			{
				L_u8PressedKey=G_u8Grid[row][col];
			}
			while(MDIO_U8GetPinValue(G_u8PortNum,row+ColNumber)==LOW) {}
			_delay_ms(5);

		}
		MDIO_voidSetPinValue(G_u8PortNum,col,HIGH);
	}
	return L_u8PressedKey;
}
