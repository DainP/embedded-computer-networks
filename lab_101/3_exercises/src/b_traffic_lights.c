/*
 * b_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PA8
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t led4 = {PI_2, GPIOI, GPIO_PIN_2};
gpio_pin_t led5 = {PA_15, GPIOA, GPIO_PIN_15};
gpio_pin_t led6 = {PA_8, GPIOA, GPIO_PIN_8};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  
  // initialise the gpio pin
  init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	init_gpio(led5, OUTPUT);
	init_gpio(led6, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    // toggle the led on the gpio pin1
    toggle_gpio(led1);
		//toggle the led on the gpio pina8
		toggle_gpio(led6);
    
		
    // wait for 10 second
    HAL_Delay(10000);
		
		 // toggle the led on the gpio pina8
    toggle_gpio(led6);
		
		// toggle the led on the gpio pina15
		toggle_gpio(led5);
		
		// wait for 1 second
		 HAL_Delay(2000);
		
		// toggle the led on the gpio pina15
		toggle_gpio(led5);
		
		// toggle the led on the gpio pinI2
		toggle_gpio(led4);
		
		//toggle the led on the gpio pinI1
		toggle_gpio(led1);
		
		//toggle the led on the gpiopinb14
		toggle_gpio(led2);
		
		HAL_Delay(2000);
		
		//toggle the led on the gpiopinb14
		toggle_gpio(led2);
		//toggle the led on the gpio pinb15
		toggle_gpio(led3);
		// wait for 1 second
		 HAL_Delay(10000);
		 
		 // toggle the led on the gpio pina15
		toggle_gpio(led3);
		//toggle the led on gpio pina14
		toggle_gpio(led2);
		
		HAL_Delay(2000);
		
		// toggle the led on the gpio pinb14
		toggle_gpio(led2);
		
		// toggle the led on the gpio pinI2
		toggle_gpio(led4);
  }
}
