/*
 * app_2d4.h
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_2D4_H_
#define APP_INC_APP_2D4_H_

#define LCD2LAMP_HEADER   0xF2
#define LAMP2LCD_HEADER   0xF8

#define  KEY_MODE_POWER_CMD           0x50
#define  KEY_MODE_POWER_LONG_CMD      0x70
#define  KEY_PREV_VOL_MINUS_CMD       0x51
#define  KEY_PREV_VOL_MINUS_LONG_CMD  0x71
#define  KEY_PLAY_BT_CALL_CMD         0x52
#define  KEY_PLAY_BT_CALL_LONG_CMD    0x72
#define  KEY_NEXT_VOL_ADD_CMD         0x53
#define  KEY_NEXT_VOL_ADD_LONG_CMD    0x73

#define  KEY_POWER_CMD              0x54
#define  KEY_MODE_ADD_CMD           0x55

#define  KEY_SPEED_ADD_CMD          0x56
#define  KEY_DEMO_CMD               0x57
#define  KEY_SPEED_MINUS_CMD        0x58

#define  KEY_COLOR_ADD_CMD          0x59
#define  KEY_MODE_CMD               0x5A
#define  KEY_BRIGHT_ADD_CMD         0x5B

#define  KEY_COLOR_MINUS_CMD        0x5C
#define  KEY_BRIGHT_MINUS_CMD       0x5D

#define  KEY_NUM_1_CMD              0x5E
#define  KEY_NUM_2_CMD              0x5F
#define  KEY_NUM_3_CMD              0x60
#define  KEY_NUM_4_CMD              0x61

#define WIRELESS_MATCH_CODE_CMD  0xFE

extern idata uint8_t sendBuf[PAYLOAD_WIDTH];

void app_2d4_switch_public_address(void);
void app_2d4_switch_saved_address(void);

void app_2d4_init(void);
void app_2d4_send(uint8_t *d, uint8_t len);
void app_2d4_pro(void);

#endif /* APP_INC_APP_2D4_H_ */
