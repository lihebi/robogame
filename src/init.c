#include "derivative.h"

//#define   CSN               PORTB_PB6
//#define   CE                PORTB_PB7
#define   LED               PORTB_PB0

/************��ʼ�����໷*****************/
void PLL_Init(void) {	// ��ʼ�����໷�����ñ�Ƶ
			// PLLCLK		= 2 *  OSCCLK	* (SYNR+1) / (REFDV+1)
			// ���໷ʱ��	= 2 *    16		* (  4 +1) / (  0  +1)		=160MHz
			// ����Ƶ��		= PLLCLK / 2 = 80MHz
//	DisableInterrupts;		// ��ֹ���ж�
	CLKSEL_PLLSEL	= 0;	// ѡ��ʱ��ԴΪOSCCLK(�ⲿ����)
	PLLCTL_PLLON	= 0;	// �������໷
	SYNR_VCOFRQ		= 0b11; // ѡ��VCOƵ�ʷ�ΧΪ���
	SYNR_SYNDIV		= 4;	// ����SYNR�Ĵ���ֵΪ4
	REFDV_REFFRQ	= 0b11;	// ѡ��REFƵ�ʷ�ΧΪ���
	REFDV_REFDIV	= 0;	// ����REFDV�Ĵ�����ֵΪ0
	PLLCTL_PLLON	= 1;	// �������໷
	_asm nop				// ����ָ��
	_asm nop				// +1
	_asm nop				// +2
	_asm nop				// +3
	while(!CRGFLG_LOCK);	// �ȴ����໷�ȶ�
	CLKSEL_PLLSEL	= 1;	// ѡ��ʱ��ԴΪPLLCLK(���໷)
}
/*********************************************/

/************PIT��ʼ��******************/
void PIT_Init()
{

	PITCFLMT	= 0x00;		// �ر�PITģ��
	PITFLT		= 0x01;		// 0·��ʱ�����ص���ʱ��ֵ
	PITCE		= 0x01;		// 0·��ʱ��ʹ��
	PITMUX		= 0x00;		// 16λ����������΢������0
	
	PITMTLD0	= 159;		  // 8λ�ݼ�����ֵ
	PITLD0		= 49999;	  // 16λ�ݼ�����ֵ
	                    // frequncy	= BusClk / 160 / 50000 = 10
	                    // cycle	= 100ms
	
	PITINTE		= 0x01;	  // ʹ��0·�ж�
	PITCFLMT	= 0x81; 	// ʹ��PITģ��,ʹ��΢������0
}
/**************************************/

/*****************PWM��ʼ��*********************/
void PWM_Init(void) 
{
	PWME			=	0x00;	// ��������PWMͨ��
	PWMPOL			=	0xFF;	// ȫ����������Ϊ��
	PWMCAE			=	0x00;	// ȫ�����뷽ʽ����Ϊ�����
	PWMPRCLK		=	0x22;	// Ԥ��Ƶ�Ĵ�������Ϊ A=B=80M/4=20M
	PWMSCLA			=	50;		// ʱ������Ϊ SA=A/2/10=200K
	PWMSCLB			=	50;		// ʱ������Ϊ SB=B/2/50=200K 			
	//���1(0ͨ��,1ͨ��)
	PWMCLK_PCLK0	=	1;		// ͨ��0ʱ��Դѡ��ΪSA
	PWMCLK_PCLK1	=	1;		// ͨ��1ʱ��Դѡ��ΪSA
	PWMPER0			=	101;	// 0ͨ�����ڼĴ�������Ϊ Frequency=SA/100=2k
	PWMDTY0			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	PWMPER1			=	101;	// 1ͨ�����ڼĴ�������Ϊ Frequency=SA/100=2k
	PWMDTY1			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	//���2(2ͨ��,3ͨ��)
	PWMCLK_PCLK2	=	1;		// ͨ��2ʱ��Դѡ��ΪSB
	PWMCLK_PCLK3	=	1;		// ͨ��3ʱ��Դѡ��ΪSB
	PWMPER2			=	101;	// 2ͨ�����ڼĴ�������Ϊ Frequency=SB/100=2k
	PWMDTY2			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	PWMPER3			=	101;	// 3ͨ�����ڼĴ�������Ϊ Frequency=SB/100=2k
	PWMDTY3			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%	
	//���3(4ͨ��,5ͨ��)
	PWMCLK_PCLK4	=	1;		// ͨ��4ʱ��Դѡ��ΪSA
	PWMCLK_PCLK5	=	1;		// ͨ��5ʱ��Դѡ��ΪSA
	PWMPER4			=	101;	// 4ͨ�����ڼĴ�������Ϊ Frequency=SA/100=2k
	PWMDTY4			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	PWMPER5			=	101;	// 5ͨ�����ڼĴ�������Ϊ Frequency=SA/100=2k
	PWMDTY5			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	//���4(6ͨ��,7ͨ��)
	PWMCLK_PCLK6	=	1;		// ͨ��6ʱ��Դѡ��ΪSB
	PWMCLK_PCLK7	=	1;		// ͨ��7ʱ��Դѡ��ΪSB
	PWMPER6			=	101;	// 6ͨ�����ڼĴ�������Ϊ Frequency=SB/100=2k
	PWMDTY6			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%
	PWMPER7			=	101;	// 7ͨ�����ڼĴ�������Ϊ Frequency=SB/100=2k
	PWMDTY7			=	0;		// ռ�ձȼĴ�������ռ�ձ�0%	
	
	PWME			=	0xFF;	// ʹ������PWMͨ��
}
/***********************************************/

/***************SCI��ʼ��********************/
void SCI_Init()
{
    SCI0BDH = 0x02; 
    SCI0BDL = 0x08;     // BaudRate = BusClk/16/SBR[12:0] = 9615 = 9600
    SCI0CR1	= 0x00;		// ���� 8 λģʽ,����żУ��
    SCI0CR2	= 0x2C;		// �����ж�ʹ��,�ɷ�����ģʽ
}
/*******************************************/

/***********SPI��ʼ��****************/
/*void SPI_Init(void)
{
  SPI0DRL = 0x00;      //���ݼĴ������
  SPI0CR1 = 0x52;      //SPIʹ��,��ģʽ
  SPI0CR2 = 0x00;      //
  SPI0BR  = 0x42;      //������4M
}
*/
/**************************************/  

/*************��ض˿ڳ�ʼ��******************/
void PORT_Init(void)
{
  DDRA = 0xFF;     //��Ϊ���
  PORTA = 0xFF;

  
  DDRB = 0xFF;
  PORTB = 0xFF;
  //CE   = 0;
  //CSN  = 1;
  LED  = 0;
}
/**********************************************/

/***********�ⲿ�жϳ�ʼ��***************/
/*void IRQ_Init(void)
{
  IRQCR_IRQE  = 0; //�͵�ƽ���
  IRQCR_IRQEN = 1; //ʹ�� 
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