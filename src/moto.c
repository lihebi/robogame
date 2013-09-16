#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define SPEED   20    //�����ٶ�

void moto_run(char SpeedL,char SpeedR);
//void Moto(char speedl,char speedr);

unsigned int  P    = 5;      //ת���ٶ�ϵ��
unsigned char temp = 0;      //��ʱ����,���ڵ���
extern unsigned char flag;      //��־״̬
extern unsigned char flag_old;  //�ϴε�״̬

unsigned char stage_4_flag = 0; //���Ľ׶����е�һ����־

char Left  = 0;
char Right = 0;

char Left_old = 0;
char Right_old = 0;

extern unsigned char stage;       //��¼���н׶�
extern unsigned char dir;         //ƫ��
extern void Delay_ms(word ms);

void Moto_Control(void)
{
    //unsigned char Left  = SPEED;
    //unsigned char Right = SPEED;
    
    if(dir == 0xF1)          //��¥
    {
        PITINTE = 0x00;	     // �ر�0·�ж�
        SCI0CR2_RE = 0;      //���ڽ���ֹͣ
        
        stage = 0xF1;
        //moto_run(15,15);
        Delay_ms(1000);		 //��ʱ5s
        dir = 255;
        
        SCI0CR2_RE = 1;      //���ڽ���ʹ��       
        PITINTE = 0x01;      //��0·�ж�
         
    } 
    else if(dir == 0xF2)
    {
        stage = 0xF2;
        dir = 255;
    }
    else if(dir == 0xF3)
    {
        stage = 0xF3;
        dir = 255;
    }
    else if(dir == 0xF4)
    {
        stage = 0xF4;
        dir = 255;
    }
    
    if(!dir)         //·�겻����Ұ��
    {
        flag = 0;
        
        if((!flag)&&flag_old)   //��֡����
        {
            moto_run(0,0);
            //while(!dir);
            PITINTE = 0x00;	     // �ر�0·�ж�
           
            Delay_ms(100);
            PITINTE = 0x01;	     // �ر�0·�ж�
        }
        else
        {
            if(stage == 0xF1)       //��һ�׶�
            {
                moto_run(40,-20);   //��ת,ֱ����һ��·�����
            }         
            else if(stage == 0xF2)  //�ڶ��׶� 
            {
                moto_run(-20,40);   //��ת,ֱ���ڶ���·�����
                
            }        
            else if(stage == 0xF3)  //�����׶�
            {
                moto_run(-20,40);   //��ת,ֱ��������·�����
            }        
            else if(stage == 0xF4)  //���Ľ׶�
            {
              /*  temp++;
                if(temp == 1)
                    stage_4_flag = 1;
                if(stage_4_flag)
                {
                    PITINTE = 0x00;	   // �ر�0·�ж�
                    moto_run(30,30);   //ֱ��һ��
                    Delay_ms(3000);
                    stage_4_flag = 0;  //���־
                    PITINTE = 0x01;	   // ��0·�ж�
                }
              */
                moto_run(40,-20);      //��ת,ֱ�����ĸ�·�����
            }
        }
        flag_old = flag;
    }

    if((dir >= 26)&&(dir <= 34))  //;��......
    {
        flag  = 1;
        flag_old  = flag; 
        Left  = (dir - 30) * P;
        Right = (30 - dir) * P;
        Left_old  = Left;
        Right_old = Right; 
        moto_run(Left + SPEED,Right + SPEED);
    } 
    else if(dir == 255)
    {
        moto_run(45,45);
    }
        
}

void moto_run(char SpeedL,char SpeedR)
{
    if(SpeedL > 99)     SpeedL = 99;        //����
    if(SpeedL < -99)    SpeedL = -99;
    
    if(SpeedR > 99)     SpeedL = 99;
    if(SpeedR < -99)    SpeedL = -99;
    
    if(SpeedL>=0)
    {
        PWMDTY0 = SpeedL;      //���1,��ǰ
	    PWMDTY1 = 0;
	    
	    PWMDTY6 = 0;           //���4,���
    	PWMDTY7 = SpeedL+30;
    } 
    else
    {
        PWMDTY0 = 0;           //���1,��ǰ
        PWMDTY1 = (-SpeedL);
        
        PWMDTY6 = (-SpeedL);   //���4,���
    	PWMDTY7 = 0;
    }
    
    if(SpeedR >= 0)
    {
        PWMDTY2 = 0;           //���2,��ǰ
    	PWMDTY3 = SpeedR;
	                   
    	PWMDTY4 = SpeedR+30;      //���3,�Һ�
    	PWMDTY5 = 0;    
    }
    else
    {
        PWMDTY2 = (-SpeedR);   //���2,��ǰ
    	PWMDTY3 = 0;
	                   
    	PWMDTY4 = 0;           //���3,�Һ�
    	PWMDTY5 = (-SpeedR);     
    }
}