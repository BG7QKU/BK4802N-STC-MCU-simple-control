//Connection:
//BK4802N    STC8Fxxx
//______________________
//SCL(pin17)  -> P3.3(see BK4802NIIC.H)
//SDA(PIN18)  -> P3.2(see BK4802NIIC.H)
//TRX(PIN23)  -> P5.4
//______________________
//This is STC8FXXX MCU control BK4802N TRX simple test C program main function.
//Abot STC8Fxx MCU, pleae see: WWW.STCMCU.COM
//(c)BG7QKU 1,Dec 2019. E-mail:1027630917@qq.com
//Caution:The IRC freqency set to 5.5296MHz when you down hex to MCU.
#include "STC8F.h"
#include "intrins.h"
#include "BK4802NIIC.h"
sbit ppt=P5^4;
sbit test=P5^5;//test(p5.5) connect a LED to GND to indict IIC RUN.
//DEFAULT FERQ:TX=RX=439.725mh.uSING "BK4802NCalc.exe to calculate.
int rxfreq[]={
0x52BE,0xF850,0x0000};
int txfreq[]={
0x52C5,0x925F,0x0000};
int rxreg[]={ 
0x0300,
0x8e04,
0xF140,
0xED00,
0x17E0,
0xe0e0,
0x8543,
0x0700,
0xA066,
0xFFFF,
0xFFE0,
0x07a0,
0x9E3C,
0x1F00,
0xD1D1,
0x200F,
0x01FF,
0xE000,
0x0340
 };
 int txreg[]={
0x7C00,
0x0c04,
0xF140,
0xED00,
0x3fE0,
0xe0e0,
0x8543,
0x0700,
0xA066,
0xFFFF,
0xffe0,
0x061f,
0x9e3c,
0x1f00,
0xd1C1,
0x200f,
0x01FF,
0xE000,
0x0c00
};
void main()
{
	unsigned char i;
	unsigned char k=0;
	test=0;
  Delay50ms();//NOT delay less than 50 ms for setup.
	writing(0x90,23,0xa8,0XD0);//start to init to RX.
	for(i=4;i<=22;i++)
	    {
				writing(0x90,i,HIGHBYTE(rxreg[i-4]),LOWBYTE(rxreg[i-4]));
			}
			
		 for(i=5;i>2;i--)
		 {
			 writing(0x90,i-3,HIGHBYTE(rxfreq[i-3]),LOWBYTE(rxfreq[i-3]));
		 }
		 test=1;
		  while(1)
		{
			if(ppt==1&&k==0)//Set to TX if PTT =HIGH.
			{
				test=0;
				Delay30ms();
				if(ppt==1)
				{
					Delay30ms();
					  for(i=4;i<=22;i++)
	       {
				   writing(0x90,i,HIGHBYTE(txreg[i-4]),LOWBYTE(txreg[i-4]));
			    }
			
		      for(i=5;i>2;i--)
		      {
			     writing(0x90,i-3,HIGHBYTE(txfreq[i-3]),LOWBYTE(txfreq[i-3]));
		      }
					Delay30ms();
					test=1;
					k=1;
				}
			}
				if(ppt==0&&k==1)//Set to RX.
				{
					test=0;
					Delay30ms();
				if(ppt==0)
				{
					Delay30ms();
					writing(0x90,23,0xa8,0XD0);
					  for(i=4;i<=22;i++)
	       {
				   writing(0x90,i,HIGHBYTE(rxreg[i-4]),LOWBYTE(rxreg[i-4]));
			    }
			
		      for(i=5;i>2;i--)
		      {
			     writing(0x90,i-3,HIGHBYTE(rxfreq[i-3]),LOWBYTE(rxfreq[i-3]));
		      }
					Delay30ms();
					test=1;
					k=0;
			  }
		   }
   }
}
