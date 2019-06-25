#include "LCD.h"
#include "Font.h"

uint16_t delay_count=0;

void SysTick_Handler(void)//1ms
{
	if (delay_count > 0){delay_count--;}
}

void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	while(delay_count){}
}

void LCD_MO(unsigned char OnOff)
{
	if (OnOff)
		GPIO_SetBits(GPIOC, GPIO_Pin_6);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_6);
}
void LCD_write_string(char *s)
{
  unsigned char ch;
    while(*s!='\0')
  {
    ch = *s;
    LCD_write_char(ch);
    s++;
  }
}
void LCD_GPIO_Config()
{
	GPIO_InitTypeDef GPIOA_Init;
	GPIO_InitTypeDef GPIOC_Init;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	GPIOA_Init.GPIO_Pin = GPIO_Pin_8;
	GPIOA_Init.GPIO_Speed = GPIO_Speed_25MHz;
	GPIOA_Init.GPIO_Mode = GPIO_Mode_OUT;
	GPIOA_Init.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIOA_Init.GPIO_OType = GPIO_OType_PP;
	GPIOC_Init.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIOC_Init.GPIO_Speed = GPIO_Speed_25MHz;
	GPIOC_Init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOC_Init.GPIO_Mode = GPIO_Mode_OUT;
	GPIOC_Init.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA,&GPIOA_Init);
	GPIO_Init(GPIOC,&GPIOC_Init);
}
void LCD_write_byte(unsigned char dat, unsigned char mode)
{
	unsigned char i;
	LCD_CS_OFF();
	if (!mode) LCD_DC_OFF(); else LCD_DC_ON(); 
	for(i = 0; i < 8; i++)
	{
		LCD_MO(dat & 0x80);
		dat = dat<<1;
		LCD_SCK_OFF();
		LCD_SCK_ON();
	}
	LCD_CS_ON(); 
}
void LCD_clear()
{
  unsigned char i,j;
  for(i=0;i<6;i++)
    for(j=0;j<84;j++)
      LCD_write_byte(0,1);
}
void LCD_write_bitmap(uint8_t* pic){
	unsigned char i,j;
  for(i=0;i<6;i++)
    for(j=0;j<84;j++)
      LCD_write_byte(pic[i*84+j],1);
}

void LCD_init()
{
	LCD_GPIO_Config();
	LCD_DC_ON();
	LCD_MO(1);
	LCD_SCK_ON();
	LCD_CS_ON();
	LCD_RST_OFF() ;
	delay_ms(40);
	LCD_RST_ON();
	LCD_write_byte(0x21,0);
	LCD_write_byte(0xc6,0);
	LCD_write_byte(0x06,0);
	LCD_write_byte(0x13,0);
	LCD_write_byte(0x20,0);
	LCD_clear();
	LCD_write_byte(0x0c,0);
}

void LCD_set_XY(unsigned char X,unsigned char Y)
{
  unsigned char x;
  x = 6*X;

  LCD_write_byte(0x40|Y,0);
  LCD_write_byte(0x80|x,0);
}

void LCD_write_char(unsigned char c) // write char
{
  unsigned char line;
  unsigned char ch = 0;

  c = c - 32;

  for(line=0;line<6;line++)
  {
    ch = font6_8[c][line];
    LCD_write_byte(ch,1); 
  }
}
void LCD_write_char_reg(unsigned char c) // write invert char
{
  unsigned char line;
  unsigned char ch = 0;

  c = c - 32;

  for(line=0;line<6;line++)
  {
    ch = ~font6_8[c][line];
    LCD_write_byte(ch,1);
    
  }
}

void LCD_Write_Dec(unsigned int b)
{
  unsigned char datas[4];

  datas[0] = b/1000;
  b = b - datas[0]*1000;
  datas[1] = b/100;
  b = b - datas[1]*100;
  datas[2] = b/10;
  b = b - datas[2]*10;
  datas[3] = b;

  datas[0]+=48;
  datas[1]+=48;
  datas[2]+=48;
  datas[3]+=48;

  LCD_write_char(datas[0]);
  LCD_write_char(datas[1]);
  LCD_write_char(datas[2]);
  LCD_write_char(datas[3]);
}
