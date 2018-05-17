# include "stm32f10x.h"
# include "timer.h"
# include "key.h"
# include "usart.h"
# include "led.h"
# include "delay.h"
# include "beep.h"

u8 judge; // 判断：0=刚上电，1=按KEY0蜂鸣器响，2=按KEY1呼吸灯600ms循环
u16 led0pwmval = 0; //PWM比较值 控制占空比
u8 dir = 1; // 1=上升;0=下降
u8 key;

int main(void){
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	     //串口初始化为9600
	KEY_Init();              //按键端口初始化
	LED_Init();			     //LED端口初始化
	BEEP_Init();
	judge = 0;
	TIM2_Int_Init(4999, 7199);//上电后LED0亮500ms,灭500ms
	
   	while(1)
	{
		key = GetKey();
		if(key){
			switch(key){
				case 2:{ // KEY1
					BEEP = 0;
					TIM3_PWM_Init(899, 0); // 不分频，PWM频率=72000000/（899+1）=80kHz
					TIM2_Int_Init(5999, 7199); //600ms
					judge = 2;
					break;
				}
				case 1:{ // KEY0，蜂鸣器响0.5s，停0.5s
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
