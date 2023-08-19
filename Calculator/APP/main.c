/*
 * main.c
 *
 *  Created on: Aug 19, 2023
 *      Author: dell
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/KEY_PAD/Key_int.h"
#include "../HAL/LCD/LCD_int.h"



int main() {
    MDIO_voidSetPortDirection(PORTA, 0xFF);
    MDIO_voidSetPortDirection(PORTB, 0xFF);
    HLCD_voidInt();
    HKPD_voidInit(KPD_PORT);

    s32 currentNumber = 0;     // Store the current input number (negative or positive)
    u8 operatorPressed = '\0';  // Store the operator pressed (+, -, *, /)
    s32 result = 0;             // Store the result of calculations

    while (1) {
        u8 key = HKPD_u8GetKeyPressed();

        if (key >= '0' && key <= '9') {
            currentNumber = (currentNumber * 10) + (key - '0');
            HLCD_voidSendData(key);
        }
        else if (key == '-') {
            if (currentNumber == 0) {
                currentNumber = -1;  // Indicate that the next input is negative
                HLCD_voidSendData(key);
            }
        }
        else if (key == 'c') {
            currentNumber = 0;
            operatorPressed = '\0';
            result = 0;
            HLCD_voidClear();  // Clear the display
        }
        else if (key == '+' || key == '*' || key == '/') {
            if (operatorPressed != '\0') {
                if (operatorPressed == '+') {
                    result += currentNumber;
                }
                else if (operatorPressed == '-') {
                    result -= currentNumber;
                }
                else if (operatorPressed == '*') {
                	if (currentNumber == 0) currentNumber++;
                    result *= currentNumber;
                }
                else if (operatorPressed == '/') {
                    if (currentNumber != 0) {
                        result /= currentNumber;
                    }
                    else {
                        HLCD_voidSendString("Error!");
                        for (u16 i = 0; i < 2000; i++) {
                            _delay_ms(1);  // Wait for 2 seconds
                        }
                        HLCD_voidClear();  // Clear the display after showing error
                    }
                }
                HLCD_voidSendData(key);
            }
            else {
                result = currentNumber;
            }
            currentNumber = 0;  // Reset the current number
            operatorPressed = key;

            if (key == '/') {
                HLCD_voidSendData(key);
            }
        }
        else if (key == '=') {
            if (operatorPressed != '\0') {
                if (operatorPressed == '+') {
                    result += currentNumber;
                }
                else if (operatorPressed == '-') {
                    result -= currentNumber;
                }
                else if (operatorPressed == '*') {
                    result *= currentNumber;
                }
                else if (operatorPressed == '/') {
                    if (currentNumber != 0) {
                        result /= currentNumber;
                    }
                    else {
                        HLCD_voidSendString("Error!");
                        for (u16 i = 0; i < 2000; i++) {
                            _delay_ms(1);  // Wait for 2 seconds
                        }
                        HLCD_voidClear();  // Clear the display after showing error
                    }
                }
                HLCD_voidDisplayChar('=');
                HLCD_voidDisplyNumber(result);
                currentNumber = result;  // Store the result as the new input
                operatorPressed = '\0';  // Clear the operator
            }
        }
    }

    return 0;
}




