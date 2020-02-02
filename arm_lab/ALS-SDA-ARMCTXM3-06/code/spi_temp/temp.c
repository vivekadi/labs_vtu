/***************************************************************************************
 * EXP11:Temperature sensor Interface through SPI
 * Developed by
 * Advanced Electronics Systems, Bengaluru

 *-------------------------------------------------------------------------------
 * Controller	: LPC1768
 * Project		: ALS-SDA-ARMCTXM3-06
 
 * Description	: Through this software Channel 1 of ADC IC MCP3202 is selected. Channel 1 is LM335
 * The value is read from MCP3202 in digital format. Average of 8 values are taken.
 * Analog value of the Average is taken and then it is converted into deg celcius format.
 * A value is then converted to ASCII format through sprintf statement and sent to 
 * serial port. Port lines used : MISO - P0.17. MOSI - P0.18. SCK - P0.15. SSEL - P0.7
 * CN7.1 to JP1.3. CN7.2 to JP1.2. CN7.3 to JP1.4 and CN7.17 to JP1.7


//------------------Temperature Calculation------------------------------------//

  For 0 deg C --> 273K and according to LM335 datasheet 10mV is increased for every 1 Kelvin
  For 273K  --> we will get 2731mV and VREF = 5100mV(you have to measure bcz board to board it can change)

  For Example : Assume that Current Temperature 27 deg C so
  				
			  analog_val = (float) ( avg * (float)VREF)/(float)FULLSCALE ;

			  I will get analog_val = 2999mV for 27deg C
				
				0'C -----------------> 273K------------->2731mV
				T in C---------------> T in K----------->2999mV

				so T in K = (2999mV * 273K)/(2731mV);
						  =  299K

			temp_valK = (float)( (analog_val * 273.14)/(2731.4));		 //temperature in deg K

				   T in C =  T in K - 273
				   		  = 299 - 273
						  = 27
		      
			  temp_valC	= temp_valK - 273.14;	 

 ***************************************************************************************/
#include <LPC17xx.h>
#include <stdio.h>
#include "UART0.h"
#include "SPI.h"

#define VREF		5350 // NOTE: VREF voltage will be changes from one power supply to another,so user must measure the voltage at TP1(+5V)(positive probe/Red of Meter) w.r.t TP2(GND)(Negative probe/Black)
										//using Multi Meter and the range will be 5.000V to 5.300V.That measured voltage should be written in Code in milliVolts.

#define FULLSCALE	4095 
#define SSEL		0x00010000

unsigned char temp1=0x00;
unsigned int up4bits,low8bits;
unsigned char *ptr,*ptr1,adc_val[8],temp_float[12];
//unsigned char adc_op[]= " ADC O/P = ";
unsigned char temp_op[]= "TEMP('C)=";
float analog_val,temp_valK,temp_valC;
volatile unsigned long i=0,j = 0;
unsigned int avg;

int main(void)
{
	LPC_PINCON->PINSEL1 &= 0xFFFFFFFC;	//P0.16 GPIO
	LPC_GPIO0->FIODIR |= SSEL;			//CHIPSELECT LINE MADE AS O/P P0.7
	LPC_GPIO0->FIOSET = SSEL;			//if device is powered up with CS low, set high before comm
	for(j=0;j<1000;j++);				//delay 
        
	UART0_Init();						//Initializes UART0 
	SPI_Init();							//Initializes SPI
 
	spi_flag=0;

	while(1)
	{
		for(i=0;i<8;i++)
		{							
			LPC_GPIO0->FIOCLR = SSEL;	//make SS low
			for(j=0;j<1000;j++);

        	LPC_SPI->SPDR = 0x01;		//Send the start bit

        	while(spi_flag == 0);
        	spi_flag = 0;

        	LPC_SPI->SPDR = 0xC0;		//Select channel1 in single ended mode & MSB first format
        
			while(spi_flag == 0);
        	spi_flag = 0;
        	up4bits = temp;				//temp has SPI data register value 
		       
        	LPC_SPI->SPDR = 0x00;

			while(spi_flag == 0);		//while((temp = S1SPSR) != 0X80);//while(((temp = S1SPSR)& 0x80) != 0X80);//while((flag == 0x00)&& ((temp = S1SPSR) == 0X80));
        	spi_flag = 0;
        	low8bits = temp;			//SPI Data Register.
			up4bits = up4bits & 0x0f;      	        
			up4bits <<= 8;       		//shift to the MSB side
			low8bits|=up4bits; 			//combine the lower bits and upper bits
			avg += low8bits;		 

			LPC_GPIO0->FIOSET = SSEL;	//make SS high

			for(j=0;j<1000;j++);
			
	  	}
	  	
		avg >>= 3;						//right shifted to get the avg of 8 

	  analog_val = (float) ( avg * (float)VREF)/(float)FULLSCALE ;
	  
	   
     temp_valK = (float)( (analog_val * 273.14)/(2731.4));		 //temperature in deg K
	  temp_valC	= temp_valK - 273.14;							 //temperature in deg C
      sprintf(temp_float,"%3.2f",temp_valC);	
			
		avg = 0x00;		
					ptr = temp_op;
        while(*ptr!='\0')
        {
        	LPC_UART0->THR = *ptr++; 
			while(tx0_flag == 0);
			tx0_flag= 0;
       	   for(j=0;j<200;j++); 
	    }
		LPC_UART0->THR = 0x20; 				//space between values displayed on the terminal;    
        while(tx0_flag == 0);
		tx0_flag= 0;		
      
	    ptr1 = temp_float;

        while(*ptr1!='\0')
        {
        	LPC_UART0->THR = *ptr1++; 
			while(tx0_flag == 0);
			tx0_flag= 0;
       		for(j=0;j<200;j++);
	    }      
        for(j=0;j<65000;j++); 				//delay for display // for 1 sec value 400000//for 10000 counts 25msec.
			
			
		LPC_UART0->THR = 0x0D; 				//new line
    while(tx0_flag == 0);
		tx0_flag= 0;		
			
    }
}
