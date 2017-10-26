/*
 * main.c
 *
 * this is the main lcd application
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2017
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
// Include the studio libary
#include <stdio.h>
#include "adc.h"
#include "gpio.h"

gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};

// Map Leds to pins
gpio_pin_t led1 = {PF_10,GPIOF,GPIO_PIN_10};
gpio_pin_t led2 = {PF_9,GPIOF,GPIO_PIN_9};
gpio_pin_t led3 = {PF_8,GPIOF,GPIO_PIN_8};

// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*     Hello LCD World!     *",
  "*      Welcome to SHU      *"
};

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  float bar;
	init_adc(pot);
	init_gpio(led1,OUTPUT);
	init_gpio(led2,OUTPUT);
	init_gpio(led3,OUTPUT);
	
  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER); 
  
  
  // delay a little ...
  HAL_Delay(5000);
  
  // display an "uptime" counter
//  BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"Current uptime =");
  int counter = 0;
	
  while(1)
  {
    // format a string based around the uptime counter
//    char str[20];
//    sprintf(str, "%d s", counter++);
//    // print the message to the lcd
//    BSP_LCD_ClearStringLine(6);
//    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		uint16_t adc_val = read_adc(pot);
		float percent = (adc_val/4095.0) * 100;
		
		
		//Drawing a rectangle - BSP_LCD_FillRect(xpos,ypos,  Height,  Width)    
		bar = percent * 4.8;
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(0,200,bar,20);
		
		char str[20];
		sprintf(str, "ADC = %3.2f", percent);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		
		if (adc_val > 0 && adc_val< 1365)
		{
			write_gpio(led1, HIGH);	
			write_gpio(led2, LOW);
			write_gpio(led3, LOW);
		}
		
		if (adc_val > 1364 && adc_val < 2730)
		{
			write_gpio(led1, LOW);	
			write_gpio(led2, HIGH);
			write_gpio(led3, LOW);
		}
		
		if (adc_val > 2729)
		{
			write_gpio(led1, LOW);	
			write_gpio(led2, LOW);
			write_gpio(led3, HIGH);
		}
		
	
    HAL_Delay(1000);
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		BSP_LCD_FillRect(0,200,480,20);
  }
}
