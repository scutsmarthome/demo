#include "stm32f10x.h"
#include "SYSTICK.h"
#include "USART.h"
#include "spi_enc28j60.h"
#include "web_server.h"
int main(void)
{
	SystemInit(); //ʱ��Ĭ��72M
	SysTick_CONFIG();
	USART_CONFIG();
	Delay_ms(100);
	printf("���ڳ�ʼ���ɹ�!\n");
	SPI_Enc28j60_Init();
	printf("SPI��ʼ���ɹ�!\n");
	Web_Server();
 	while(1)      //һ��Ҫ��ʹ��ʱ������������
	{
				
	}
}
