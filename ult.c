#include "ult.h"
 
float distant;      //测量距离
uint32_t measure_Buf[3] = {0};   //存放定时器计数值的数组
uint8_t  measure_Cnt = 0;    //状态标志位
uint32_t high_time;   //超声波模块返回的高电平时间
 
 
//===============================================读取距离
void SR04_GetData(void)
{
switch (measure_Cnt){
	case 0:

		TRIG_H; 
		HAL_Delay(30);
		TRIG_L;

		measure_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5)                                                                                  		
		break;
	
	case 3:
		high_time = measure_Buf[1]- measure_Buf[0];    //高电平时间							
		distant=(high_time*0.034)/2;  //单位cm        
		measure_Cnt = 0;  //清空标志位
		TIM2->CNT=0;     //清空计时器计数
		CR_d=distant;
		if(CR_d<15&&CR_d>0)
			Fa_s=1;
    else Fa_s=0;		
		break; 				
	}
}
 
 
//===============================================中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(TIM2 == htim->Instance)// 判断触发的中断的定时器为TIM2
	{
		switch(measure_Cnt){
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_2); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;                           
		}
	
	}
	
}

