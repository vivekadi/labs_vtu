/******************************************************************************
 * EXP1 : UART0 test Demonstration(To display HELLO WORLD)
 * Developed by
 * Advanced Electronics Systems. Bengaluru
 ----------------------------------------------------------------------------
 * Controller	: LPC1768
 * Project		: ALS-SDA-ARMCTXM3-06
 * Description	: In this example fixed string "HELLO WORLD" is displayed
 * on the Hyperterminal using Uart0 Feature.
 ----------------------------------------------------------------------------
*****************************************************************************/

#include<LPC17xx.h>

void delay(unsigned int r1);
void UART0_Init(void);
void UART0_IRQHandler(void);

unsigned long int r=0, i = 0;
unsigned char tx0_flag=0;
unsigned char *ptr, arr[] = "Hello world\r";

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	UART0_Init();
	while(1)
	{
		ptr = arr;
		while ( *ptr != '\0'){ 
			LPC_UART0->THR = *ptr++;
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			for (i=0; i<200; i++);
		}
		for (i=0; i<500; i++)
		delay(625);			//delay
	}
}

void UART0_Init(void)
{
	LPC_SC->PCONP |= 0x00000008;			//UART0 peripheral enable
	LPC_PINCON->PINSEL0 |= 0x00000050;
	LPC_UART0->LCR = 0x00000083;			//enable divisor latch, parity disable, 1 stop bit, 8bit word length
	LPC_UART0->DLM = 0X00; 
	LPC_UART0->DLL = 0x13;      			//select baud rate 9600 bps
	LPC_UART0->LCR = 0X00000003;
	LPC_UART0->FCR = 0x07;
	LPC_UART0->IER = 0X03;	   				//select Transmit and receive interrupt

	NVIC_EnableIRQ(UART0_IRQn);				//Assigning channel
}

void UART0_IRQHandler(void)
{
	unsigned long Int_Stat;
	Int_Stat = LPC_UART0->IIR;				//reading the data from interrupt identification register
	Int_Stat = Int_Stat & 0x06;				//masking other than txmit int & rcve data indicator

	if((Int_Stat & 0x02)== 0x02)			//transmit interrupt
		tx0_flag = 0xff;
}

void delay(unsigned int r1)
{
	for(r=0;r<r1;r++);
} 

