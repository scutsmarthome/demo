#include "stm32f10x.h"
#include "SYSTICK.h"
#include "USART.h"
#include "spi_enc28j60.h"
#include "web_server.h"
int main(void)
{
	SystemInit(); //时钟默认72M
	SysTick_CONFIG();
	USART_CONFIG();
	Delay_ms(100);
	printf("串口初始化成功!\n");
	SPI_Enc28j60_Init();
	printf("SPI初始化成功!\n");
	Web_Server();
 	while(1)      //一定要先使能时钟再配置外设
	{
				
	}
}
