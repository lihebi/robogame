#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "init.h"
#include "sci.h"
#include "moto.h"

//#define   CSN               PORTB_PB6
//#define   CE                PORTB_PB7
#define   LED               PORTB_PB0

unsigned char dir = 255;         //方向标志
unsigned char stage = 0;       //记录运行阶段
unsigned char flag = 0;      //标志状态
unsigned char flag_old = 0;  //上次的状态

unsigned char sci_status = 0;  //用于读串口状态

unsigned long time = 0;        //定时器计数,每100ms加1
unsigned long count = 0;       //用于计数,每1s加1

//unsigned char led[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};


void Delay_ms(word ms)		//延时1ms
{
	word i,j;
	for(i=0; i<ms; i++)
		for(j=0; j<13350; j++);
}

void main(void)
{
    DisableInterrupts;
    Init_All();         //初始化
    Delay_ms(3000);		//延时3s
    EnableInterrupts;   //开总中断
    
   // Delay_ms(3000);		//延时3s
			
	for(;;)
	{
	    //_FEED_COP();	// 喂狗
	    //time++;
	    //Moto_Control();
	}
}

#pragma CODE_SEG NON_BANKED

/***************定时中断*******************/
void interrupt VectorNumber_Vpit0 PIT0(void)	// every 100ms
{     
    PITTF_PTF0=1;   //清标志
    time++;
    if(time%10 == 0)
    {
        count++;    //每1s加1
        LED = ~LED;
        PORTB_PB4 = ~PORTB_PB4;
    }
    Moto_Control();
}
/**************************************/

void interrupt VectorNumber_Vsci0 SCI0(void)    //串口中断
{
 	PITINTE = 0x00;	  // 关闭0路中断
    
    sci_status = SCI0SR1_RDRF;
    dir = SCI0DRL;
    
    PITINTE	= 0x01;	  // 使能0路中断
}
