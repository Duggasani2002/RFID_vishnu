#include <LPC21xx.H>
#include"header.h"
#include<string.h>
s8 time[4];

u32 menu_display(void)	 //MENU
{
 u32 temp;
 uart0_tx_string("choose the option \r\n 1)add details \r\n 2)take attandance \r\n 3)show details \r\n 4)set time \r\n 5)hours worked \r\n 6)save data\r\n");
 uart0_tx_string("op : ");
 temp=uart0_rx();
 uart0_tx(temp);
 uart0_tx_string("\r\n");
 return temp;
}






void add_details(u32 i)			//ADD DETAILS OF EMPLOYEE
{
  //uart0_tx_string("add the rfid num and name \r\n");
  RFID_rx_string(&SD[i]);
  uart0_tx_string("\r\n");
}


void set_time(void)
{
	u8 ss=0x00,mm=0x00,hh=0x00;
	uart0_tx_string("enter the hours : ");
	uart0_rx_string(time,4);
	hh=hh|((time[0]&0xf)<<4);
	hh=hh|(time[1]&0xf);
	uart0_tx_string("\r\n");
	//uart0_tx_string(time);
	//uart0_tx_string("\r\n");
	//uart0_tx_hex(hh);
	//uart0_tx_string("\r\n");
	uart0_tx_string("enter the minutes : ");
	uart0_rx_string(time,4);
	mm=mm|((time[0]&0xf)<<4);
	mm=mm|(time[1]&0xf);
	//uart0_tx_string("\r\n");
	//uart0_tx_string(time);
	//uart0_tx_string("\r\n");
	//uart0_tx_hex(mm);
	uart0_tx_string("\r\n");
	uart0_tx_string("enter the seconds : ");
	uart0_rx_string(time,4);
	ss=ss|((time[0]&0xf)<<4);
	ss=ss|(time[1]&0xf);
	//uart0_tx_string("\r\n");
	//uart0_tx_string(time);
	//uart0_tx_string("\r\n");
	//uart0_tx_hex(ss);
	uart0_tx_string("\r\nnow the time is : ");
	i2c_byte_write_frame(0XD0,0X0,ss);
	i2c_byte_write_frame(0XD0,0X1,mm);
	i2c_byte_write_frame(0XD0,0X2,hh);
	ss=i2c_byte_read_frame(0XD0,0X0);
	mm=i2c_byte_read_frame(0XD0,0X1);
	hh=i2c_byte_read_frame(0XD0,0X2);
	uart0_tx_hex(hh);
	uart0_tx(':');
	uart0_tx_hex(mm);
	uart0_tx(':');
	uart0_tx_hex(ss);
	uart0_tx_string("\r\n");
	
}

void store_data(void)
{
	u32 i,j;
	u8 mr;
	for(i=0,j=0;i<4;i++,j+=16)
	{
		mr=0x00;
		mr=mr|j;
		i2c_page_write_frame(0xA0,mr,SD[i].name);
	}
	for(i=0,j=0;i<4;i++,j+=16)
	{
		mr=0x00;
		mr=mr|j;
		i2c_page_write_frame(0xA0,mr,SD[i].rollno);
	}
}


u32 hexatodecimal(u8 ch)
{
	u32 d=0;
	d+=((ch/0x10)*10);
	d+=ch%0x10;
	return d;
}	
	

s8 RO_NO[12];
void run_RFID(void)				//taking the attandance
{
	u8 ss=0x00,mm=0x00,hh=0x00;
	u32 i;
	uart0_tx_string("enter the stop for exit\r\n");
	L1:
  while(1)
	{
		//define the switch is pressed break the while
			// break;
		uart0_tx_string("running the RFID : ");
		uart0_rx_string(RO_NO,12); 		//scan the rfid 
		uart0_tx_string("\r\n");
		if(strcmp(RO_NO ,"stop")==0)
			 break;
		for(i=0;i<SIZE;i++)
		{
			if(strcmp(RO_NO , SD[i].rollno)==0)
			{
				if(SD[i].flag=='0') 					//in time
				{	
             hh=0x08;
             mm=0x26;
             ss=0x45;					
            ss=i2c_byte_read_frame(0XD0,0X0);
            mm=i2c_byte_read_frame(0XD0,0X1);
	          hh=i2c_byte_read_frame(0XD0,0X2);					//rtc read time
	          SD[i].in_time[0]=hexatodecimal(hh);					//store in in_time
					  SD[i].in_time[1]=hexatodecimal(mm);
					  SD[i].in_time[2]=hexatodecimal(ss);
				    SD[i].flag='1';      //flag++
					  uart0_tx_string("\r\n");
					  for(int j=0;j<3;j++)
					   {
					       uart0_tx_integer(SD[i].in_time[j]);
							   uart0_tx(':');
						 }
					  uart0_tx_string("\r\n welcome ");
						lcd_string("welcome");
						lcd_cmd(0xc0);
						lcd_string(SD[i].name);
					  uart0_tx_string(SD[i].name);
					  uart0_tx_string("\r\n");
					 goto L1;
				}
				if(SD[i].flag=='1')                        //out time
				{
					   hh=0x16;
             mm=0x15;
             ss=0x57;	
					  ss=i2c_byte_read_frame(0XD0,0X0);
            mm=i2c_byte_read_frame(0XD0,0X1);
	          hh=i2c_byte_read_frame(0XD0,0X2);    //rtc read time
					  SD[i].out_time[0]=hexatodecimal(hh);	    //store in out_time
					  SD[i].out_time[1]=hexatodecimal(mm);
					  SD[i].out_time[2]=hexatodecimal(ss);
				    SD[i].flag='2';     //flag++ 
					  uart0_tx_string("\r\n");
					  for(int j=0;j<3;j++)
					   {
					       uart0_tx_integer(SD[i].out_time[j]);
							   uart0_tx(':');
						 }
					  uart0_tx_string("\r\n thanq ");
					  uart0_tx_string(SD[i].name);
					  uart0_tx_string("\r\n");
				}
				if(SD[i].flag=='2')
			  {
					s32 val;
					u8 mr;
					u8 data;
					u32 HH_work[3];
				  for(int j=0;j<3;j++){       //store the no of hours worked
						val=SD[i].out_time[j] - SD[i].in_time[j];
						if(val >= 0)
							HH_work[j]=val;
						else
							HH_work[j]=-val;
					}
				    SD[i].flag='0';     //flag=0
					uart0_tx_string("hours worked added to memory :  ");
					val=i*16;
					for(int j=0;j<3;j++)
					{
						mr=mr|val;
						data=data|HH_work[j];
						i2c_byte_write_frame(0XA0,mr,data);                //store the data in EEPEOM
						++val;
					}
					 for(int j=0;j<3;j++)
					{
						uart0_tx_integer(HH_work[j]);
							   uart0_tx(':');
					}
					uart0_tx_string("\r\n");
					 goto L1;
			  }	
			}
		}
	}
	return;
	//menu_display();
}





void hours_worked(void)
{
	u32 i;
	s8 RO_NO[12];
	uart0_tx_string("enter the rollno : ");
	uart0_rx_string(RO_NO,12);                                 //enter the roll no
  for(i=0;i<3;i++)                      	//if matches
  {
		if(SD[i].rollno==RO_NO)
		{
			                                  
		}
	}		
	//print the value is above address	
	
}





void show_details(void)
{
  u32 i;
  uart0_tx_string("NAME	| ROLL NO | flag | IN Time | OUT Time\r\n");
  for(i=0;i<SIZE;i++)
  {
    uart0_tx_string(SD[i].name);
	  uart0_tx_string("	| ");
	  uart0_tx_string(SD[i].rollno);
		uart0_tx_string("	| ");
	  uart0_tx(SD[i].flag);
		uart0_tx_string("	| ");
		for(int j=0;j<3;j++){
		uart0_tx_integer(SD[i].in_time[j]);
		uart0_tx(':');
		}
		uart0_tx_string("	| ");
		for(int j=0;j<3;j++){
		uart0_tx_integer(SD[i].out_time[j]);
		uart0_tx(':');
		}
	  uart0_tx_string("\r\n");
  }
}




#define THRE ((U0LSR>>5)&1)
#define RDR ((U0LSR)&1)
void RFID_rx_string(EMP* ptr)
{
 s32 i;
	ptr->flag='0';
 uart0_tx_string("scan the RFID card: ");
 for(i=0;i<12;i++)
 {
   while(RDR==0);
   ptr->rollno[i]=U0RBR;
   U0THR=ptr->rollno[i];
   while(THRE==0);
   if(ptr->rollno[i]=='\r')
    break;
 }
 ptr->rollno[i]='\0';
 uart0_tx_string("\r\n");

 uart0_tx_string("enter the name: ");
 for(i=0;i<20;i++)
 {
   while(RDR==0);
   ptr->name[i]=U0RBR;
   U0THR=ptr->name[i];
   while(THRE==0);
   if(ptr->name[i]=='\r')
    break;
 }
 ptr->name[i]='\0';
}
