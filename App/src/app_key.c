/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

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

void app_key_pro(uint8_t keyCode) {
	uint8_t index = 0;
	uint8_t i = 0;

	index = 0;
	memset(sendBuf, 0, PAYLOAD_WIDTH);
	switch (keyCode) {
	case KEY_UP_K1:   // power short
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:   //power long

		break;
	case KEY_UP_K2:   //play/pause
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K2:

		break;
	case KEY_LONG_K2:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K3:   // down
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K3:

		break;
	case KEY_LONG_K3:

		break;
	case KEY_UP_K4:   // up
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K4:  // 连发

		break;
	case KEY_LONG_K4:

		break;
	case KEY_UP_K5:   //vol+
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K5:

		break;
	case KEY_LONG_K5:

		break;
	case KEY_UP_K6:   //ACC  继电器
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = 0;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K6:

		break;
	case KEY_LONG_K6:

		break;
	case KEY_UP_K7:   // vol-
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K7:

		break;
	case KEY_LONG_K7:

		break;
	case KEY_UP_K8:   // mode
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_MODE_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K8:

		break;
	case KEY_LONG_K8:

		break;
	case KEY_UP_K9:   // dome
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = 0;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K9:

		break;
	case KEY_LONG_K9:

		break;
	case KEY_UP_K10:   //

		break;
	case KEY_DOWN_K10:

		break;
	case KEY_LONG_K10:

		break;
	case KEY_UP_K11:   //

		break;
	case KEY_DOWN_K11:

		break;
	case KEY_LONG_K11:

		break;
	case KEY_UP_K12:   //

		break;
	case KEY_DOWN_K12:

		break;
	case KEY_LONG_K12:

		break;
	case KEY_UP_K13:   //

		break;
	case KEY_DOWN_K13:

		break;
	case KEY_LONG_K13:

		break;
	case KEY_UP_K14:   //

		break;
	case KEY_DOWN_K14:

		break;
	case KEY_LONG_K14:

		break;
	case KEY_UP_K15:   //

		break;
	case KEY_DOWN_K15:

		break;
	case KEY_LONG_K15:

		break;
	case KEY_UP_K16:   //

		break;
	case KEY_DOWN_K16:

		break;
	case KEY_LONG_K16:

		break;
	case KEY_UP_K17:   //

		break;
	case KEY_DOWN_K17:

		break;
	case KEY_LONG_K17:

		break;
	case KEY_UP_K18:   //

		break;
	case KEY_DOWN_K18:

		break;
	case KEY_LONG_K18:

		break;
	case KEY_UP_K19:   //

		break;
	case KEY_DOWN_K19:

		break;
	case KEY_LONG_K19:

		break;
	case KEY_UP_K20:   //

		break;
	case KEY_DOWN_K20:

		break;
	case KEY_LONG_K20:

		break;
	case KEY_UP_K21:   //

		break;
	case KEY_DOWN_K21:

		break;
	case KEY_LONG_K21:

		break;
	case KEY_UP_K22:   //

		break;
	case KEY_DOWN_K22:

		break;
	case KEY_LONG_K22:

		break;
	case KEY_UP_K23:   //

		break;
	case KEY_DOWN_K23:

		break;
	case KEY_LONG_K23:

		break;
	case KEY_UP_K24:   //

		break;
	case KEY_DOWN_K24:

		break;
	case KEY_LONG_K24:

		break;
	default:

		break;
	}
	if (index) {
		index++;
		app_2d4_send(sendBuf, index);
	}

}

