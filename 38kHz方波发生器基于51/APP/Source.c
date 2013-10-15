#include "stc12c5a.h"

sbit ExtInt0 = P3^2;	//外部中断0
sbit LED0 = P0^0;
void Delay_us(unsigned int time)
{
	while(time--);
}

void Exti0_Init() //中断初始化函数
{
	TCON = 0x00;	//外部中断0低电平触发
	EX0=1;
	EA=1;
}

void main()
{
	ExtInt0 = 1;
	Exti0_Init();
	P1M1=0xFF;
	P1M0=0xFF;
	while(1)
	{
		P1=0X00;
		Delay_us(18);
		P1=0Xff;
		Delay_us(16);
	}		
}

void  Exti0_Handle() interrupt 0 using 0
{ 	 
	P1=0Xff;
	LED0=0; 	 
} 