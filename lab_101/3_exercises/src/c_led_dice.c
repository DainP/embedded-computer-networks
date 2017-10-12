/*
 * c_traffic_lights.c
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
#include "random_numbers.h"

// map the led to GPIO pins
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t led4 = {PI_2, GPIOI, GPIO_PIN_2};
gpio_pin_t led5 = {PA_15, GPIOA, GPIO_PIN_15};
gpio_pin_t led6 = {PA_8, GPIOA, GPIO_PIN_8};
gpio_pin_t led7 = {PB_8, GPIOB, GPIO_PIN_8};

gpio_pin_t pb = {PB_9, GPIOB, GPIO_PIN_9}; 

uint32_t rnd;

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_gpio(pb,INPUT);
	
	init_random();
  
  // initialise the gpio pins
  init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	init_gpio(led5, OUTPUT);
	init_gpio(led6, OUTPUT);
	init_gpio(led7, OUTPUT);
	
  
  // loop forever ...
  while(1)
  {
    // toggle the led on the gpio pin
   if (read_gpio(pb))
	 {
		 rnd = (get_random_int() % 6) + 1;
	 }
	 
	 
	if (rnd == 1)
	 {
 
		write_gpio(led1, LOW);
		write_gpio(led2, LOW);
		write_gpio(led3, LOW); 
		write_gpio(led4, LOW); 
		write_gpio(led5, LOW); 
		write_gpio(led6, LOW); 
		write_gpio(led7, HIGH);
	 }
	 
	 if (rnd == 2)
	 {
 
		write_gpio(led1, HIGH);
		write_gpio(led2, LOW);
		write_gpio(led3, LOW); 
		write_gpio(led4, LOW); 
		write_gpio(led5, LOW); 
		write_gpio(led6, HIGH); 
		write_gpio(led7, LOW);
	 }
	 
	 if (rnd == 3)
	 {
 
		write_gpio(led1, HIGH);
		write_gpio(led2, LOW);
		write_gpio(led3, LOW); 
		write_gpio(led4, LOW); 
		write_gpio(led5, LOW); 
		write_gpio(led6, HIGH); 
		write_gpio(led7, HIGH);
	 }
	 
	 if (rnd == 4)
	 {
 
		write_gpio(led1, HIGH);
		write_gpio(led2, LOW);
		write_gpio(led3, HIGH); 
		write_gpio(led4, HIGH); 
		write_gpio(led5, LOW); 
		write_gpio(led6, HIGH); 
		write_gpio(led7, LOW);
	 }
	 
	 if (rnd == 5)
	 {
 
		write_gpio(led1, HIGH);
		write_gpio(led2, LOW);
		write_gpio(led3, HIGH); 
		write_gpio(led4, HIGH); 
		write_gpio(led5, LOW); 
		write_gpio(led6, HIGH); 
		write_gpio(led7, HIGH);
	 }
	 
	 if (rnd == 6)
	 {
 
		write_gpio(led1, HIGH);
		write_gpio(led2, HIGH);
		write_gpio(led3, HIGH); 
		write_gpio(led4, HIGH); 
		write_gpio(led5, HIGH); 
		write_gpio(led6, HIGH); 
		write_gpio(led7, LOW);
	 }
	 
	 	
    // wait for 1 second
    HAL_Delay(1000);
  }
}
