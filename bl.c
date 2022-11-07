#include "bl.h"

uint8_t aRxBuffer[5]={0,0,0,0,0};//�������ջ���


// �����жϷ�����
void USART2_IRQHandler(void)
{
	uint8_t res = 0;
	static uint8_t rxConut=0;
	//�����ж�
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE) != RESET)
	{
	HAL_UART_Receive(&huart2,&res,1,1000);
	//�����ݷ��뻺����
	if(rxConut < 6)
	{
		aRxBuffer[rxConut] = res;
		rxConut++;
	}
	__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
	}
	//�����ж�
	if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE) != RESET)
	{
		HAL_UART_Transmit(&huart2,aRxBuffer, rxConut,1000);//һ֡���ݽ������
		
		memcpy((char*)Buffer,aRxBuffer,rxConut);//��������
    //Car_Data(aRxBuffer, rxConut);	
		rxConut = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		Falg=1;
	}
}

//������յ�������
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
				Car_advance();//ǰ��
			}
			  
			else if ((char)buf[2]=='2')
				Car_back();//����
			else if ((char)buf[2]=='3')
				Car_L();//��
			else if ((char)buf[2]=='4')
				Car_R();//��ת
	  } 
		if ((char)buf[2]=='0'	)
		  Car_S();//ֹͣ
	}
	else if ((char)buf[1]=='1')
	{
	 if ((char)buf[2]=='1' )
	 {Car_S();//ֹͣ
		 xj=0;}
	 else if((char)buf[2]=='2' )
		 xj=1;
	}
	   
}

