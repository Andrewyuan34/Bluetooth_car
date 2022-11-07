#include "ult.h"
 
float distant;      //��������
uint32_t measure_Buf[3] = {0};   //��Ŷ�ʱ������ֵ������
uint8_t  measure_Cnt = 0;    //״̬��־λ
uint32_t high_time;   //������ģ�鷵�صĸߵ�ƽʱ��
 
 
//===============================================��ȡ����
void SR04_GetData(void)
{
switch (measure_Cnt){
	case 0:

		TRIG_H; 
		HAL_Delay(30);
		TRIG_L;

		measure_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);	//�������벶��       ����: __HAL_TIM_ENABLE(&htim5)                                                                                  		
		break;
	
	case 3:
		high_time = measure_Buf[1]- measure_Buf[0];    //�ߵ�ƽʱ��							
		distant=(high_time*0.034)/2;  //��λcm        
		measure_Cnt = 0;  //��ձ�־λ
		TIM2->CNT=0;     //��ռ�ʱ������
		CR_d=distant;
		if(CR_d<15&&CR_d>0)
			Fa_s=1;
    else Fa_s=0;		
		break; 				
	}
}
 
 
//===============================================�жϻص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(TIM2 == htim->Instance)// �жϴ������жϵĶ�ʱ��ΪTIM2
	{
		switch(measure_Cnt){
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ.
				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_2); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;                           
		}
	
	}
	
}

