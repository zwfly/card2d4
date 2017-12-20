/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

static uint8_t press_long_lock = 0;

//static idata uint8_t buf[PAYLOAD_WIDTH] = {0};
#if 0
void app_key_init(void) {

}

void app_power_on(void) {
	SW_Reset();  //复位
}
void app_power_off(void) {
//	lcd_bright_off();
	LCD_Clear_All();
}
#endif

static void app_send_key(uint8_t key, uint8_t *index) {
	uint8_t i = 0;
	Repeat_Stop();
	Repeat_SetStart(bsp_led_on);
	Repeat_SetStop(bsp_led_off);
	Repeat_Start(3, 1, 1);

	sendBuf[(*index)++] = LCD2LAMP_HEADER;
	sendBuf[(*index)++] = 0x01;
	sendBuf[(*index)++] = key;
	for (i = 0; i < (sendBuf[1] + 1); i++) {
		sendBuf[*index] += sendBuf[i + 1];
	}
}

void app_key_pro(uint8_t keyCode) {
	uint8_t index = 0;
	uint16_t i = 0;

	if (g_tWork.match_code_mode) {
		return;
	}

	index = 0;
	memset(sendBuf, 0, PAYLOAD_WIDTH);
	switch (keyCode) {
	case KEY_UP_K1:   //mode power
		if (press_long_lock == 0) {
			app_send_key(KEY_MODE_POWER_CMD, &index);
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:   //power long
		press_long_lock = 1;
		app_send_key(KEY_MODE_POWER_LONG_CMD, &index);
		break;
	case KEY_UP_K2:   //prev vol-
		if (press_long_lock == 0) {
			app_send_key(KEY_PREV_VOL_MINUS_CMD, &index);
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K2:
		if (press_long_lock) {
			app_send_key(KEY_PREV_VOL_MINUS_LONG_CMD, &index);
		}
		break;
	case KEY_LONG_K2:
		press_long_lock = 1;
		app_send_key(KEY_PREV_VOL_MINUS_LONG_CMD, &index);
		break;
	case KEY_UP_K3:   // play BT
		if (press_long_lock == 0) {
			app_send_key(KEY_PLAY_BT_CALL_CMD, &index);
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K3:
		break;
	case KEY_LONG_K3:
		press_long_lock = 1;
		app_send_key(KEY_PLAY_BT_CALL_LONG_CMD, &index);
		break;
	case KEY_UP_K4:   // next vol+
		if (press_long_lock == 0) {
			app_send_key(KEY_NEXT_VOL_ADD_CMD, &index);
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K4:
		if (press_long_lock) {
			app_send_key(KEY_NEXT_VOL_ADD_LONG_CMD, &index);
		}
		break;
	case KEY_LONG_K4:
		press_long_lock = 1;
		app_send_key(KEY_NEXT_VOL_ADD_LONG_CMD, &index);
		break;
	case KEY_UP_K5:   //power
		app_send_key(KEY_POWER_CMD, &index);
		break;
	case KEY_DOWN_K5:
		break;
	case KEY_LONG_K5:
		break;
	case KEY_UP_K6:   // NC
		break;
	case KEY_DOWN_K6:
		break;
	case KEY_LONG_K6:
		break;
	case KEY_UP_K7:   // mode+
		break;
	case KEY_DOWN_K7:
		app_send_key(KEY_MODE_ADD_CMD, &index);
		break;
	case KEY_LONG_K7:
		break;
	case KEY_UP_K8:   // NC
		break;
	case KEY_DOWN_K8:
		break;
	case KEY_LONG_K8:
		break;
	case KEY_UP_K9:   // NC
		break;
	case KEY_DOWN_K9:
		break;
	case KEY_LONG_K9:
		break;
	case KEY_UP_K10:   //speed+
		break;
	case KEY_DOWN_K10:
		app_send_key(KEY_SPEED_ADD_CMD, &index);
		break;
	case KEY_LONG_K10:
		break;
	case KEY_UP_K11:   //DEMO
		app_send_key(KEY_DEMO_CMD, &index);
		break;
	case KEY_DOWN_K11:
		break;
	case KEY_LONG_K11:
		break;
	case KEY_UP_K12:   //speed-
		break;
	case KEY_DOWN_K12:
		app_send_key(KEY_SPEED_MINUS_CMD, &index);
		break;
	case KEY_LONG_K12:
		break;
	case KEY_UP_K13:   // NC
		break;
	case KEY_DOWN_K13:
		break;
	case KEY_LONG_K13:
		break;
	case KEY_UP_K14:   // COLOR+
		break;
	case KEY_DOWN_K14:
		app_send_key(KEY_COLOR_ADD_CMD, &index);
		break;
	case KEY_LONG_K14:
		break;
	case KEY_UP_K15:   // MODE-
		break;
	case KEY_DOWN_K15:
		app_send_key(KEY_MODE_CMD, &index);
		break;
	case KEY_LONG_K15:
		break;
	case KEY_UP_K16:   // bright+
		break;
	case KEY_DOWN_K16:
		app_send_key(KEY_BRIGHT_ADD_CMD, &index);
		break;
	case KEY_LONG_K16:
		break;
	case KEY_UP_K17:   // NC
		break;
	case KEY_DOWN_K17:
		break;
	case KEY_LONG_K17:
		break;
	case KEY_UP_K18:   // COLOR-
		break;
	case KEY_DOWN_K18:
		app_send_key(KEY_COLOR_MINUS_CMD, &index);
		break;
	case KEY_LONG_K18:
		break;
	case KEY_UP_K19:   // NC
		break;
	case KEY_DOWN_K19:
		break;
	case KEY_LONG_K19:
		break;
	case KEY_UP_K20:   // bright-
		break;
	case KEY_DOWN_K20:
		app_send_key(KEY_BRIGHT_MINUS_CMD, &index);
		break;
	case KEY_LONG_K20:
		break;
	case KEY_UP_K21:   // num 1
		if (press_long_lock == 0) {
			app_send_key(KEY_NUM_1_CMD, &index);
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K21:
		break;
	case KEY_LONG_K21:
		press_long_lock = 1;
		break;
	case KEY_UP_K22:   // num 2
		app_send_key(KEY_NUM_2_CMD, &index);
		break;
	case KEY_DOWN_K22:
		break;
	case KEY_LONG_K22:
		break;
	case KEY_UP_K23:   // num 3
		app_send_key(KEY_NUM_3_CMD, &index);
		break;
	case KEY_DOWN_K23:
		break;
	case KEY_LONG_K23:
		break;
	case KEY_UP_K24:   // num 4
		app_send_key(KEY_NUM_4_CMD, &index);
		break;
	case KEY_DOWN_K24:
		break;
	case KEY_LONG_K24:
		break;
	case KEY_UP_K21_24:   // num 1 and 4
		break;
	case KEY_DOWN_K21_24:
		break;
	case KEY_LONG_K21_24:
		g_tWork.match_code_mode = 1;

		for (i = 0; i < 1000; i++) {
			nop
		}

		app_2d4_switch_public_address();
		Repeat_Stop();
		Repeat_SetStart(bsp_led_on);
		Repeat_SetStop(bsp_led_off);
		Repeat_Start(1, 5, 0);

		index = 0;
		break;
	default:
		break;
	}
	if (index) {
		index++;
		app_2d4_send(sendBuf, index);
	}

}

