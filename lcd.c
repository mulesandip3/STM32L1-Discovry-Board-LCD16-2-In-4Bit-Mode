#include "lcd.h"

#define LCD_D4 GPIO_Pin_12
#define LCD_D5 GPIO_Pin_13
#define LCD_D6 GPIO_Pin_14
#define LCD_D7 GPIO_Pin_15
#define LCD_RS GPIO_Pin_9
#define LCD_RW GPIO_Pin_8
#define LCD_EN GPIO_Pin_5

#define LED3 GPIO_Pin_9  /*LED3 Yellow*/
#define LED4 GPIO_Pin_8  /*LED4 Blue*/

void led_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED3 | LED4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void lcd_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7 | LCD_RS | LCD_RW | LCD_EN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void lcd_init(void)
{
	lcd_gpio_init();
	delay(300000);
	write_cmd(0x20 << 8);							        /* 4 Bit Mode 16*1 Line */ 
	lcd_cmd(0x28);                           /* 4 Bit Mode 16*2 Line */
  lcd_cmd(0x01);                          /* clear display */ 
  lcd_cmd(0x06);                          /* auto address inc */
	lcd_cmd(0x0C);                          /* Display on Cusor Blinking */
	lcd_cmd(0x80);                          /* first location */
	}

void write_cmd(int cmd)
{
	GPIO_ResetBits(GPIOB,LCD_RW);
	GPIO_ResetBits(GPIOB , LCD_D4|LCD_D5|LCD_D6|LCD_D7);
	GPIO_ResetBits(GPIOB,LCD_RS);
	GPIO_Write(GPIOB , (cmd & 0xF000));
	GPIO_SetBits(GPIOB,LCD_EN);
	delay(30000);
	GPIO_ResetBits(GPIOB,LCD_EN);	
}

void write_data(int data)
{
	GPIO_ResetBits(GPIOB,LCD_RW);
	GPIO_ResetBits(GPIOB , LCD_D4|LCD_D5|LCD_D6|LCD_D7);
	GPIO_SetBits(GPIOB,LCD_RS);
	GPIO_Write(GPIOB , (data & 0xF000));
	GPIO_SetBits(GPIOB,LCD_EN);
	delay(30000);
	GPIO_ResetBits(GPIOB,LCD_EN);
}

void lcd_data(uint8_t data)
{
  write_data(data << 8);
  write_data(data << 12);
}

void lcd_cmd(uint8_t cmd)
{
  write_cmd(cmd << 8);
  write_cmd(cmd << 12);
}

void lcd_str(char *str)
{
	while(*str !='\0')
	{
		lcd_data(*str);
		str++;
		delay(20000);
	}
}

void delay(unsigned long b)
{
  while (--b!=0); 
}
