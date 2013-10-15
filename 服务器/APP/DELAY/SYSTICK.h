#ifndef	 _SYSTICK_

#include "stm32f10x.h"
#define _SYSTICK_

extern uint32_t Time_us_Delay;
void SysTick_CONFIG(void);
void SysTick_Handler(void);
void Delay_us(uint32_t time);
void Delay_ms(uint32_t time);

#endif
