#include "reg51.h"
#include "led1602.h"
sfr P4=0xc0;//led�ƵĶ˿�
sfr  WDT_CONTR=0xc1;//���Ź����ƼĴ���
sfr  IAP_CONTR=0xc7; //�����λ���ƼĴ���
sfr  CLK_DIV=0X97;//ʱ�ӷ�Ƶ����
sfr WKTCL = 0xAA;//���绽��ר�üĴ���
sfr WKTCH = 0xAB;//���绽��ר�üĴ���
sbit P46=P4^6;
sbit P47=P4^7;


void disumoshi();
void kongxianmoshi();
void diaodianmoshi();
void shangdianfuwei();
void didianyafuwei();
void error();
void delay(int a,int b);
void main()
{
	
	int i;
	INT0=1;
	INT1=1;
	IT0=1;   //ֻ�����½��ش���
	IT1=1;
	EX0=1;   //�����ⲿ�ж�0
	EX1=1;
	PX1=1;
	PX0=0;
	EA=1;    //����ȫ���ж�
	P0M0=0;
	P0M1=0;
  P2M0=0;
	P2M1=0;
	if(PCON==0x30)
	{
		shangdianfuwei();
	}
	if(PCON==0x20)
	{
		didianyafuwei();
	}

	for(i=0;i<3;i++)
	{	
		switch(i)
		{
			case 0: disumoshi();break;//����ģʽ
				
			case 1: diaodianmoshi();break;//����ģʽ
				
			case 2: kongxianmoshi();break;//����ģʽ
			
			default: error();
			
		}
		delay(1000,100);
	}

}



void servivce_int0() interrupt 0//�ж�0
{
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"ruanjianfuwei");
	delay(1000,100);
	PCON=0x00;
	IAP_CONTR=0x20;
}
void servivce_int1() interrupt 2//�ж�1
{
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"kanmengoufuwei");
	PCON=0x00;
	WDT_CONTR |= 0x2A;
	while(1);
	
}
void shangdianfuwei()
{
  lcdwait();
	lcdinit();
	lcdshowstr(0,0,"shangdianfuwei");
  delay(1000,1000);
	PCON=0;
}
void didianyafuwei()
	
{
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"didianyafuwei");
	delay(1000,1000);
	PCON=0;
}

void disumoshi()
{
	CLK_DIV = 0xc5;//f���=f��/��32*4�� ��ʱ����ISP���س���ʱ��ѡ
	P46 = 0;
	P47 = 0;
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"disumoshi");
}
 
void kongxianmoshi()
{
	P46 = 0;
	P47 = 0;
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"kongxianmoshi");
	PCON |= 0x01;
}

void diaodianmoshi()
{
	WKTCL = 255;
	WKTCH = 0x80;
	P46 = 0;
	P47 = 0;
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"diaodianmoshi");
	PCON |= 0x02;
}


void error()
{
	lcdwait();
	lcdinit();
	lcdshowstr(0,0,"error");
}

void delay(int a,int b)
{
	int i,j;
	for(i=0;i<a;i++)
	{
		for(j=0;j<b;j++);
		
	}
}