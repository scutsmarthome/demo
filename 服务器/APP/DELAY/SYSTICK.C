#include "stm32f10x.h"

uint32_t Time_us_Delay;

void SysTick_CONFIG(void)
{
	while(SysTick_Config(SystemCoreClock/1000000));
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;   //关闭滴答定时器
}

void Delay_us(uint32_t time)
{
	Time_us_Delay=time;
	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;   //开启滴答定时器
	while(Time_us_Delay);
}

void Delay_ms(uint32_t time)
{
	for(;time>0;time--)
		Delay_us(1000);	
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
	if(Time_us_Delay!=0)
		Time_us_Delay--;
}



