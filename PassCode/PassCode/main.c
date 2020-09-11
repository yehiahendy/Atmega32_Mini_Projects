/*
 * LCD.c
 *
 * Created: 9/4/2020 5:44:51 PM
 * Author : yehia
 */ 
#include "Driver/HAL/KeyPad/KeyPad.h"
#include "Driver/HAL/LCD/LCD.h"
int main(void)
{
	uint8 rest[6]="*#0*#";
    uint8 pass[5];
	uint8 choice[6];
	//choice[5]='\0';
	//pass[4]='\0';
	LCD_init();
	KP_VidInit();
	uint8 i=0;
	uint8 x='\0';
	uint8 temp[]="9619";
	while(1)
	{
			    //show welcome message
			    LCD_Move_Right("WELCOME");
			    //ask the user about his option
			    LCD_GotoXY(0,0);
			    LCD_WriteString("1-reset password");
			    LCD_GotoXY(1,0);
			    LCD_WriteString("2-Sign in");
			    //get the choice
				 x='\0' ;
				 _delay_ms(500);
			    while(1)
			    {
				    x = KP_u8GetKey();
				    if (x != '\0')
				    {
					    break;
				    }
			    }
			    
			    switch(x)
			    {
				    case  '1' : // reset the password
				    LCD_clearScreen();
				    LCD_WriteString("Enter the code");
				    LCD_GotoXY(1,0);
				    //get the reset code
					i=0;
				    while (i<5)
				    {
					    x = KP_u8GetKey();
					    if (x != '\0')
					    {
						    choice[i] = x;
						    LCD_SendData('*');
						    i++;
					    }
					    
				    }
				    LCD_clearScreen();
				    _delay_ms(1000);
				    if (strcmp(choice,rest) == 0)
				    {
					    LCD_WriteString("The new password");
					    LCD_GotoXY(1,0);
					    i = 0;
					    while(i<4)
					    {
						    x = KP_u8GetKey();
						    if (x != '\0')
						    {
							    temp[i] = x;
							    LCD_SendData('*');
							    i++;
						    }
					    }
					    LCD_clearScreen();
					    LCD_WriteString("success");
					    _delay_ms(3000);
				    }
				    else
				    {
					    LCD_WriteString("Not allowed");
					    _delay_ms(3000);
				    }
				    break;
				    case '2':
				    i = 0;
				    LCD_clearScreen();
				    LCD_WriteString("Enter password");
				    LCD_GotoXY(1,0);
				    while(i<4)
				    {
					    x = KP_u8GetKey();
					    if (x != '\0')
					    {
						    pass[i] = x;
						    LCD_SendData('*');
						    i++;
					    }
				    }
				    LCD_clearScreen();
				    _delay_ms(1000);
				    if (strcmp(temp,pass) == 0)
				    {
					    LCD_WriteString("Welcome Yehia");
						_delay_ms(3000);
				    }
				    else
				    {
					    LCD_WriteString("Wrong password");
						_delay_ms(3000);
				    }
				    break;
				    
			    }
				
	}

}
