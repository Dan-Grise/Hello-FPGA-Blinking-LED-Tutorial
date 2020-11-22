#include <stdio.h>
#include <unistd.h>
#include "drivers/mss_sys_services/mss_sys_services.h"
#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_gpio/mss_gpio.h"
#include "drivers/mss_timer/mss_timer.h"

//Function Declarations
void timer_delay(uint32_t load_value);

/*==============================================================================
 Main function.
*/
int main(){
	uint32_t load_value= 100000000;
	//initialize GPIO and timer
	MSS_GPIO_init();
	MSS_TIM1_init(MSS_TIMER_ONE_SHOT_MODE);
	while(1){
		//set GPIO high
		MSS_GPIO_set_output(MSS_GPIO_0, MSS_GPIO_DRIVE_LOW);
		//delay
		timer_delay(load_value);
		//set GPIO low
		MSS_GPIO_set_output(MSS_GPIO_0, MSS_GPIO_DRIVE_HIGH);
		timer_delay(load_value);
		//delay
	};
	return 0;
}
void timer_delay(uint32_t load_value){
	MSS_TIM1_load_immediate(load_value);
	MSS_TIM1_start();
	while (MSS_TIM1_get_current_value()); //while counter has not reached 0
}
