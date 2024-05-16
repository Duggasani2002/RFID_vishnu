#include <LPC21xx.H>
#include"header.h"
#include<stdio.h>
#define THRE ((U0LSR>>5)&1)
#define RDR ((U0LSR)&1)


void uart0_init(int baud)
{
  s32 a[]={15,60,30,0,15};
  u32 pclk=a[VPBDIV]*1000000,result;
  result=pclk/(16*baud);
  PINSEL0|=0X5;
  U0LCR=0x83;
  U0DLL=result&0xff;
  U0DLM=(result>>8)&0xff;
  U0LCR=0X03;
}

void uart0_tx(u8 data)
{
 U0THR=data;
 while(THRE==0);
}

u8 uart0_rx(void)
{
 while(RDR==0);
 return U0RBR;
}

void uart0_tx_string(s8 *ptr)
{
 while(*ptr!=0)
 {
   U0THR=*ptr;
   while(THRE==0);
   ptr++;
 }
}

void uart0_rx_string(s8* ptr,u8 max_bytes)
{
 s32 i;
 for(i=0;i<max_bytes;i++)
 {
   while(RDR==0);
   ptr[i]=U0RBR;
   U0THR=ptr[i];
   while(THRE==0);
   if(ptr[i]=='\r')
    break;
 }
 ptr[i]='\0';
}

void uart0_tx_integer(s32 num)
{
  s8 buf[10];
  sprintf(buf,"%d",num);
  uart0_tx_string(buf);
}

void uart0_tx_float(float num)
{
  s8 buf[10];
  sprintf(buf,"%.1f",num);
  uart0_tx_string(buf);
}

void uart0_tx_hex(u8 temp)
{
	//uart0_tx_string("0X");
  u8 t;
  t=((temp>>4)&0xf);
  if(t<10)
   uart0_tx(t+48);
  else
   uart0_tx(t-10+65);
  t=((temp)&0x0f);
  if(t<10)
   uart0_tx(t+48);
  else
   uart0_tx(t-10+65);
}
