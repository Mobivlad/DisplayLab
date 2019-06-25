#ifndef LCD_H

#define LCD_H

#include "main.h"

#define LCD_CS_ON() GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define LCD_CS_OFF() GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define LCD_RST_ON() GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define LCD_RST_OFF() GPIO_ResetBits(GPIOC, GPIO_Pin_8)
#define LCD_DC_ON() GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define LCD_DC_OFF() GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define LCD_SCK_ON() GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LCD_SCK_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_8)

void SysTick_Handler(void);
void delay_ms(uint16_t delay_temp);
void LCD_MO(unsigned char OnOff);
void LCD_GPIO_Config(void);
void LCD_write_byte(unsigned char dat, unsigned char mode);
void LCD_clear(void);
void LCD_init(void);
void LCD_write_string(char *s);
void LCD_set_XY(unsigned char X,unsigned char Y);
void LCD_write_char(unsigned char c);
void LCD_write_char_reg(unsigned char c);
void LCD_Write_Dec(unsigned int b);
void LCD_write_bitmap(uint8_t pic[]);
#endif
