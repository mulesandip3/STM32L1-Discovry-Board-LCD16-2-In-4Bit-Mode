#include "lcd.h"

int main()
{
	lcd_init();
	led_gpio_init();
	while(1)
	{
		GPIO_SetBits(GPIOC , LED3);
		GPIO_SetBits(GPIOC , LED4);
	  delay(100000);
		lcd_cmd(0x01);
		lcd_str("Sandip");
		GPIO_ResetBits(GPIOC , LED3);
		GPIO_ResetBits(GPIOC , LED4);
		delay(100000);
	}
}

