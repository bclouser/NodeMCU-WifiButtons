#include <c_types.h>
#include "osapi.h"
#include "led.h"
#include "math.h"




#define PERIOD 2000 /*us.(2ms)*/  
/* PERIOD * 1000/45 was a hard to find value that maxes out the duty cycle */    
#define MAXDUTY PERIOD * 1000/45

bool ICACHE_FLASH_ATTR setLed(LedNumEnum ledNum, uint8 dutyPercent)
{
	// First verify that duty is within acceptable range
	// For now, we error out, in the future we could clip to min, max
	if( (dutyPercent < 0) || (dutyPercent > 100) ){
		return false;
	}

	os_printf("Setting LED %d\n", ledNum);
	// need to convert percentage to actual duty value

	double decimalPercent = ((double)dutyPercent)/100;
	double actualDuty = decimalPercent * (double)MAXDUTY;

	uint32 dutyToSet = (uint32)actualDuty;
	//os_printf("Actual actualDuty = %.2f\n", actualDuty);
	//os_printf("Actual dutyToSet = %d\n", dutyToSet);
	pwm_set_duty( dutyToSet, (uint8)ledNum );
	pwm_start(); // start must be called after every change
}

void ICACHE_FLASH_ATTR initLeds()
{
	os_printf("Initializing leds\n");

	PIN_FUNC_SELECT(PWM_0_OUT_IO_MUX, PWM_0_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_1_OUT_IO_MUX, PWM_1_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_2_OUT_IO_MUX, PWM_2_OUT_IO_FUNC);
	PIN_FUNC_SELECT(PWM_3_OUT_IO_MUX, PWM_3_OUT_IO_FUNC);

	/* We may want to change this in the future, right now we are only using 2 pins for pwm */
    uint32 io_info[][3] = {   {PWM_0_OUT_IO_MUX,PWM_0_OUT_IO_FUNC,PWM_0_OUT_IO_NUM},
                              {PWM_1_OUT_IO_MUX,PWM_1_OUT_IO_FUNC,PWM_1_OUT_IO_NUM},
                              {PWM_2_OUT_IO_MUX,PWM_2_OUT_IO_FUNC,PWM_2_OUT_IO_NUM},
                              {PWM_3_OUT_IO_MUX,PWM_3_OUT_IO_FUNC,PWM_3_OUT_IO_NUM}
                         };
    
    // Initialize duty cycle for channels 0 and 1 to 0
    uint32 pwm_duty_init[] = {MAXDUTY/2, MAXDUTY};
    pwm_init(PERIOD, pwm_duty_init, 4, io_info);
    pwm_start(); 
}