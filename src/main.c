#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "init.h"
#include "sci.h"
#include "moto.h"

//#define   CSN               PORTB_PB6
//#define   CE                PORTB_PB7
#define   LED               PORTB_PB0

unsigned char dir = 255;         //�����־
unsigned char stage = 0;       //��¼���н׶�
unsigned char flag = 0;      //��־״̬
unsigned char flag_old = 0;  //�ϴε�״̬

unsigned char sci_status = 0;  //���ڶ�����״̬

unsigned long time = 0;        //��ʱ������,ÿ100ms��1
unsigned long count = 0;       //���ڼ���,ÿ1s��1

//unsigned char led[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};


void Delay_ms(word ms)		//��ʱ1ms
{
	word i,j;
	for(i=0; i<ms; i++)
		for(j=0; j<13350; j++);
}

void main(void)
{
    DisableInterrupts;
    Init_All();         //��ʼ��
    Delay_ms(3000);		//��ʱ3s
    EnableInterrupts;   //�����ж�
    
   // Delay_ms(3000);		//��ʱ3s
			
	for(;;)
	{
	    //_FEED_COP();	// ι��
	    //time++;
	    //Moto_Control();
	}
}

#pragma CODE_SEG NON_BANKED

/***************��ʱ�ж�*******************/
void interrupt VectorNumber_Vpit0 PIT0(void)	// every 100ms
{     
    PITTF_PTF0=1;   //���־
    time++;
    if(time%10 == 0)
    {
        count++;    //ÿ1s��1
        LED = ~LED;
        PORTB_PB4 = ~PORTB_PB4;
    }
    Moto_Control();
}
/**************************************/

void interrupt VectorNumber_Vsci0 SCI0(void)    //�����ж�
{
 	PITINTE = 0x00;	  // �ر�0·�ж�
    
    sci_status = SCI0SR1_RDRF;
    dir = SCI0DRL;
    
    PITINTE	= 0x01;	  // ʹ��0·�ж�
}
