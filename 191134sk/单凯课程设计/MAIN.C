#define IOCON	8006H
#define IOA     8000H
#define IOB     8002H
#define IOC     8004H

unsigned char table1[8]={0x02,0x06,0x04,0x0c,0x08,0x09,0x01,0x03};
unsigned char table2[8]={0x03,0x01,0x09,0x08,0x0c,0x04,0x06,0x02};

void outp(unsigned int addr, char data)
// Write a byte to the specified I/O port
 { __asm
    { mov dx, addr
      mov al, data
      out dx, al
    }
 }

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
void delay()
{
    int i,j;
    for(i=10;i>0;i--)
    for(j=0;j<1;j++){}
}
void main(void)
{
    unsigned char i,tmp;
    outp(IOCON,0x90);
    i=0;
    while(1){
        i=inp(IOA);
        if(i==0xfd)
        while(1){
	     for(tmp=0;tmp<8;tmp++){
		outp(IOB,table2[tmp]);
		i=inp(IOA);
		if(i==0xfe||i==0xfb)break;
		delay();
	     }
	     if(i==0xfe||i==0xfb)break;
	}
	if(i==0xfe)
	while(1){
	     for(tmp=0;tmp<8;tmp++){
		outp(IOB,table1[tmp]);
		i=inp(IOA);
		if(i==0xfd||i==0xfb)break;
		delay();
	     }
	     if(i==0xfd||i==0xfb)break;
       }
       if(i==0xfb)outp(IOB,0xf0);
    }
}