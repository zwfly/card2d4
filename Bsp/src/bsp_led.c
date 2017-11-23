/*
 * bsp_led.c
 *
 *  Created on: 2017Äê11ÔÂ13ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include <string.h>

void bsp_led_init(void) {
	clr_P3M1_0;
	set_P3M2_0;
	bsp_led_off();
}

void bsp_led_on(void) {
	P30 = 1;
}
void bsp_led_off(void) {
	P30 = 0;
}
void bsp_led_set(uint8_t s) {
	if (s) {
		bsp_led_on();
	} else {
		bsp_led_off();
	}
}
