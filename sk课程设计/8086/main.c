//步进电机的8255的各个端口的地址
#define IOCON	8006H
#define IOA     8000H
#define IOB     8002H
#define IOC     8004H

//速度表8255的各个端口地址
#define IOCON8255   0A060H
#define IOA8255     0A000H
#define IOB8255     0A020H
#define IOC8255     0A040H

//油门相关芯片的地址
#define AD0809	0C100H
#define OUT373  0B000H
#define my373   0D000H

//按键的各个含义
#define btnerdang 0xef
#define btnsandang 0xdf
#define btnlaba 0xbf
#define btnyidang 0xf7
#define btnyoumen 0x7f
//速度表数码显示
#define pos 0x01
#define one 0F9H
#define two 0A4H 
#define three 0B0H
#define zero 0C0H 
#define four 99h
unsigned char number[10]={0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H}; 
unsigned char daoche[3]={0xa1,88H,0C0H};//“dao”
unsigned char laba[4]={0xc7,88H,80H,88H};//"laba"

//8253各个端口的地址
#define TCONTRO   9018H
#define TCON0     9000H
#define TCON1     9008H
#define TCON2     9010H

//实例49：用定时器T0的中断实现"渴望"主题曲的播放
//#define feq 1000000
//以下是C调低音的音频宏定义
#define l_dao 382   //将“l_dao”宏定义为低音“1”的频率262Hz
#define l_re 350    //将“l_re”宏定义为低音“2”的频率286Hz
#define l_mi 322    //将“l_mi”宏定义为低音“3”的频率311Hz
#define l_fa 287    //将“l_fa”宏定义为低音“4”的频率349Hz
#define l_sao 253   //将“l_sao”宏定义为低音“5”的频率392Hz
#define l_la 227    //将“l_a”宏定义为低音“6”的频率440Hz
#define l_xi 202    //将“l_xi”宏定义为低音“7”的频率494Hz
//以下是C调中音的音频宏定义
#define dao 191     //将“dao”宏定义为中音“1”的频率523Hz
#define re 170      //将“re”宏定义为中音“2”的频率587Hz
#define mi 152      //将“mi”宏定义为中音“3”的频率659Hz
#define fa 143      //将“fa”宏定义为中音“4”的频率698Hz
#define sao 128     //将“sao”宏定义为中音“5”的频率784Hz
#define la 114      //将“la”宏定义为中音“6”的频率880Hz
#define xi 101      //将“xi”宏定义为中音“7”的频率523H      
//以下是C调高音的音频宏定义
#define h_dao 96     //将“h_dao”宏定义为高音“1”的频率1046Hz
#define h_re 85      //将“h_re”宏定义为高音“2”的频率1174Hz
#define h_mi 76      //将“h_mi”宏定义为高音“3”的频率1318Hz
#define h_fa 72     //将“h_fa”宏定义为高音“4”的频率1396Hz
#define h_sao 64    //将“h_sao”宏定义为高音“5”的频率1567Hz
#define h_la 57     //将“h_la”宏定义为高音“6”的频率1760Hz
#define h_xi 51     //将“h_xi”宏定义为高音“7”的频率1975Hz

//端口的输入输出函数
char inp(unsigned int addr);
void outp(unsigned int addr, char data);

//步进电机的相序表
unsigned char table1[8]={0x02,0x06,0x04,0x0c,0x08,0x09,0x01,0x03};
unsigned char table2[8]={0x03,0x01,0x09,0x08,0x0c,0x04,0x06,0x02};
 
 //一档函数       监视一档						//一档的时间延时
 void yidang(); unsigned char watchyidang(unsigned char m);	void delay2();
 //二档函数	监视二档						//二档的时间延时
 void erdang(); unsigned char watcherdang(unsigned char m);	void delay3();
//三档函数	监视三档						//三档的时间延时
void sandang(); unsigned char watchsandang(unsigned char m);	void delay4();
//四档函数	监视四档						//四档的时间延时
void sidang();	unsigned char watchsidang(unsigned char m);	void delay();
//倒车函数        监视倒车						//倒车的时间延时
void backdang(); unsigned char watchdaoche(unsigned char m);	void delayDao();
//按喇叭           监视喇叭					//喇叭的延时时间
void pressLaba(); unsigned char watchLaba(unsigned char m);	void delayLaba();
//油门函数		监视油门						//油门的时间延时
unsigned char youmen(); unsigned char watchYoumen(unsigned char m);	void delayYoumen();
//左转向灯
void turnLeft(unsigned char tmp);

//公用的加速度
unsigned char myYoumenAcc=0;
//转向灯
unsigned char turn;

void main(void)
{
    unsigned char button,i,tmp;
    outp(IOCON,0x99);
    i=0;	button=0;
    while(1)
    {
       //从A口都如数据
        button=inp(IOA);
        turn=inp(IOC);
       //如果逆时针转(4档)
        if(button==0xfd){sidang();}
	//顺时针转
	if(button==0xfe){backdang();}
        //按下停止(熄火，刹车)
        if(button==0xfb)
       {
	  //初始化速度表的8255芯片
	  outp(IOA8255,zero);//A口控制现实的数字
          outp(IOB8255,pos);//b口控制显示的位置
	  outp(IOB,0xf0);
        }
        //一档
        if(button==0xf7){yidang();}
        //二档
        if(button==0xef){erdang();}
        //三档
        if(btnsandang==button){sandang();}
        //喇叭
        if(btnlaba==button){pressLaba();}
	//油门
	if(btnyoumen==button)
	{   
	   //我的AD转换，油门 
	   myYoumenAcc=youmen();   
	}
    }
}

//左转向灯
void turnLeft(unsigned char tmp)
{
    //读取转向
    turn=inp(IOC);
    if(turn==0xef)
    {
       for(int sk=0;sk<50;sk++)
       {
	      outp(IOB,0x40|table2[tmp]);
	      for(int j=0;j<20;j++){}
	      outp(IOB,table2[tmp]);
       }
    }
}

//右转向灯
void turnRight(unsigned char tmp)
{
    //读取转向
    turn=inp(IOC);
    if(turn==0xdf)
    {
       for(int sk=0;sk<50;sk++)
       {
	      outp(IOB,0x80|table2[tmp]);
	      for(int j=0;j<20;j++){}
	      outp(IOB,table2[tmp]);
       }
    }
}

//油门函数
unsigned char youmen()
{
   unsigned char button;
   unsigned char in;
   while(1)
   {
      for(char iii=10000;iii>0;iii--)
      {
	    
	    //从A口读入按键数据
	    button=inp(IOA);
	    if(watchYoumen(button))
	    {
	        return in;
		break;
	    }
	 
	    outp(AD0809,0);
	    in=inp(AD0809);
      }
      outp(OUT373,in);
      myYoumenAcc=in;
      //从A口读入按键数据
      button=inp(IOA);
      if(watchYoumen(button))
      {
	   return in;
	   break;
      }
       //用数码管显示
      /*(inp(my373))*/
      unsigned char tempNum=(unsigned char)in/10;
      unsigned char weishu[2];
      weishu[0]=tempNum/10;
      weishu[1]=tempNum%10;
      unsigned char mypos=pos<<2;
      for(unsigned char kkk=0;kkk<2;kkk++)
      {
	 outp(IOA8255,number[weishu[kkk]]);//A口控制现实的数字
         outp(IOB8255,mypos);//b口控制显示的位置
	  //从A口读入按键数据
	 button=inp(IOA);
	 delayYoumen();
	 mypos<<=1;
	 if(watchYoumen(button))
	 {
	      return in;
	      break;
	 }
      }
   }
   return in;
}
//监视油门
unsigned char watchYoumen(unsigned char button)
{
    if(btnlaba==button || btnsandang==button || button==0xef || button==0xf7 || button==0xfb || button==0xfe || button==0xfd)
    {
	return 1;
    }
    return 0;
}

void delayYoumen()
{
   unsigned char m;
   for(int i=0;i<350;i++)
   {
      m=inp(IOA);
      if(m==0xfe||m==0xfb || m==0xfd || m==0xef || btnsandang==m || btnlaba==m  || 0xfe==m || 0xf7==m)
      {
	  break;
      }
   }
}

//倒车函数
void backdang()
{
    unsigned char button,i,tmp;
    outp(IOCON8255,0x80);
	   while(1)
	   {
	      //显示“dao”，提醒倒车
	      unsigned char mypos=pos;
	      for(int sk=0;sk<3;sk++)
	      {
		 outp(IOA8255,daoche[sk]);//A口控制现实的数字
                 outp(IOB8255,mypos);//b口控制显示的位置
		 if(button==0xfd||button==0xfb || button==0xf7 || i==0xef || btnsandang==button ||btnlaba==button || btnyoumen==button)break;
		 delayDao();
		 mypos<<=1;
	      }
	      for(tmp=0;tmp<8;tmp++)
	      {
		outp(IOB,table1[tmp]);
		outp(IOB,0x30|table1[tmp]);
		button=inp(IOA);
		if(watchdaoche(button)){break;}
		delay();
	      }
	      if(watchdaoche(button)){break;}
           }
}
//监视倒车
unsigned char watchdaoche(unsigned char button)
{
    if(button==0xfd||button==0xfb || button==0xf7 || button==0xef || btnsandang==button ||btnlaba==button || btnyoumen==button)
    {
	return 1;
    }
    return 0;
}

//四档函数
void sidang()
{
    unsigned char button,i,tmp;
   //初始化速度表的8255芯片
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,four);//A口控制现实的数字
        outp(IOB8255,pos);//b口控制显示的位置
	for(tmp=0;tmp<8;tmp++)
	{
	    turnRight(tmp);
	    turnLeft(tmp);
	    outp(IOB,table2[tmp]);
	    button=inp(IOA);
	    if(watchsidang(button))break;
	    delay();
	}
	if(watchsidang(button))break;
	turnRight(tmp);
	turnLeft(tmp);
    }
}

//监视四档
unsigned char watchsidang(unsigned char button)
{
   if(button==0xfe||button==0xfb || button==0xf7 || button==0xef || btnsandang==button || btnlaba==button  || btnyoumen==button)
   {
	return 1;
   }
   return 0;
}

//三档函数
void sandang()
{
    unsigned char button,i,tmp;
   //初始化速度表的8255芯片
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,three);//A口控制现实的数字
        outp(IOB8255,pos);//b口控制显示的位置
	for(tmp=0;tmp<8;tmp++)
	{
	    outp(IOB,table2[tmp]);
	    i=inp(IOA);
	    turnLeft(tmp);
	    turnRight(tmp);
	    if(watchsandang(i)){break;}
	    delay4();
            if(watchsandang(i)){break;}
	 }
	 if(watchsandang(i)){break;}
	 turnLeft(tmp);
	 turnRight(tmp);
    }
}

//监视三档
unsigned char watchsandang(unsigned char i)
{
    if(i==0xfe||i==0xfb || i==0xfd || i==0xf7 || btnerdang==i ||btnlaba==i  || btnyoumen==i)
    {
	 return 1;
    }
    return 0;
}

//二档函数
void erdang()
{
   unsigned char button,i,tmp;
   //初始化速度表的8255芯片
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,two);//A口控制现实的数字
        outp(IOB8255,pos);//b口控制显示的位置
	for(tmp=0;tmp<8;tmp++)
	{
	    outp(IOB,table2[tmp]);
	    i=inp(IOA);
	    turnLeft(tmp);
	    turnRight(tmp);
	    if(watcherdang(i)){break;}
	    delay3();
            if(watcherdang(i)){break;}
	    turnLeft(tmp);
	    turnRight(tmp);
	 }
	 if(watcherdang(i)){break;}
	 turnLeft(tmp);
	 turnRight(tmp);
    }
}
//监视二档
unsigned char watcherdang(unsigned char i)
{
   if(i==0xfe||i==0xfb || i==0xfd || i==0xf7 || btnlaba==i || btnsandang==i || btnyoumen==i)
   {
	return 1;
   }
   return 0;
}

//一档函数
void yidang()
{
   unsigned char button,i,tmp;
   outp(IOA8255,one);//A口控制现实的数字
   outp(IOB8255,pos);//b口控制显示的位置
   while(1)
   {
      for(tmp=0;tmp<8;tmp++)
      {
	  turnLeft(tmp);
	  turnRight(tmp);
	  outp(IOB,table2[tmp]);
	  i=inp(IOA);
	  if(watchyidang(i)){break;}
	  delay2();
	  if(watchyidang(i)){break;}
      }
      if(watchyidang(i)){break;}
      turnLeft(tmp);
      turnRight(tmp);
   }
}
//监视一档
unsigned char watchyidang(unsigned char i)
{
   if(i==0xfe||i==0xfb || i==0xfd || i==0xef ||  btnsandang==i || btnlaba==i || btnyoumen==i)
   {
       return 1;
   }
   return 0;
}
//三档的时间延时
void delay4()
{
    int i,j;
    unsigned char m;
    unsigned char shankai=(myYoumenAcc/10);
    if(shankai>=15)
    {
       shankai=14;
    }
    turnLeft(0);
    for(i=0;i<15-shankai;i++)
    {
       for(j=0;j<1;j++)
       {
	  turnLeft(0);
	  turnRight(0);
	  m=inp(IOA);
	  //初始化速度表的8255芯片
	  outp(IOA8255,three);//A口控制现实的数字
	  outp(IOB8255,pos);//b口控制显示的位置
	  if(watchsandang(m)){break;}
       }
       if(watchsandang(m)){break;}
       turnLeft(0);
    }
}

//一档的时间延时
void delay2()
{
    int i,j;
    unsigned char m;
    unsigned char shankai=(myYoumenAcc/10);
    for(i=0;i<30-shankai;i++)
    {
       for(j=0;j<1;j++)
       {
	  turnLeft(0);
	  turnRight(0);
	  m=inp(IOA);
	  //初始化速度表的8255芯片
	  outp(IOA8255,one);//A口控制现实的数字
	  outp(IOB8255,pos);//b口控制显示的位置
	  if(watchyidang(m)){break;}
       }
       if(watchyidang(m)){break;};
       turnLeft(0);
       turnRight(0);
    }  
}

//二档的时间延时
void delay3()
{
    int i,j;
    unsigned char m;
    unsigned char shankai=myYoumenAcc/10;
    if(shankai>=20)
    {
       shankai=19;
    }
    for(i=0;i<20-shankai;i++)
    {
       for(j=0;j<1;j++)
       {
	  m=inp(IOA);
	  turnLeft(0);
	  turnRight(0);
	  if(watcherdang(m)){break;}//如果监视到有别的键按下，跳出
       }
      if(watcherdang(m)){break;}//如果监视到有别的键按下，跳出
    }
}

//4档的时间延时
void delay()
{
    int i,j;
    for(i=5;i>0;i--)
    {
        for(j=0;j<1;j++)
	{
	    turnRight(0);
	    turnLeft(0);
	}
    }
}

//喇叭的时间延时
void delayLaba()               
{
     unsigned char i,j;
     unsigned char m;
     for(i=0;i<250;i++)
     {
	m=inp(IOA);
	if(watchLaba(m))
	{
	   outp(TCONTRO,0x10);
	   break;
	}
	for(j=0;j<4;j++)
	{
	   m=inp(IOA);
	   if(watchLaba(m))
	   {
	      outp(TCONTRO,0x10);
	      break;
	   }
	}
     }
}

unsigned char watchLaba(unsigned char m)
{
    if(m==0xfe||m==0xfb || m==0xfd || m==0xef || m==btnerdang  || btnyoumen==m)
    {
        return 1;
    }
    return 0;
}

//按喇叭
void pressLaba()
{
     unsigned char i,j;
     unsigned int count;     //储存定时器的定时常数
     unsigned int ch, cl;     //储存定时器的定时常数

     
     //以下是《渴望》片头曲的一段简谱
     unsigned  int cf[]={re,mi,re,dao,l_la,dao,l_la,   //每行对应一小节音符
                           l_sao,l_mi,l_sao,l_la,dao,
							      l_la,dao,sao,la,mi,sao,
							      re,					
							      mi,re,mi,sao,mi,
							      l_sao,l_mi,l_sao,l_la,dao,
                           l_la,l_la,dao,l_la,l_sao,l_re,l_mi,
									l_sao,
									re,re,sao,la,sao,
									fa,mi,sao,mi,
									la,sao,mi,re,mi,l_la,dao,
									re,
									mi,re,mi,sao,mi,
									l_sao,l_mi,l_sao,l_la,dao,
									l_la,dao,re,l_la,dao,re,mi,
									re,
									l_la,dao,re,l_la,dao,re,mi,
									re,
									0xff}; //以0xff作为音符的结束标志					
      //以下是简谱中每个音符的节拍
      //"4"对应4个延时单位，"2"对应2个延时单位，"1"对应1个延时单位 
      unsigned char JP[]={4,1,1,4,1,1,2,  
			   2,2,2,2,8,
							      4,2,3,1,2,2,
							      10,
							      4,2,2,4,4,
							      2,2,2,2,4,
			   2,2,2,2,2,2,2,
							      10,
							      4,4,4,2,2,
							      4,2,4,4,
							      4,2,2,2,2,2,2,
							      10,
							      4,2,2,4,4,
							      2,2,2,2,6,
							      4,2,2,4,1,1,4,
							      10,
							      4,2,2,4,1,1,4,
							      10
							      };

			
	   //初始化8253
           outp(TCONTRO,0x36);//计数器0，只写计算值低8位，方式3，二进制计数
	   //初始化速度显示表8255
	   outp(IOCON8255,0x80);			
	   while(1)       //无限循环
           {
		 i=0;   //从第1个音符f[0]开始播放
	         unsigned char button=inp(IOA);
		 if(watchLaba(button))
		 {
		     outp(TCONTRO,0x10);
		     break;
		 }
		 //显示“laba”，提醒倒车
		 unsigned char mypos=pos;
		 for(int sk=0;sk<4;sk++)
		 {
		    outp(IOA8255,laba[sk]);//A口控制现实的数字
		    outp(IOB8255,mypos);//b口控制显示的位置
		    if(watchLaba(button))
		    {
		       outp(TCONTRO,0x10);
		       break;
		    }
		    mypos<<=1;
		 }
		 if(watchLaba(button))
		 {
		     outp(TCONTRO,0x10);
		     break;
		 }
		 while(cf[i]!=0xff)            //只要没有读到结束标志就继续播放
		 {
		      //如果按下了其他按键就停止
		      button=inp(IOA);
		      if(watchLaba(button))
		      {
			   outp(TCONTRO,0x10);
		           break;
		      }
		      ch=cf[i]/256;	      
		      cl=cf[i]%256;	      
		      outp(TCON0,cl);   
		      outp(TCON0,ch);
		    
		      for(j=0;j<JP[i];j++)  //控制节拍数
		      {
			 button=inp(IOA);
			 if(watchLaba(button))
			 {
			     outp(TCONTRO,0x10);
			     break;
			 }
			 delayLaba();          //延时1个节拍单位
		      }
		      i++;                 //播放下一个音符
		 }   
		  button=inp(IOA);
		  if(watchLaba(button))
		  {
		       outp(TCONTRO,0x10);
		       break;
		  }
	   }	
}

//倒车的时间延时
void delayDao()
{
   unsigned char m;
   for(int i=0;i<100;i++)
   {
      m=inp(IOA);
      if(m==0xfe||m==0xfb || m==0xfd || m==0xef || btnsandang==m || btnlaba==m  || btnyoumen==m)
      {
	  break;
      }
   }
}

//端口的输出函数
void outp(unsigned int addr, char data)
// Write a byte to the specified I/O port
 { __asm
    { mov dx, addr
      mov al, data
      out dx, al
    }
 }
//端口的输入函数
char inp(unsigned int addr)
// Read a byte from the specified I/O port
 { char result;
   __asm
    { mov dx, addr
      in al, dx
      mov result, al
    }
   return result;
 }