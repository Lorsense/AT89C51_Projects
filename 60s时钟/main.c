#include <reg52.h>  // 51��Ƭ���Ĵ�������ͷ�ļ�

unsigned int num,flag,flag1,gewei,shiwei;

sbit LED = P1^0;
sbit key = P3^2;

void Init();
void delay();
void scan();
void delay_ms(unsigned int ms);

unsigned char code leddata[] = 
{
	0xc0, //0
	0xf9,  //1
	0xa4,  //2
	0xb0,  //3
	0x99,  //4
	0x92,  //5
	0x82,  //6
	0xf8,  //7
	0x80,  //8
	0x90   //9
};

void xianshi(unsigned int i,unsigned int j)
{
	gewei = flag1%10;
	shiwei = flag1/10;
	P2 = 0x02;
	P0 = leddata[i];
	delay_ms(2);
	P2 = 0x01;
	P0 = leddata[j];
	delay_ms(2);
}

void main()
{
	Init();
	while(1)
	{
		xianshi(gewei,shiwei);
	}
}

void scan()
{
	if (key == 0)
	{	
		while(1)
		{
			if (key == 1)
			{
				num++;
				break;
			}
		}

	}
}

void delay()
{
	unsigned int i,j;
	for( i = 20000;i>1;i--)
	for( j =6000;j>1;j--);
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++); // ������ʱ 1ms��12MHz ����
}

void Init()
{
	EA = 1;		//�������ж�	
	ET0 = 1;	//ʹ�ܶ�ʱ���ж�
	TR0 = 1;	//������ʱ��0
	
	TMOD = 0x01;	//���ù���ģʽ
	TH0 = (65535 - 50000)/256;
	TL0 =(65535 - 50000)%256;
	LED = 0;
}

void timer0() interrupt 1
{
	TH0 = (65535 - 50000)/256;
	TL0 =(65535 - 50000)%256;
	flag++;
	if(flag == 20)
	{
		flag = 0;
		flag1++;		//��ʱ��
	}
		//������Ҫ����ʱ�����ŵ���ʱ�ж���Ӱ���ʱʱ��
		if(flag1 == 60)
		{
			LED = 1;
			EA = 0;
			TH0 = (65535 - 50000)/256;	//Ϊ�˲���ʧ��ʱ���ļ���ֵ
			TL0 =(65535 - 50000)%256;
		}
	
}