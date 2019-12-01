#define __BK4802NIIC_H_
#ifdef  __BK4802NIIC_H_

#include "STC8F.H"
// ------------------------------------------------------------
// IO口模拟I2C通信 Using software IIC bus.
// SCL->P3^3
// SDA->P3^2
// ------------------------------------------------------------
sbit SCL=P3^3; //串行时钟
sbit SDA=P3^2; //串行数据
#define high 1
#define low 0

char HIGHBYTE(int bi)//Get higer 8 bit
	 {
		 char highER ;
		 highER=bi>>8;
		 return highER;
	 }
char 	LOWBYTE(int bi)//Get lower 8 bit
	 {
		 char lowER;
		 lowER=bi&0xff;
		 return lowER;
	 }
void Delay()//For IIC
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}
void Delay50ms()		//@5.5296MHz
{
	unsigned char i, j, k;

	i = 2;
	j = 104;
	k = 12;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay30ms()		//@5.592MHZMHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 175;
	k = 110;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL = high;		
   SDA = high;
   SDA = low;
   SCL = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL = low;
   SDA = low;
   SCL = high;
   SDA = high;
}

/**********************************************
// 通过I2C总线写一个字节
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			SDA=high;
		else
			SDA=low;
		SCL=high;
		SCL=low;
		IIC_Byte<<=1;
	}
	SDA=1;
	SCL=1;
	SCL=0;
}

void writing(char ICaddforwrite,char hadd,char hdata,char ldata)//WRITE TO  BK4802N
	 {

    IIC_Start();	 //??????
    Write_IIC_Byte(ICaddforwrite);                          //??????+???
    Write_IIC_Byte(hadd); 
	  Write_IIC_Byte(hdata); 
		Write_IIC_Byte(ldata); 
		IIC_Stop();
		Delay();
	 }
	 
	 #endif