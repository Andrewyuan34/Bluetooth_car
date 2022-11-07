#include "bl.h"

uint8_t aRxBuffer[5]={0,0,0,0,0};//蓝牙接收缓存


// 串口中断服务函数
void USART2_IRQHandler(void)
{
	uint8_t res = 0;
	static uint8_t rxConut=0;
	//接收中断
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE) != RESET)
	{
	HAL_UART_Receive(&huart2,&res,1,1000);
	//将数据放入缓冲区
	if(rxConut < 6)
	{
		aRxBuffer[rxConut] = res;
		rxConut++;
	}
	__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
	}
	//空闲中断
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE) != RESET)
	{
		HAL_UART_Transmit(&huart2,aRxBuffer, rxConut,1000);//一帧数据接收完成
		
		memcpy((char*)Buffer,aRxBuffer,rxConut);//备份数据
    //Car_Data(aRxBuffer, rxConut);	
		rxConut = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		Falg=1;
	}
}

//处理接收到的数据
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

