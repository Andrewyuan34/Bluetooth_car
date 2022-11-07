#include "motor.h"
#include "main.h"


void ID_int()
{
  HAL_UART_Transmit_IT(&huart3,(uint8_t *)"#255PID006!",11);//修改id号
}

//ID号：左前7，左后6，右前8，右后9


void Car_state()
{
	
  if(speed_l==speed_r&&speed_r==1500)
	sprintf((char*)str,"   State:  Stop     ");				
	else if(speed_l==speed_r&&speed_r>1500)
	{
		sprintf((char*)str,"   State:  Forward  ");	
		if(Fa_s==1)
	  {
			Car_S();
		  sprintf((char*)str,"   State:  Stop     ");
		}
	}
	
	else if(speed_l==speed_r&&speed_r<1500)
	sprintf((char*)str,"   State:  Back off ");
	else if(speed_l>speed_r)
	sprintf((char*)str,"   State:  Right    ");
	else if(speed_l<speed_r)
	sprintf((char*)str,"   State:  Left     ");		
}

void Car_mode()
{
	
	if(xj==0)
	{sprintf((char*)mode_c,"   Mode:   Remote   ");}	
	else 
	{sprintf((char*)mode_c,"   Mode:   Track    ");}

}

void Car_advance()//前进
{
	speed_l=speed_r=1900;
  printf("#006P%04dT0000!#007P%04dT0000!#008P%04dT0000!#009P%04dT0000!",speed_l,speed_l,speed_r,speed_r);
}

void Car_back()//后退
{
	speed_l=speed_r=1100;
  printf("#006P%04dT0000!#007P%04dT0000!#008P%04dT0000!#009P%04dT0000!",speed_l,speed_l,speed_r,speed_r);
}

void Car_L()//左转
{
	speed_l=900;
	speed_r=2100;
  printf("#006P%04dT0000!#007P%04dT0000!#008P%04dT0000!#009P%04dT0000!",speed_l,speed_l,speed_r,speed_r);
}

void Car_R()//右转
{
	speed_l=2100;
	speed_r=900;
  printf("#006P%04dT0000!#007P%04dT0000!#008P%04dT0000!#009P%04dT0000!",speed_l,speed_l,speed_r,speed_r);
}
void Car_S()//停止
{
	speed_l=speed_r=1500;
  printf("#006P%04dT0000!#007P%04dT0000!#008P%04dT0000!#009P%04dT0000!",speed_l,speed_l,speed_r,speed_r);
}

