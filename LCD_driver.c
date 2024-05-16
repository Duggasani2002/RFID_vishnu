#include <LPC21xx.H>
#include"header.h"

#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)

void lcd_init(void)
{
 IODIR1|=0X00FE0000;
 PINSEL2=0;
 IOCLR1=EN;
 lcd_cmd(0x02);
 lcd_cmd(0x03);
 lcd_cmd(0x28);
 lcd_cmd(0x01);
}

void lcd_data(u8 data)
{
 u32 temp=0;
 IOCLR1=0X00FE0000;
 temp=(data&0xf0)<<16;
 IOSET1=temp;
 IOSET1=RS;
 IOCLR1=RW;
 IOSET1=EN;
 delay_ms(2);
 IOCLR1=EN;

 IOCLR1=0X00FE0000;
 temp=(data&0x0F)<<16;
 IOSET1=temp;
 IOSET1=RS;
 IOCLR1=RW;
 IOSET1=EN;
 delay_ms(2);
 IOCLR1=EN;
}


void lcd_cmd(u8 data)
{
 u32 temp=0;
 IOCLR1=0X00FE0000;
 temp=(data&0xf0)<<16;
 IOSET1=temp;
 IOCLR1=RS;
 IOCLR1=RW;
 IOSET1=EN;
 delay_ms(2);
 IOCLR1=EN;

 IOCLR1=0X00FE0000;
 temp=(data&0x0F)<<16;
 IOSET1=temp;
 IOCLR1=RS;
 IOCLR1=RW;
 IOSET1=EN;
 delay_ms(2);
 IOCLR1=EN;
}

void lcd_string(s8 *ptr)
{
 while(*ptr!=0)
 {
	 lcd_data(*ptr);
   ptr++;
 }
}

void delay_ms(u32 ms)
{
 T0PR=15000-1;
 T0PC=0;
 T0TC=0;
 T0TCR=1;
 while(T0TC<ms);
 T0TCR=0;
}
