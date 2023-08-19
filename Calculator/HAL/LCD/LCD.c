/*
 * LCD.c
 *
 *  Created on: Aug 15, 2023
 *      Author: dell
 */

#define F_CPU 8000000UL //for coventionality

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO.h"
#include <util/delay.h>
#include "../LCD/LCD_int.h"


void HLCD_voidSendCommand(u8 A_u8cmd)
{
	//control RS and RW pins
	MDIO_voidSetPinDirection(Control_Port,PIN0,OUTPUT);
		MDIO_voidSetPinDirection(Control_Port,PIN1,OUTPUT);

		MDIO_voidSetPinValue(Control_Port,PIN0,LOW);
		MDIO_voidSetPinValue(Control_Port,PIN1,LOW);

		//write data on data_port
		MDIO_voidSetPortDirection(Data_Port,OUTPUT);
		MDIO_voidSetPortValue(Data_Port,A_u8cmd);

		//Enable pin
		MDIO_voidSetPinDirection(Control_Port,PIN2,OUTPUT);

		MDIO_voidSetPinValue(Control_Port,PIN2,HIGH);
		_delay_ms(1);
		MDIO_voidSetPinValue(Control_Port,PIN2,LOW);
		_delay_ms(1);

}


void HLCD_voidSendData(u8 A_u8Data)
{

	MDIO_voidSetPinDirection(Control_Port,PIN0,OUTPUT);
		MDIO_voidSetPinDirection(Control_Port,PIN1,OUTPUT);

		MDIO_voidSetPinValue(Control_Port,PIN0,HIGH);
		MDIO_voidSetPinValue(Control_Port,PIN1,LOW);

		//write data on data_port
		MDIO_voidSetPortDirection(Data_Port,OUTPUT);
		MDIO_voidSetPortValue(Data_Port,A_u8Data);

		//Enable pin
		MDIO_voidSetPinDirection(Control_Port,PIN2,OUTPUT);

		MDIO_voidSetPinValue(Control_Port,PIN2,HIGH);
		_delay_ms(1);
		MDIO_voidSetPinValue(Control_Port,PIN2,LOW);
		_delay_ms(1);
}


void HLCD_voidInt()
{

	_delay_ms(30);
	HLCD_voidSendCommand(LCD_functionset);
	_delay_ms(1);

	//display on/off 0b00001100

	HLCD_voidSendCommand(LCD_DisplayONOFF);
	_delay_ms(1);

	//display clear  0b00000001
	HLCD_voidSendCommand(LCD_Clear);
	_delay_ms(1);


	_delay_ms(2);
	//entry mode     0b00000110
	HLCD_voidSendCommand(LCD_EntryMode);


}



void HLCD_voidClear()
{

	//display clear  0b00000001
	HLCD_voidSendCommand(LCD_Clear);
	_delay_ms(2);
}


void HLCD_voidSendString(u8 *A_u8PtrString)
{
	u8 L_u8cnt=0;
	while(A_u8PtrString[L_u8cnt] !="\0")
	{
		HLCD_voidSendData(A_u8PtrString[L_u8cnt++]);
	}

}




void HLCD_voidCursor(u8 A_u8LinePos , u8 A_u8LineNo)
{

	switch(A_u8LineNo)
	{

	case LCD_LINE0: HLCD_voidSendCommand(0x80 + 0 + A_u8LinePos);break;
	case LCD_LINE1 : HLCD_voidSendCommand(0x80 + 64 + A_u8LinePos);break;
	}
}


void HLCD_voidDisplyNumber(s32 A_s32Num){
	if(A_s32Num==0)
		{
			HLCD_voidDisplayChar('0');
			return;
		}
		u32 L_u32Num=0;
		u8 flag=0;
		if (A_s32Num < 0)
		{
			HLCD_voidDisplayChar('-');
			A_s32Num*=-1;
		}
		while ((A_s32Num % 10) == 0)
			{
				flag++;
				A_s32Num/=10;
			}
		while (A_s32Num !=0)
		{
			L_u32Num=((L_u32Num*10)+(A_s32Num%10));
			A_s32Num/=10;
		}
		while (L_u32Num >0)
		{
			HLCD_voidSendData((L_u32Num%10)+48);
			L_u32Num/=10;
		}
		while (flag !=0)
		{
			HLCD_voidDisplayChar('0');
			flag--;
		}
}

void HLCD_voidDisplayChar(u8 A_u8Char)
{
	HLCD_voidSendData(A_u8Char);
}


void HLCD_voidSaveCustomChar(u8 A_u8CGRAMIndex,u8 A_u8CustmArr[]){
			HLCD_voidSendCommand(0b01000000+(A_u8CGRAMIndex*8));//num of location jumps
			for(u8 L_u8Index=0;L_u8Index<8;L_u8Index++){
				HLCD_voidSendData(A_u8CustmArr[L_u8Index]);

			}
			HLCD_voidSendCommand(0x80);//IMP BACK TO DDRAM

}

void HLCD_voidDisplayCustomChar(u8 A_u8CGRAMIndex){
	if(A_u8CGRAMIndex <8){
		HLCD_voidSendData(A_u8CGRAMIndex);
	}
}


