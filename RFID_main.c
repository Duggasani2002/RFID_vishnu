#include <LPC21xx.H>
#include"header.h"
EMP SD[SIZE];
int main()
{
 u32 i;
 u8 op;
 uart0_init(9600);
 lcd_init();
 i2c_init();
	i2c_slave_detect();
	i2c_eeprom_write_frame(0xA8,0x0010,'C');
	delay_ms(10);
	uart0_tx(i2c_eeprom_read_frame(0xA8,0x0010));
	uart0_tx_string("\r\n");
	i2c_eeprompage_write_frame(0xA0,0,"vishnu");
	delay_ms(10);
	i2c_eeprompage_read_frame(0xA0,0);
	uart0_tx_string("\r\n");
 while(1)
 {
   op=menu_display();
   if(op=='1')
   {
    for(i=0;i<SIZE;i++)
     add_details(i);  //add employee datails
   }
   else if(op=='2')
   {
    run_RFID();		   //aking attandance
   }
   else if(op=='3')
   {
     show_details();				   //employee details show
   }
	 else if(op=='4')
	 {
		 set_time();
	 }
	 else if(op=='5')
	 {
		 hours_worked();
	 }
	 else if(op=='6')
	 {
		 
	 }
   else
   {
     uart0_tx_string("selected wrong option \r\n");
   }
 }
}
