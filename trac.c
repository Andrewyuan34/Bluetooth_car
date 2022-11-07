#include "trac.h"
#include "main.h"

uint8_t by=0;//偏移标志

void Car_xj()
{
	uint8_t L=0,R=0;
	R=HAL_GPIO_ReadPin(IOL_GPIO_Port,IOL_Pin); //获得电平高低
	L=HAL_GPIO_ReadPin(IOR_GPIO_Port,IOR_Pin); //获得电平高低
  if(L==1&R==0)
  {speed_r=1000;
	speed_l=2100;
		by=1;
	}
	else if(L==0&R==1)
  {speed_r=2100;
	speed_l=1000;
	by=2;
	}
	else if(L==0&R==0)
	{speed_r=speed_l=1800;
		by=0;
	}
	else if(L==1&R==1)
	{
		 if(by==1)
		{speed_r=1000;
		speed_l=2100;
		}
		else if(by==2)
		{speed_r=2100;
		speed_l=1000;
		}
		else if(by==0)
		{
		  speed_r=1000;
	    speed_l=2100;
		}
	}
	if(Fa_s==1)
		speed_r=speed_l=1500;
	
  printf("#006P%dT0000!#007P%dT0000!#008P%dT0000!#009P%dT0000!",speed_l,speed_l,speed_r,speed_r);	
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==IOL_Pin)
	{
		if(by==0)
	  by=2;
	}
	else if(GPIO_Pin==IOR_Pin)
	{
		if(by==0)
	  by=1;
	}
}
