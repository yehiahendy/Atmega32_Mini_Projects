/*
 * GccApplication1.c
 *
 * Created: 9/10/2020 6:43:18 AM
 * Author : yehia
 */ 

#include "Driver/MCAL/DIO/DIO.h"
#include "Driver/HAL/LCD/LCD.h"
#include <avr/interrupt.h>		
#include "Driver/MCAL/External_Interrupt/EXTI.h"
#define MAX  10
uint8 counter = 0;
uint8 str[] = "No.of cars is ";
int main(void)
{	 
	///initialize LCD
	LCD_init();
	///initialize External interrupt 
	EXTI_init();
	sei();
	///initialize red alarm 
	DIO_WritePinDir('A',0,STD_OUT);
	///set the message
	uint8 message[] = "Garage";
	

	while(1)
	{
		LCD_Move_Right(message);
		LCD_Move_Left(message);
	}
	
}
///new car enters the garage
ISR( INT0_vect )
{
		++counter;
		 if( (counter) <= MAX)

		{
				LCD_clearScreen();
				LCD_WriteString("A new car enters");
				LCD_GotoXY(1,0);
				LCD_WriteString(str);
				LCD_SendNumber(counter);
				DIO_WritePin('a',0,STD_low);
				 if ((counter) == MAX)
				{
				    DIO_WritePin('a',0,STD_high);
				}
				_delay_ms(1000);
		}

	    else if (counter > MAX)
	    {
				counter--;
				LCD_clearScreen();
				LCD_WriteString("Sorry");
				LCD_GotoXY(1,0);
				LCD_WriteString("Garage is full");
				DIO_WritePin('a',0,STD_high);
				_delay_ms(1000);
		}


	
}
ISR(INT1_vect)
{

		DIO_WritePin('A',0,STD_low);
		LCD_clearScreen();
		LCD_WriteString("Empty place :");
		LCD_GotoXY(1,0);
		LCD_WriteString(str);
		LCD_SendNumber(--counter);
		_delay_ms(1000);
		LCD_clearScreen();
}