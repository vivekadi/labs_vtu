/**************************************************************************
 * Alphanumeric LCD
 * Developed by 													  
 * Advanced Electronics Systems, Bengaluru
 *-------------------------------------------------------------------------
 * Controller	: LPC1768
 * Project		: ALS-SDA-AMCTXM3-01
 * Port lines used: Data1 to Data4 - P0.23 to P0.26
 * En - P0.28. RS - P0.27, RW - Ground
 * Connection : CND to CNAB
 ***************************************************************************/

 #include <lpc17xx.h>

 #include "LCD.h"
 #include "libs.h"

 unsigned long int temp1=0, temp2=0 ;
 unsigned char Msg1[13]={"Sum 1 to 10:"};

 //lcd initialization
 void lcd_init()
 {
//	/* Ports initialized as GPIO */
//    LPC_PINCON->PINSEL3 &= 0xFC003FFF;  //P0.23 to P0.28
	  /* Ports initialized as GPIO */
    LPC_PINCON->PINSEL4 &= 0xFFF000FF;  //P2.4 to P2.9
	/* Setting the directions as output */
    LPC_GPIO2->FIODIR |= DT_CTRL;	
	LPC_GPIO2->FIODIR |= RS_CTRL;	
	LPC_GPIO2->FIODIR |= EN_CTRL;	
        
    clear_ports();
	delay_lcd(3200);

	temp2 = (0x30<<2);
	wr_cn();	   
	delay_lcd(30000); 
		
	temp2 = (0x30<<2);
	wr_cn();
	delay_lcd(30000);	 
		
	temp2 = (0x30<<2);
	wr_cn();
	delay_lcd(30000);

	temp2 = (0x20<<2);
	wr_cn();
	delay_lcd(30000);

	temp1 = 0x28;
	lcd_com();
	delay_lcd(30000);
		
	temp1 = 0x0c;		
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x06;
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
	
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
    return;
 }

 void lcd_com(void)
 {
	temp2 = temp1 & 0xf0;				//move data (26-8+1) times : 26 - HN place, 4 - Bits
	temp2 = temp2 << 2;					//data lines from 23 to 26
	wr_cn();
	temp2 = temp1 & 0x0f; 				//26-4+1
	temp2 = temp2 << 6; 
	wr_cn();
	delay_lcd(1000);
    return;
 }

 // command nibble o/p routine
 void wr_cn(void)                        //write command reg
 { 	 
		clear_ports();
	LPC_GPIO2->FIOPIN = temp2;			//Assign the value to the data lines    
    LPC_GPIO2->FIOCLR = RS_CTRL;		//clear bit RS
	LPC_GPIO2->FIOSET = EN_CTRL;   		//EN=1
	delay_lcd(25);
	LPC_GPIO2->FIOCLR = EN_CTRL;		//EN =0
    return;
    
 }

 // data o/p routine which also outputs high nibble first
 // and lower nibble next
 void lcd_data(void)
 {             
     temp2 = temp1 & 0xf0;
    temp2 = temp2 << 2;
    wr_dn();
    temp2= temp1 & 0x0f;	
    temp2= temp2 << 6;
    wr_dn();
    delay_lcd(1000);	
    return;
 } 

 // data nibble o/p routine
 void wr_dn(void)
 {  	  
	clear_ports();

	LPC_GPIO2->FIOPIN = temp2;			//Assign the value to the data lines    
	LPC_GPIO2->FIOSET = RS_CTRL;		//set bit  RS
	LPC_GPIO2->FIOSET = EN_CTRL;   		//EN=1
	delay_lcd(25);
	LPC_GPIO2->FIOCLR = EN_CTRL;		//EN =0
    return;
 }

 void delay_lcd(unsigned int r1)
 {
  	unsigned int r;
  	for(r=0;r<r1;r++);
    return;
 }

 void clr_disp(void)
 {
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
    return;
 }
 void clear_ports(void)
 {
    /* Clearing the lines at power on */
	LPC_GPIO2->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO2->FIOCLR = RS_CTRL;  //Clearing RS line
	LPC_GPIO2->FIOCLR = EN_CTRL; //Clearing Enable line
        
    return;
 }

 void lcd_puts(unsigned char *buf1)
 {
    unsigned int i=0;

    while(buf1[i]!='\0')
    {
        temp1 = buf1[i];
     	lcd_data();
		i++;
        if(i==16)
		{
           	temp1 = 0xc0;
			lcd_com();
		}
         
       }
    return;
 }

 
 void LCD_DISP(unsigned int val)
 {
 	unsigned char var1,var2;

	lcd_init();

	temp1 = 0x80;		// display the initial message at 1st line of LCD
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg1);

	var1 = (unsigned char)val;	// toke the hex result and convert into decimal value
	var1 = hex_dec(var1);
	var2 = var1;

	var1 &= 0xF0;
	var1 >>= 4;
	var1 = hex_ascii(var1);	   //convert the higher nibble into ascii

	temp1 = 0x8C;			   // display the higher nibble
	lcd_com();
	delay_lcd(800);
	lcd_puts(&var1);

	var1 = var2;			   // convert the lower nibble and display on LCD
	var1 &= 0x0F;
	var1 = hex_ascii(var1);

	temp1 = 0x8D;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&var1);
 }


