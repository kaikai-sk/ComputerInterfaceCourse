//���������8255�ĸ����˿ڵĵ�ַ
#define IOCON	8006H
#define IOA     8000H
#define IOB     8002H
#define IOC     8004H

//�ٶȱ�8255�ĸ����˿ڵ�ַ
#define IOCON8255   0A060H
#define IOA8255     0A000H
#define IOB8255     0A020H
#define IOC8255     0A040H

//�������оƬ�ĵ�ַ
#define AD0809	0C100H
#define OUT373  0B000H
#define my373   0D000H

//�����ĸ�������
#define btnerdang 0xef
#define btnsandang 0xdf
#define btnlaba 0xbf
#define btnyidang 0xf7
#define btnyoumen 0x7f
//�ٶȱ�������ʾ
#define pos 0x01
#define one 0F9H
#define two 0A4H 
#define three 0B0H
#define zero 0C0H 
#define four 99h
unsigned char number[10]={0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H}; 
unsigned char daoche[3]={0xa1,88H,0C0H};//��dao��
unsigned char laba[4]={0xc7,88H,80H,88H};//"laba"

//8253�����˿ڵĵ�ַ
#define TCONTRO   9018H
#define TCON0     9000H
#define TCON1     9008H
#define TCON2     9010H

//ʵ��49���ö�ʱ��T0���ж�ʵ��"����"�������Ĳ���
//#define feq 1000000
//������C����������Ƶ�궨��
#define l_dao 382   //����l_dao���궨��Ϊ������1����Ƶ��262Hz
#define l_re 350    //����l_re���궨��Ϊ������2����Ƶ��286Hz
#define l_mi 322    //����l_mi���궨��Ϊ������3����Ƶ��311Hz
#define l_fa 287    //����l_fa���궨��Ϊ������4����Ƶ��349Hz
#define l_sao 253   //����l_sao���궨��Ϊ������5����Ƶ��392Hz
#define l_la 227    //����l_a���궨��Ϊ������6����Ƶ��440Hz
#define l_xi 202    //����l_xi���궨��Ϊ������7����Ƶ��494Hz
//������C����������Ƶ�궨��
#define dao 191     //����dao���궨��Ϊ������1����Ƶ��523Hz
#define re 170      //����re���궨��Ϊ������2����Ƶ��587Hz
#define mi 152      //����mi���궨��Ϊ������3����Ƶ��659Hz
#define fa 143      //����fa���궨��Ϊ������4����Ƶ��698Hz
#define sao 128     //����sao���궨��Ϊ������5����Ƶ��784Hz
#define la 114      //����la���궨��Ϊ������6����Ƶ��880Hz
#define xi 101      //����xi���궨��Ϊ������7����Ƶ��523H      
//������C����������Ƶ�궨��
#define h_dao 96     //����h_dao���궨��Ϊ������1����Ƶ��1046Hz
#define h_re 85      //����h_re���궨��Ϊ������2����Ƶ��1174Hz
#define h_mi 76      //����h_mi���궨��Ϊ������3����Ƶ��1318Hz
#define h_fa 72     //����h_fa���궨��Ϊ������4����Ƶ��1396Hz
#define h_sao 64    //����h_sao���궨��Ϊ������5����Ƶ��1567Hz
#define h_la 57     //����h_la���궨��Ϊ������6����Ƶ��1760Hz
#define h_xi 51     //����h_xi���궨��Ϊ������7����Ƶ��1975Hz

//�˿ڵ������������
char inp(unsigned int addr);
void outp(unsigned int addr, char data);

//��������������
unsigned char table1[8]={0x02,0x06,0x04,0x0c,0x08,0x09,0x01,0x03};
unsigned char table2[8]={0x03,0x01,0x09,0x08,0x0c,0x04,0x06,0x02};
 
 //һ������       ����һ��						//һ����ʱ����ʱ
 void yidang(); unsigned char watchyidang(unsigned char m);	void delay2();
 //��������	���Ӷ���						//������ʱ����ʱ
 void erdang(); unsigned char watcherdang(unsigned char m);	void delay3();
//��������	��������						//������ʱ����ʱ
void sandang(); unsigned char watchsandang(unsigned char m);	void delay4();
//�ĵ�����	�����ĵ�						//�ĵ���ʱ����ʱ
void sidang();	unsigned char watchsidang(unsigned char m);	void delay();
//��������        ���ӵ���						//������ʱ����ʱ
void backdang(); unsigned char watchdaoche(unsigned char m);	void delayDao();
//������           ��������					//���ȵ���ʱʱ��
void pressLaba(); unsigned char watchLaba(unsigned char m);	void delayLaba();
//���ź���		��������						//���ŵ�ʱ����ʱ
unsigned char youmen(); unsigned char watchYoumen(unsigned char m);	void delayYoumen();
//��ת���
void turnLeft(unsigned char tmp);

//���õļ��ٶ�
unsigned char myYoumenAcc=0;
//ת���
unsigned char turn;

void main(void)
{
    unsigned char button,i,tmp;
    outp(IOCON,0x99);
    i=0;	button=0;
    while(1)
    {
       //��A�ڶ�������
        button=inp(IOA);
        turn=inp(IOC);
       //�����ʱ��ת(4��)
        if(button==0xfd){sidang();}
	//˳ʱ��ת
	if(button==0xfe){backdang();}
        //����ֹͣ(Ϩ��ɲ��)
        if(button==0xfb)
       {
	  //��ʼ���ٶȱ��8255оƬ
	  outp(IOA8255,zero);//A�ڿ�����ʵ������
          outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
	  outp(IOB,0xf0);
        }
        //һ��
        if(button==0xf7){yidang();}
        //����
        if(button==0xef){erdang();}
        //����
        if(btnsandang==button){sandang();}
        //����
        if(btnlaba==button){pressLaba();}
	//����
	if(btnyoumen==button)
	{   
	   //�ҵ�ADת�������� 
	   myYoumenAcc=youmen();   
	}
    }
}

//��ת���
void turnLeft(unsigned char tmp)
{
    //��ȡת��
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

//��ת���
void turnRight(unsigned char tmp)
{
    //��ȡת��
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

//���ź���
unsigned char youmen()
{
   unsigned char button;
   unsigned char in;
   while(1)
   {
      for(char iii=10000;iii>0;iii--)
      {
	    
	    //��A�ڶ��밴������
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
      //��A�ڶ��밴������
      button=inp(IOA);
      if(watchYoumen(button))
      {
	   return in;
	   break;
      }
       //���������ʾ
      /*(inp(my373))*/
      unsigned char tempNum=(unsigned char)in/10;
      unsigned char weishu[2];
      weishu[0]=tempNum/10;
      weishu[1]=tempNum%10;
      unsigned char mypos=pos<<2;
      for(unsigned char kkk=0;kkk<2;kkk++)
      {
	 outp(IOA8255,number[weishu[kkk]]);//A�ڿ�����ʵ������
         outp(IOB8255,mypos);//b�ڿ�����ʾ��λ��
	  //��A�ڶ��밴������
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
//��������
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

//��������
void backdang()
{
    unsigned char button,i,tmp;
    outp(IOCON8255,0x80);
	   while(1)
	   {
	      //��ʾ��dao�������ѵ���
	      unsigned char mypos=pos;
	      for(int sk=0;sk<3;sk++)
	      {
		 outp(IOA8255,daoche[sk]);//A�ڿ�����ʵ������
                 outp(IOB8255,mypos);//b�ڿ�����ʾ��λ��
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
//���ӵ���
unsigned char watchdaoche(unsigned char button)
{
    if(button==0xfd||button==0xfb || button==0xf7 || button==0xef || btnsandang==button ||btnlaba==button || btnyoumen==button)
    {
	return 1;
    }
    return 0;
}

//�ĵ�����
void sidang()
{
    unsigned char button,i,tmp;
   //��ʼ���ٶȱ��8255оƬ
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,four);//A�ڿ�����ʵ������
        outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
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

//�����ĵ�
unsigned char watchsidang(unsigned char button)
{
   if(button==0xfe||button==0xfb || button==0xf7 || button==0xef || btnsandang==button || btnlaba==button  || btnyoumen==button)
   {
	return 1;
   }
   return 0;
}

//��������
void sandang()
{
    unsigned char button,i,tmp;
   //��ʼ���ٶȱ��8255оƬ
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,three);//A�ڿ�����ʵ������
        outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
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

//��������
unsigned char watchsandang(unsigned char i)
{
    if(i==0xfe||i==0xfb || i==0xfd || i==0xf7 || btnerdang==i ||btnlaba==i  || btnyoumen==i)
    {
	 return 1;
    }
    return 0;
}

//��������
void erdang()
{
   unsigned char button,i,tmp;
   //��ʼ���ٶȱ��8255оƬ
   outp(IOCON8255,0x80);
    while(1)
    {
        outp(IOA8255,two);//A�ڿ�����ʵ������
        outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
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
//���Ӷ���
unsigned char watcherdang(unsigned char i)
{
   if(i==0xfe||i==0xfb || i==0xfd || i==0xf7 || btnlaba==i || btnsandang==i || btnyoumen==i)
   {
	return 1;
   }
   return 0;
}

//һ������
void yidang()
{
   unsigned char button,i,tmp;
   outp(IOA8255,one);//A�ڿ�����ʵ������
   outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
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
//����һ��
unsigned char watchyidang(unsigned char i)
{
   if(i==0xfe||i==0xfb || i==0xfd || i==0xef ||  btnsandang==i || btnlaba==i || btnyoumen==i)
   {
       return 1;
   }
   return 0;
}
//������ʱ����ʱ
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
	  //��ʼ���ٶȱ��8255оƬ
	  outp(IOA8255,three);//A�ڿ�����ʵ������
	  outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
	  if(watchsandang(m)){break;}
       }
       if(watchsandang(m)){break;}
       turnLeft(0);
    }
}

//һ����ʱ����ʱ
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
	  //��ʼ���ٶȱ��8255оƬ
	  outp(IOA8255,one);//A�ڿ�����ʵ������
	  outp(IOB8255,pos);//b�ڿ�����ʾ��λ��
	  if(watchyidang(m)){break;}
       }
       if(watchyidang(m)){break;};
       turnLeft(0);
       turnRight(0);
    }  
}

//������ʱ����ʱ
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
	  if(watcherdang(m)){break;}//������ӵ��б�ļ����£�����
       }
      if(watcherdang(m)){break;}//������ӵ��б�ļ����£�����
    }
}

//4����ʱ����ʱ
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

//���ȵ�ʱ����ʱ
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

//������
void pressLaba()
{
     unsigned char i,j;
     unsigned int count;     //���涨ʱ���Ķ�ʱ����
     unsigned int ch, cl;     //���涨ʱ���Ķ�ʱ����

     
     //�����ǡ�������Ƭͷ����һ�μ���
     unsigned  int cf[]={re,mi,re,dao,l_la,dao,l_la,   //ÿ�ж�ӦһС������
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
									0xff}; //��0xff��Ϊ�����Ľ�����־					
      //�����Ǽ�����ÿ�������Ľ���
      //"4"��Ӧ4����ʱ��λ��"2"��Ӧ2����ʱ��λ��"1"��Ӧ1����ʱ��λ 
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

			
	   //��ʼ��8253
           outp(TCONTRO,0x36);//������0��ֻд����ֵ��8λ����ʽ3�������Ƽ���
	   //��ʼ���ٶ���ʾ��8255
	   outp(IOCON8255,0x80);			
	   while(1)       //����ѭ��
           {
		 i=0;   //�ӵ�1������f[0]��ʼ����
	         unsigned char button=inp(IOA);
		 if(watchLaba(button))
		 {
		     outp(TCONTRO,0x10);
		     break;
		 }
		 //��ʾ��laba�������ѵ���
		 unsigned char mypos=pos;
		 for(int sk=0;sk<4;sk++)
		 {
		    outp(IOA8255,laba[sk]);//A�ڿ�����ʵ������
		    outp(IOB8255,mypos);//b�ڿ�����ʾ��λ��
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
		 while(cf[i]!=0xff)            //ֻҪû�ж���������־�ͼ�������
		 {
		      //�������������������ֹͣ
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
		    
		      for(j=0;j<JP[i];j++)  //���ƽ�����
		      {
			 button=inp(IOA);
			 if(watchLaba(button))
			 {
			     outp(TCONTRO,0x10);
			     break;
			 }
			 delayLaba();          //��ʱ1�����ĵ�λ
		      }
		      i++;                 //������һ������
		 }   
		  button=inp(IOA);
		  if(watchLaba(button))
		  {
		       outp(TCONTRO,0x10);
		       break;
		  }
	   }	
}

//������ʱ����ʱ
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

//�˿ڵ��������
void outp(unsigned int addr, char data)
// Write a byte to the specified I/O port
 { __asm
    { mov dx, addr
      mov al, data
      out dx, al
    }
 }
//�˿ڵ����뺯��
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