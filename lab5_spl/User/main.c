#include "main.h"
#include "pictures.h"

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	LCD_init();
	LCD_set_XY(0, 0);
	
	//
	while(1){
		LCD_write_bitmap(pic0);
		delay_ms(1000);
		LCD_write_bitmap(pic1);
		delay_ms(1000);
		LCD_write_bitmap(pic2);
		delay_ms(1000);
		LCD_write_bitmap(pic3);
		delay_ms(1000);
		LCD_write_bitmap(pic4);
		delay_ms(1000);
		LCD_write_bitmap(pic5);
		delay_ms(1000);
		LCD_write_bitmap(pic6);
		delay_ms(1000);
		LCD_write_bitmap(pic7);
		delay_ms(1000);
		LCD_write_bitmap(pic8);
		delay_ms(1000);
	}
}
