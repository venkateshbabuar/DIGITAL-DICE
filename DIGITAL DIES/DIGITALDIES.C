#include<LPC21xx.h>
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(unsigned char *);
void LCD_INTEGER(int);
unsigned int a=0;
#define LCD_D 0xff<<0
#define RS 1<<17
#define E  1<<18

void delay(int ms)
{
int i;
for(;ms>0;ms--)
for(i=12000;i>0;i--);
}
void ext0_int_isr(void)__irq
{
EXTINT=0x01;

T0PR=6-1;
T0TCR=0x01;
a=T0PC;
if (a==0)
a=6;


VICVectAddr=0;

}
int main()
{
int count=0;
LCD_INIT();

PINSEL1=1<<0;
VICIntSelect=0;
VICVectCntl0=0x20|14;
VICVectAddr0=(unsigned long)ext0_int_isr  ;
EXTMODE=0x01;
EXTPOLAR=0x00;
VICIntEnable=1<<14;
while(1)
{
LCD_CMD(0x80);
LCD_STRING("DICE:");
LCD_CMD(0xc0);
LCD_INTEGER(a);
LCD_CMD(0x87);
LCD_STRING("COUNT:");
LCD_CMD(0xc7);
LCD_INTEGER(count);




		  if((IOPIN0&1<<16)==0)
		  {
		  delay(100);
		  count++;
		  
		  }
}

}
void LCD_INIT(void)
{
IODIR0=LCD_D|RS|E;
LCD_CMD(0x01);
LCD_CMD(0x02);
LCD_CMD(0x0c);
LCD_CMD(0x38);
LCD_CMD(0x80);
}
void LCD_CMD(unsigned char cmd)
{
IOCLR0=LCD_D;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=E;
delay(20);
IOCLR0=E;
}
void LCD_DATA(unsigned char d)
{
IOCLR0=LCD_D;
IOSET0=d;
IOSET0=RS;
IOSET0=E;
delay(20);
IOCLR0=E;
}
void LCD_STRING(unsigned char *s)
{
while(*s)
{
   LCD_DATA(*s)	;
   s++;
}
  }
  void LCD_INTEGER(int a)
  {
  unsigned char b[20];
  unsigned int i=0;
  signed int j;
  if(a==0)
  LCD_DATA('0');
  else
  {
  if(a<0)
  {
  LCD_DATA('-');
  a=-a;
  }
  while(a>0)
  {
  b[i++]=a%10;
  a/=10	;

  }
  for(j=i-1;j>=0;j--)
  LCD_DATA(b[j]+48);

  }

  }
