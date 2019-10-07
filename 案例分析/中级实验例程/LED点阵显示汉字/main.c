//�ð����ϵĵ���Ϊ8*8��ֻ����ʾ�򵥵�һЩ���ӣ����Ҫ��ʾ�����ĺ���
//ͨ��ȡģ���ȡ�Ŀ���ѡ��16*16����İ���

#include<reg51.h>
#include<intrins.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

//--����Ҫʹ�õ�IO��--  P0�û���ѡ//
#define COMMONPORTS		P0

//--��ѡͨ����--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

//--��������--//
unsigned char code CHARCODE[4][8]=
{

{0x00,0x3E,0x08,0x3E,0x08,0x3E,0x00,0x00},  //��
{0x24,0xFF,0x24,0x3E,0x20,0x3E,0x42,0x7E},   //С
{0x44,0xFF,0x60,0xFD,0x34,0xFF,0x11,0x10},  //��

0x7C,0x48,0x48,0xFF,0x48,0x48,0x7C,0x00  //��

};
void delay(unsigned int time)
{
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++);
}

/*******************************************************************************
* ������         : Hc595SendByte(unsigned char dat)
* ��������		   : ��74H595����һ���ֽڵ�����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Hc595SendByte(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}
/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{	
 	unsigned char tab, j;
	unsigned int  i;

	while(1)
	{	
		for(i= 0; i<50; i++ )   //������֮���ɨ����ʱ��
		{
			for(tab=0;tab<8;tab++)
			{	

				Hc595SendByte(0x00);			     //����																
				COMMONPORTS	= TAB[tab];				 //�������	
				Hc595SendByte(CHARCODE[j][tab]);	
				delay(2);		
			}
			 
		}
		j++;
		if(j == 4)
		{
			j = 0;
		}
	}	
}
