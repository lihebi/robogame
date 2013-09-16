#include "derivative.h"

//#define   CSN               PORTB_PB6
//#define   CE                PORTB_PB7
#define   LED               PORTB_PB0

/************初始化锁相环*****************/
void PLL_Init(void) {	// 初始化锁相环，设置倍频
			// PLLCLK		= 2 *  OSCCLK	* (SYNR+1) / (REFDV+1)
			// 锁相环时钟	= 2 *    16		* (  4 +1) / (  0  +1)		=160MHz
			// 总线频率		= PLLCLK / 2 = 80MHz
//	DisableInterrupts;		// 禁止总中断
	CLKSEL_PLLSEL	= 0;	// 选择时钟源为OSCCLK(外部晶振)
	PLLCTL_PLLON	= 0;	// 禁用锁相环
	SYNR_VCOFRQ		= 0b11; // 选择VCO频率范围为最大
	SYNR_SYNDIV		= 4;	// 设置SYNR寄存器值为4
	REFDV_REFFRQ	= 0b11;	// 选择REF频率范围为最大
	REFDV_REFDIV	= 0;	// 设置REFDV寄存器的值为0
	PLLCTL_PLLON	= 1;	// 启用锁相环
	_asm nop				// 汇编空指令
	_asm nop				// +1
	_asm nop				// +2
	_asm nop				// +3
	while(!CRGFLG_LOCK);	// 等待锁相环稳定
	CLKSEL_PLLSEL	= 1;	// 选择时钟源为PLLCLK(锁相环)
}
/*********************************************/

/************PIT初始化******************/
void PIT_Init()
{

	PITCFLMT	= 0x00;		// 关闭PIT模块
	PITFLT		= 0x01;		// 0路定时器加载倒计时数值
	PITCE		= 0x01;		// 0路定时器使能
	PITMUX		= 0x00;		// 16位计数器基于微计数器0
	
	PITMTLD0	= 159;		  // 8位递减计数值
	PITLD0		= 49999;	  // 16位递减计数值
	                    // frequncy	= BusClk / 160 / 50000 = 10
	                    // cycle	= 100ms
	
	PITINTE		= 0x01;	  // 使能0路中断
	PITCFLMT	= 0x81; 	// 使能PIT模块,使能微计数器0
}
/**************************************/

/*****************PWM初始化*********************/
void PWM_Init(void) 
{
	PWME			=	0x00;	// 禁用所有PWM通道
	PWMPOL			=	0xFF;	// 全部极性设置为高
	PWMCAE			=	0x00;	// 全部对齐方式设置为左对齐
	PWMPRCLK		=	0x22;	// 预分频寄存器设置为 A=B=80M/4=20M
	PWMSCLA			=	50;		// 时钟设置为 SA=A/2/10=200K
	PWMSCLB			=	50;		// 时钟设置为 SB=B/2/50=200K 			
	//电机1(0通道,1通道)
	PWMCLK_PCLK0	=	1;		// 通道0时钟源选择为SA
	PWMCLK_PCLK1	=	1;		// 通道1时钟源选择为SA
	PWMPER0			=	101;	// 0通道周期寄存器设置为 Frequency=SA/100=2k
	PWMDTY0			=	0;		// 占空比寄存器设置占空比0%
	PWMPER1			=	101;	// 1通道周期寄存器设置为 Frequency=SA/100=2k
	PWMDTY1			=	0;		// 占空比寄存器设置占空比0%
	//电机2(2通道,3通道)
	PWMCLK_PCLK2	=	1;		// 通道2时钟源选择为SB
	PWMCLK_PCLK3	=	1;		// 通道3时钟源选择为SB
	PWMPER2			=	101;	// 2通道周期寄存器设置为 Frequency=SB/100=2k
	PWMDTY2			=	0;		// 占空比寄存器设置占空比0%
	PWMPER3			=	101;	// 3通道周期寄存器设置为 Frequency=SB/100=2k
	PWMDTY3			=	0;		// 占空比寄存器设置占空比0%	
	//电机3(4通道,5通道)
	PWMCLK_PCLK4	=	1;		// 通道4时钟源选择为SA
	PWMCLK_PCLK5	=	1;		// 通道5时钟源选择为SA
	PWMPER4			=	101;	// 4通道周期寄存器设置为 Frequency=SA/100=2k
	PWMDTY4			=	0;		// 占空比寄存器设置占空比0%
	PWMPER5			=	101;	// 5通道周期寄存器设置为 Frequency=SA/100=2k
	PWMDTY5			=	0;		// 占空比寄存器设置占空比0%
	//电机4(6通道,7通道)
	PWMCLK_PCLK6	=	1;		// 通道6时钟源选择为SB
	PWMCLK_PCLK7	=	1;		// 通道7时钟源选择为SB
	PWMPER6			=	101;	// 6通道周期寄存器设置为 Frequency=SB/100=2k
	PWMDTY6			=	0;		// 占空比寄存器设置占空比0%
	PWMPER7			=	101;	// 7通道周期寄存器设置为 Frequency=SB/100=2k
	PWMDTY7			=	0;		// 占空比寄存器设置占空比0%	
	
	PWME			=	0xFF;	// 使能所有PWM通道
}
/***********************************************/

/***************SCI初始化********************/
void SCI_Init()
{
    SCI0BDH = 0x02; 
    SCI0BDL = 0x08;     // BaudRate = BusClk/16/SBR[12:0] = 9615 = 9600
    SCI0CR1	= 0x00;		// 正常 8 位模式,无奇偶校验
    SCI0CR2	= 0x2C;		// 接收中断使能,可发可收模式
}
/*******************************************/

/***********SPI初始化****************/
/*void SPI_Init(void)
{
  SPI0DRL = 0x00;      //数据寄存器清空
  SPI0CR1 = 0x52;      //SPI使能,主模式
  SPI0CR2 = 0x00;      //
  SPI0BR  = 0x42;      //波特率4M
}
*/
/**************************************/  

/*************相关端口初始化******************/
void PORT_Init(void)
{
  DDRA = 0xFF;     //作为输出
  PORTA = 0xFF;

  
  DDRB = 0xFF;
  PORTB = 0xFF;
  //CE   = 0;
  //CSN  = 1;
  LED  = 0;
}
/**********************************************/

/***********外部中断初始化***************/
/*void IRQ_Init(void)
{
  IRQCR_IRQE  = 0; //低电平检测
  IRQCR_IRQEN = 1; //使能 
}
*/
/***************************************/


void Init_All(void)
{
  PLL_Init();
  PWM_Init();
  PIT_Init();
  //SPI_Init();
  SCI_Init();
  PORT_Init();
  //IRQ_Init();
}