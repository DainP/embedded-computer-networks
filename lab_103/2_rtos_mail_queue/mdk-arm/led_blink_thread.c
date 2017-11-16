/*
 * led_blink_thread.c
 *
 * this is a blinky thread ...
 */
 
// include cmsis_os for the rtos api
#include "cmsis_os.h"


// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// RTOS DEFINES

// declare the thread function prototypes, thread id, and priority
void led_thread(void const *argument);
osThreadId tid_led_thread;
osThreadDef(led_thread, osPriorityNormal, 1, 0);

// leds ...
gpio_pin_t led2 = {PF_6, GPIOF, GPIO_PIN_6};
gpio_pin_t led3 = {PF_7, GPIOF, GPIO_PIN_7};
gpio_pin_t led4 = {PF_8, GPIOF, GPIO_PIN_8};

int init_led_thread(void)
{
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	  
  // create the thread and get its task id
  tid_led_thread = osThreadCreate(osThread(led_thread), NULL);
  
  // check if everything worked ...
  if(!tid_led_thread)
  {
    return(-1);
  }
  return(0);
	
}



void led_thread(void const *argument)
{
	while(1)
	{
		toggle_gpio(led2);
		toggle_gpio(led3);
		toggle_gpio(led4);
		osDelay(100);
	}
	
}