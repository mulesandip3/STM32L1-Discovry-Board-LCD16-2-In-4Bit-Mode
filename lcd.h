#include "stm32l1xx.h"

#define LED3 GPIO_Pin_9
#define LED4 GPIO_Pin_8

void led_gpio_init(void);

void lcd_gpio_init(void);
void lcd_init(void);

void write_cmd(int cmd);
void write_data(int data);

void lcd_data(uint8_t data);
void lcd_cmd(uint8_t cmd);

void lcd_str(char *str);

void delay(unsigned long b);

