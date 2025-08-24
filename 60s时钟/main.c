#include <reg52.h>  // 51单片机寄存器定义头文件

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
        for(j = 0; j < 123; j++); // 粗略延时 1ms（12MHz 晶振）
}

void Init()
{
	EA = 1;		//开启总中断	
	ET0 = 1;	//使能定时器中断
	TR0 = 1;	//开启定时器0
	
	TMOD = 0x01;	//设置工作模式
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
		flag1++;		//总时间
	}
		//尽量不要把延时函数放到定时中断里影响计时时间
		if(flag1 == 60)
		{
			LED = 1;
			EA = 0;
			TH0 = (65535 - 50000)/256;	//为了不丢失定时器的计数值
			TL0 =(65535 - 50000)%256;
		}
	
}