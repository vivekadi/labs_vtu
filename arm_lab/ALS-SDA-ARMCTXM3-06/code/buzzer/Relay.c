/*************************************************************************
 * EXP 10:Relay/buzzer/Led test
 * Developed by
 * Advanced Electronics Systems. Bengaluru.
 
 *------------------------------------------------------------------------
 * Controller	: LPC1768
 * Project		: ALS-SDA-ARMCTXM3-06
 
 * Description	: Coil of the relay is pulled up at one side and other side is controlled
 * by the controller via ULN2803 an inverting buffer. When Switch SW4 is Pressed ,high is sent 
 * from the controller for Relay, current flows through the coil. LED gets on and 
 * CN5 pin 1 and 2 gets short as well and low is sent from the controller then Buzzer will ON 
**************************************************************************/

#include <LPC17xx.H>
unsigned int count=0; 
int main(void)
{
	unsigned int i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL1 &= 0xFFF0FFFF;		//P0.25 GPIO
	LPC_GPIO0->FIODIR |= 0x03000000;		//P0.25 output
   while(1)
   {
	if(!(LPC_GPIO2->FIOPIN & 0x00000800))
	{
		for(i=0;i<10;i++)
		{
		LPC_GPIO0->FIOSET = 0x03000000;	//relay on
		for(i=0;i<10000;i++);

		}

  }	
	else
	{
	   LPC_GPIO0->FIOCLR = 0x03000000;	//relay off
	   for(i=0;i<100000;i++);
	}
	}
}											//end int main(void)



 