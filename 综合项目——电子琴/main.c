#include <reg52.h>

unsigned int code table[]=
{
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,	//低音区  0——11
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,	//中音区  12——23
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,	//高音区  24——35
  // Do   Do(u)  Re   Re(u)   Mi    Fa  Fa(u)  So   So(u)   La   La(u)  Si 
};

//四分音符规定为400ms
unsigned int code music1[][2] =
{
	12,4,   12,4,   19,4,   19,4,   21,4,   21,4,   19,8,
	17,4,   17,4,   16,4,   16,4,   14,4,   14,4,   12,8,
	19,4,   19,4,   17,4,   17,4,	16,4,   16,4, 	14,8,
	19,4,   19,4,   17,4,   17,4,	16,4,   16,4, 	14,8,
	12,4,   12,4,   19,4,   19,4,   21,4,   21,4,   19,8,
	17,4,   17,4,   16,4,   16,4,   14,4,   14,4,   12,8,

0xff
};

unsigned int code music2[][2] =
{
	7,2,   7,2,   9,4,   7,4,   12,4,   11,8,
	7,2,   7,2,   9,4,   7,4,   14,4,   12,8,
	7,2,   7,2,   19,4,  16,4,  12,4,   11,4,   9,4,
	17,4,  17,4,  16,4,  12,4,   14,4,   12,8,
0xff
	
};
/*
1 2
4 2
5 2
7 2
*/

void Init();
void key_scan();
void delay100ms(unsigned int z);

sbit fmq = P2^0;
sbit KEY1 = P1^0;
sbit KEY2 = P1^1;
sbit KEY3 = P1^2;
sbit KEY4 = P1^3;
sbit KEY5 = P1^4;
sbit KEY6 = P1^5;
sbit KEY7 = P1^6;
sbit KEY8 = P1^7;
unsigned int temp1,temp2,n;		//存储TH0和TL0的取值

void main()
{
	Init();
	while(1)
	{
		key_scan();
	}
}

void key_scan()
{
	if(KEY1 == 0)
	{
		temp1 = table[12]/256;
		temp2 = table[12]%256;
		TH0 = temp1;
		TL0 = temp2;
		TR0 = 1;		//使能定时器，开始演奏
		while(KEY1 == 0);
		delay100ms(2);
	}
		if(KEY2 == 0)
	{
		temp1 = table[14]/256;
		temp2 = table[14]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY2 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
		if(KEY3 == 0)
	{
		temp1 = table[16]/256;
		temp2 = table[16]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY3 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
		if(KEY4 == 0)
	{
		temp1 = table[17]/256;
		temp2 = table[17]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY4 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
		if(KEY5 == 0)
	{
		temp1 = table[19]/256;
		temp2 = table[19]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY5 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
	if(KEY6 == 0)
	{
		temp1 = table[21]/256;
		temp2 = table[21]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY6 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
	if(KEY7 == 0)
	{
		temp1 = table[23]/256;
		temp2 = table[23]%256;
		TH0 = temp1;
		TL0 = temp2;
		while(KEY7 == 0);
		TR0 = 1;		//使能定时器，开始演奏
		delay100ms(2);
	}
		if(KEY8 == 0)
		{
			while(1)
			{
				temp1 = table[music2[n][0]]/256;
				temp2 = table[music2[n][0]]%256;
				TH0 = temp1;
				TL0 = temp2;
				while(KEY7 == 0);
				TR0 = 1;
				delay100ms(music2[n][1]);
				n++;
				if(music2[n][0] == 0xff)
				{
					TR0 = 0;
					n = 0;
					break;
				}
			}
		}
	TR0 = 0;
}

void Init()
{
	TMOD = 0x01;
	EA = 1;
	ET0 = 1;
}

void delay100ms(unsigned int z)
{
	unsigned int i;
	z++;
	while(--z)
	{
		for(i = 11502;i;i--);
	}
}

void timer() interrupt 1
{
	TH0 = temp1;
	TL0 = temp2;
	fmq = ~fmq;
}