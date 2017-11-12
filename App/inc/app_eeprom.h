/*
 * app_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_EEPROM_H_
#define APP_INC_APP_EEPROM_H_



void app_eeprom_Init(void);
void app_eeprom_get_dome_with_index(DOME_DEFAULT_T* dd, uint8_t index);
void app_eeprom_write_byte(uint16_t addr, uint8_t d);

#endif /* APP_INC_APP_EEPROM_H_ */
