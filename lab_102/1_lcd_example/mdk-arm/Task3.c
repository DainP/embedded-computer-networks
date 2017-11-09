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

gpio_pin_t temp = {PF_7, GPIOF, GPIO_PIN_7};
gpio_pin_t ldr = {PA_0, GPIOA, GPIO_PIN_0};

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
	init_adc(temp);
	init_adc(ldr);
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
  
  // calibration
	
	// print progress message
	BSP_LCD_DisplayStringAtLine(4, (uint8_t *)"CALIBRATING ..."); 
	
	// calibration variables
	uint16_t sensor_min = 4096;
	uint16_t sensor_max = 0;
	uint32_t end_time = HAL_GetTick() + 5000;
	
	// calibration loop
	while(HAL_GetTick() < end_time)
	{
		// read current sensor value
		uint16_t sensor_value = read_adc(ldr);
		
		// check against the max and min values
		if(sensor_value > sensor_max)
		{
			sensor_max = sensor_value;
		}		
		if(sensor_value < sensor_min)
		{
			sensor_min = sensor_value;
		}
	}
	
	// display those values
	char calib_str[25];
	sprintf(calib_str, "MAX = %4d : MIN = %4d", sensor_max, sensor_min);
	BSP_LCD_DisplayStringAtLine(4, (uint8_t *)calib_str); 
	
	// main loop
  while(1)
  {
		// read adc values ...
		
		// temp
		uint16_t adc_val = read_adc(temp);
		float adc_vol = (adc_val/4095.0) * 3.3;
		float adc_temp = ((adc_vol * 1000) - 500) / 10.0;
    	
		// light

    uint16_t ldr_val = read_adc(ldr);		
		float fldr_val = ldr_val;
		float fsensor_max = sensor_max;
		float ldr = (fldr_val / fsensor_max) * 100.0; 
	
		// display temperature
		char str[20];
		sprintf(str, "Temp = %3.2f", adc_temp);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		// display light
		char ldr_str[20];
		sprintf(ldr_str, "LDR Value = %3.2f", ldr);
		BSP_LCD_DisplayStringAtLine(8, (uint8_t *)ldr_str);
		
		// thresholds ...
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

  }
}