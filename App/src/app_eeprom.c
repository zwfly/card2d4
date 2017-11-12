/*
 * app_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "app.h"
#include <string.h>

#define DOME_START_ADDR   0x3C00  //use 3KB

void app_eeprom_Init(void) {

}

void app_eeprom_get_dome_with_index(DOME_DEFAULT_T *dd, uint8_t index) {
	uint8_t i = 0;
	uint8_t n = 0;
	n = index;

	if (n >= DEFAULT_DOME_NUM) {
		n = 0;
	}
	for (i = 0; i < sizeof(DOME_DEFAULT_T); i++) {
		*((uint8_t*) dd + i) =
				read_APROM_BYTE(
		DOME_START_ADDR + index * sizeof(DOME_DEFAULT_T) + i);
	}
}

void app_eeprom_write_byte(uint16_t addr, uint8_t d) {
	write_DATAFLASH_BYTE(DOME_START_ADDR + addr, d);
}

void app_eeprom_100ms_pro(void) {

}

static void app_eeprom_pro(void) {

}
