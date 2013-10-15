#include "stm32f10x_conf.h"
#include "stdio.h"

#define EN_USRAT_SEND 1
#define EN_USART_RECEIVE 1

void USART_SEND_CONFIG(void)
{
#ifdef EN_USRAT_SEND
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
#else 

#endif
}
void USART_RECEIVE_CONFIG(void)
{
#ifdef EN_USART_RECEIVE
	GPIO_InitTypeDef GPIO_InitStruct;  
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct); 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0X01;
	NVIC_Init(&NVIC_InitStructure);  
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
#else 

#endif	
}

void USART_CONFIG(void)
{
#if defined (EN_USART_RECEIVE)||defined (EN_USRAT_SEND)
	USART_InitTypeDef USART_InitStruct; 
	USART_DeInit(USART1);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
#ifdef EN_USART_RECEIVE 
	USART_InitStruct.USART_Mode|=USART_Mode_Rx;
#endif
#ifdef EN_USRAT_SEND
	USART_InitStruct.USART_Mode|=USART_Mode_Tx;
#endif
	USART_InitStruct.USART_Parity=USART_Parity_No ;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_Init  (USART1,&USART_InitStruct);
	USART_SEND_CONFIG();
    USART_RECEIVE_CONFIG();
	USART_Cmd(USART1,ENABLE);
#else 

#endif
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	return (ch);
}

 void USART1_IRQHandler(void)
{
	uint16_t Data;
	while(USART_GetITStatus(USART1,USART_IT_RXNE)!=SET);
	Data=USART_ReceiveData (USART1); 
	printf("收到的数据是：%c \n",Data);
	USART_ClearFlag(USART1,USART_IT_RXNE);
}
