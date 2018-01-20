/*

* Author: Dhananjay Kumar Sharma
	  Roll - 173050046
          CSE Department, IIT Bombay

* Problem statement- 

Configure SW1 and SW2 such that:
Every time SW1 is pressed toggle delay of LED should cycle through approximately
0.5s, 1s, 2s (Of any one color).
Every time SW2 is pressed color of LED should cycle through Red, Green and Blue.

* Filename: lab1_2.c


*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include <time.h>


void setup(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //unlock PF0 based on requirement

}

void pin_config(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= GPIO_LOCK_KEY ;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01 ;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= 0;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_4;


    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

int main(void)
{

    uint8_t ui8LED = 2;
    int temp_speed,speed = 3350000;
    temp_speed =speed;

    setup();
    pin_config();

    while(1)
    {
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {
            if(ui8LED == 2)
                ui8LED = 8;
            else if(ui8LED == 8)
                ui8LED = 4;
            else
                ui8LED =2;
        }
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
        {

                if(temp_speed == 4*speed)
                    temp_speed =speed;
                else
                    temp_speed *=2;

        }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
        SysCtlDelay(temp_speed);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        SysCtlDelay(temp_speed);



    }
}
