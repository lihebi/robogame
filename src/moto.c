#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define SPEED   20    //基础速度

void moto_run(char SpeedL,char SpeedR);
//void Moto(char speedl,char speedr);

unsigned int  P    = 5;      //转弯速度系数
unsigned char temp = 0;      //临时变量,用于调试
extern unsigned char flag;      //标志状态
extern unsigned char flag_old;  //上次的状态

unsigned char stage_4_flag = 0; //第四阶段运行的一个标志

char Left  = 0;
char Right = 0;

char Left_old = 0;
char Right_old = 0;

extern unsigned char stage;       //记录运行阶段
extern unsigned char dir;         //偏差
extern void Delay_ms(word ms);

void Moto_Control(void)
{
    //unsigned char Left  = SPEED;
    //unsigned char Right = SPEED;
    
    if(dir == 0xF1)          //下楼
    {
        PITINTE = 0x00;	     // 关闭0路中断
        SCI0CR2_RE = 0;      //串口接收停止
        
        stage = 0xF1;
        //moto_run(15,15);
        Delay_ms(1000);		 //延时5s
        dir = 255;
        
        SCI0CR2_RE = 1;      //串口接收使能       
        PITINTE = 0x01;      //打开0路中断
         
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
    
    if(!dir)         //路标不在视野内
    {
        flag = 0;
        
        if((!flag)&&flag_old)   //丢帧处理
        {
            moto_run(0,0);
            //while(!dir);
            PITINTE = 0x00;	     // 关闭0路中断
           
            Delay_ms(100);
            PITINTE = 0x01;	     // 关闭0路中断
        }
        else
        {
            if(stage == 0xF1)       //第一阶段
            {
                moto_run(40,-20);   //右转,直到第一个路标出现
            }         
            else if(stage == 0xF2)  //第二阶段 
            {
                moto_run(-20,40);   //左转,直到第二个路标出现
                
            }        
            else if(stage == 0xF3)  //第三阶段
            {
                moto_run(-20,40);   //左转,直到第三个路标出现
            }        
            else if(stage == 0xF4)  //第四阶段
            {
              /*  temp++;
                if(temp == 1)
                    stage_4_flag = 1;
                if(stage_4_flag)
                {
                    PITINTE = 0x00;	   // 关闭0路中断
                    moto_run(30,30);   //直行一段
                    Delay_ms(3000);
                    stage_4_flag = 0;  //清标志
                    PITINTE = 0x01;	   // 打开0路中断
                }
              */
                moto_run(40,-20);      //右转,直到第四个路标出现
            }
        }
        flag_old = flag;
    }

    if((dir >= 26)&&(dir <= 34))  //途中......
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
    if(SpeedL > 99)     SpeedL = 99;        //限速
    if(SpeedL < -99)    SpeedL = -99;
    
    if(SpeedR > 99)     SpeedL = 99;
    if(SpeedR < -99)    SpeedL = -99;
    
    if(SpeedL>=0)
    {
        PWMDTY0 = SpeedL;      //电机1,左前
	    PWMDTY1 = 0;
	    
	    PWMDTY6 = 0;           //电机4,左后
    	PWMDTY7 = SpeedL+30;
    } 
    else
    {
        PWMDTY0 = 0;           //电机1,左前
        PWMDTY1 = (-SpeedL);
        
        PWMDTY6 = (-SpeedL);   //电机4,左后
    	PWMDTY7 = 0;
    }
    
    if(SpeedR >= 0)
    {
        PWMDTY2 = 0;           //电机2,右前
    	PWMDTY3 = SpeedR;
	                   
    	PWMDTY4 = SpeedR+30;      //电机3,右后
    	PWMDTY5 = 0;    
    }
    else
    {
        PWMDTY2 = (-SpeedR);   //电机2,右前
    	PWMDTY3 = 0;
	                   
    	PWMDTY4 = 0;           //电机3,右后
    	PWMDTY5 = (-SpeedR);     
    }
}