#include <LPC21xx.H>
#include"header.h"

void i2c_init(void)
{
  PINSEL0|=0X50;  //P0.2-->SCL
                  //P0.3-->SDA
  I2SCLH=I2SCLL=75;
  I2CONSET=(1<<6);
}

#define SI ((I2CONSET>>3)&1)
void i2c_byte_write_frame(u8 sa,u8 mr,u8 data)
{
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=mr;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=data;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
}

void i2c_eeprom_write_frame(u8 sa,u16 mr,u8 data)
{
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=(u8)((mr >> 8) & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);
	
 I2DAT=(u8)(mr & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=data;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
}

void i2c_eeprompage_write_frame(u8 sa,u16 mr,u8* ptr)
{
	u8 name[10]="vishnu";
	u32 i;
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=(u8)((mr >> 8) & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);
	
 I2DAT=(u8)(mr & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);

 for(i=0;i<16;i++){
 I2DAT=name[i];
 I2CONCLR=(1<<3);
 while(SI==0);
 }
 
 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
}

//void i2c_eeprompage_read_frame(u8 sa,u16 mr)
//{
//u32 i;
// u8 temp=0;
// I2CONSET=(1<<5);
// I2CONCLR=(1<<3);
// while(SI==0);
// I2CONCLR=(1<<5);

// I2DAT=sa;
// I2CONCLR=(1<<3);
// while(SI==0);

// I2DAT=(u8)((mr >> 8) & 0xFF);;
// I2CONCLR=(1<<3);
// while(SI==0);
//	
// I2DAT=(u8)(mr & 0xFF);
// I2CONCLR=(1<<3);
// while(SI==0);

// I2CONSET=(1<<5);
// I2CONCLR=(1<<3);
// while(SI==0);
// I2CONCLR=(1<<5);

// I2DAT=sa|1;
// I2CONCLR=(1<<3);
// while(SI==0);

// for(i=0;i<16;i++){
// I2CONCLR=(1<<3);
// while(SI==0);
// temp=I2DAT;
// uart0_tx(temp);
// }

// I2CONSET=(1<<4);
// I2CONCLR=(1<<3);
// return ;
//}


void i2c_eeprompage_read_frame(u8 sa,u16 mr)
{
u32 i;
 u8 temp=0;
//dummy write start	
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=(u8)((mr >> 8) & 0xFF);;
 I2CONCLR=(1<<3);
 while(SI==0);
	
 I2DAT=(u8)(mr & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);	
//dummy write stop


//sequential read	start
 for(i=0;i<16;i++){	
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa|1;
 I2CONCLR=(1<<3);
 while(SI==0);

 
 I2CONCLR=(1<<3);
 while(SI==0);
 temp=I2DAT;
 uart0_tx(temp);
 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
 	 
 }
//sequential read	stop
 return ;
}

u8 i2c_eeprom_read_frame(u8 sa,u16 mr)
{
 u8 temp=0;
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=(u8)((mr >> 8) & 0xFF);;
 I2CONCLR=(1<<3);
 while(SI==0);
	
 I2DAT=(u8)(mr & 0xFF);
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa|1;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONCLR=(1<<3);
 while(SI==0);
 temp=I2DAT;

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
 return temp;
}

u8 i2c_byte_read_frame(u8 sa,u8 mr)
{
 u8 temp=0;
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=mr;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa|1;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONCLR=(1<<3);
 while(SI==0);
 temp=I2DAT;

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
 return temp;
}


void i2c_page_write_frame(u8 sa,u8 mr,u8 *data)
{
	u32 i;
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=mr;
 I2CONCLR=(1<<3);
 while(SI==0);
 
 for(i=0;i<16;i++)
{
 I2DAT=data[i];
 I2CONCLR=(1<<3);
 while(SI==0);
 delay_ms(10);
}

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
}


void i2c_page_read_frame(u8 sa,u8 mr)
{
 u32 i;
 u8 temp=0;
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2DAT=mr;
 I2CONCLR=(1<<3);
 while(SI==0);

 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);

 I2DAT=sa|1;
 I2CONCLR=(1<<3);
 while(SI==0);

 for(i=0;i<16;i++)
 {
 I2CONCLR=(1<<3);
 while(SI==0);
 temp=I2DAT;
 uart0_tx(temp);
 }

 I2CONSET=(1<<4);
 I2CONCLR=(1<<3);
}

void i2c_slave_detect(void)
{
  /*u32 i;
  for(i=0;i<255;i=1+2)
  {
      I2CONSET=(1<<5);
	  I2CONCLR=(1<<3);
	  while(SI==0);
	  I2CONCLR=(1<<5);

	  I2DAT=i;
	  I2CONCLR=(1<<3);
	  while(SI==0);
	  if(I2STAT==0x18)
	   {
	     uart0_tx_string("\r\n slave addt : 0x");
		 uart0_tx_hex(i);
	   }

	  I2CONSET=(1<<4);
	  I2CONCLR=(1<<3);
  }*/
  u32 i,j;
  u8 temp;
  for(i=0;i<=15;i++)
  {
    for(j=0;j<=15;j+=2)
	{
	  temp=0;
	  I2CONSET=(1<<5);
	  I2CONCLR=(1<<3);
	  while(SI==0);
	  I2CONCLR=(1<<5);

	  temp|=i<<4;
	  temp|=j;

	  I2DAT=temp;
	  I2CONCLR=(1<<3);
	  while(SI==0);

	  if(I2STAT==0X18)
	  {
	    uart0_tx_hex(temp);
		uart0_tx('\r');
	  }
	  I2CONSET=(1<<4);
	  I2CONCLR=(1<<3);
	}
  }	  
}

