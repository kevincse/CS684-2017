/*

* Author: Dhananjay Kumar Sharma
	  Roll - 173050046
          CSE Department, IIT Bombay

* Problem statement- 

Use switch SW2 and sw2Status (a variable). Your program should increment sw2Status
by one, every time switch is pressed. Note how the value of sw2Status changes on each
switch press. Use debugger and add sw2Status to “Watch Expression” window. Does
the value of sw2Status increment by one always? Show the result to TA. Note: Define
sw2Status as a global variable and in debug perspective use continuous refresh option
1(You will find Continuous Refresh button on top of the Expression Window). You can
use step debugging or breakpoints to check the variable value.

* Filename: lab1_1.c


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


/*

* Function Name: setup()

* Input: none

* Output: none

* Description: Set crystal frequency,enable GPIO Peripherals and unlock Port F pin 0 (PF0)

* Example Call: setup();

*/
void setup(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
	//unlock PF0 based on requirement

}

/*

* Function Name: pin_config()

* Input: none

* Output: none

* Description: Set Port F Pin 1, Pin 2, Pin 3 as output. On this pin Red, Blue and Green LEDs are connected.
			   Set Port F Pin 0 and 4 as input, enable pull up on both these pins.

* Example Call: pin_config();

*/

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

int status=0;

int main(void)
{
    
    uint8_t ui8LED = 2;

    setup();
    pin_config();

    while(1)
    {
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {
            if(ui8LED == 2)
            {
                ui8LED = 8;
            }
            else if (ui8LED == 8)
            {
                ui8LED = 4;
            }
            else
                ui8LED = 2;

        }
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
        {
            status = status +1;

        }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
        SysCtlDelay(2000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        SysCtlDelay(2000000);

    }
}
