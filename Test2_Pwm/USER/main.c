# include "stm32f10x.h"
# include "timer.h"
# include "key.h"
# include "usart.h"
# include "led.h"
# include "delay.h"
# include "beep.h"

u8 judge; // �жϣ�0=���ϵ磬1=��KEY0�������죬2=��KEY1������600msѭ��
u16 led0pwmval = 0; //PWM�Ƚ�ֵ ����ռ�ձ�
u8 dir = 1; // 1=����;0=�½�
u8 key;

int main(void){
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	     //���ڳ�ʼ��Ϊ9600
	KEY_Init();              //�����˿ڳ�ʼ��
	LED_Init();			     //LED�˿ڳ�ʼ��
	BEEP_Init();
	judge = 0;
	TIM2_Int_Init(4999, 7199);//�ϵ��LED0��500ms,��500ms
	
   	while(1)
	{
		key = GetKey();
		if(key){
			switch(key){
				case 2:{ // KEY1
					BEEP = 0;
					TIM3_PWM_Init(899, 0); // ����Ƶ��PWMƵ��=72000000/��899+1��=80kHz
					TIM2_Int_Init(5999, 7199); //600ms
					judge = 2;
					break;
				}
				case 1:{ // KEY0����������0.5s��ͣ0.5s
					judge = 1;
					TIM2_Int_Init(4999, 7199);
					break;
				}
			}
		}else{
			delay_ms(10);
		}
	}	 
}
