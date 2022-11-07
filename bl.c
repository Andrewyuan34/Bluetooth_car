#include "bl.h"

uint8_t aRxBuffer[5]={0,0,0,0,0};//Bluetooth receiver Cache


// USART interruption server
void USART2_IRQHandler(void)
{
	uint8_t res = 0;
	static uint8_t rxConut=0;
	//receive
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE) != RESET)
	{
	HAL_UART_Receive(&huart2,&res,1,1000);
	//put data into Cache
	if(rxConut < 6)
	{
		aRxBuffer[rxConut] = res;
		rxConut++;
	}
	__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
	}
	//free interruption
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE) != RESET)
	{
		HAL_UART_Transmit(&huart2,aRxBuffer, rxConut,1000);//receive one byte
		
		memcpy((char*)Buffer,aRxBuffer,rxConut);//copy data
    //Car_Data(aRxBuffer, rxConut);	
		rxConut = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		Falg=1;
	}
}

//process data
void Car_Data(uint8_t *buf, uint8_t len )
{
	if ((char)buf[0]!='A'	)
	 return;
	if ((char)buf[1]=='0'	)
	{
		if(xj==0)
		{	
			if ((char)buf[2]=='1'	)
			{
				if(Fa_s==0)
				Car_advance();//前进
			}
			  
			else if ((char)buf[2]=='2')
				Car_back();//后退
			else if ((char)buf[2]=='3')
				Car_L();//左
			else if ((char)buf[2]=='4')
				Car_R();//右转
	  } 
		if ((char)buf[2]=='0'	)
		  Car_S();//停止
	}
	else if ((char)buf[1]=='1')
	{
	 if ((char)buf[2]=='1' )
	 {Car_S();//停止
		 xj=0;}
	 else if((char)buf[2]=='2' )
		 xj=1;
	}
	   
}

