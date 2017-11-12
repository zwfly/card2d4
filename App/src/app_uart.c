/*
 * app_uart.c
 *
 *  Created on: 2017年8月31日
 *      Author: fly
 */

#include "app.h"
#include <string.h>

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06

static uint8_t index = 0;
static uint8_t len = 0;
static uint8_t i = 0;

static uint8_t uart_sendBuf[16] = { 0 };

void app_uart_Init(void) {
	index = 0;
	len = 0;
	i = 0;
}

void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len) {
	index = 0;

	uart_sendBuf[index++] = 0x55;
	uart_sendBuf[index++] = 0xAA;
	uart_sendBuf[index++] = len + 1;
	uart_sendBuf[index++] = cmd;
	for (i = 0; i < len; i++) {
		uart_sendBuf[index++] = *(ptr + i);
	}
	uart_sendBuf[index++] = app_CalcCRC8(uart_sendBuf, len + 4);

	for (i = 0; i < (len + 5); i++) {
		Send_Data_To_UART0(uart_sendBuf[i]);
	}
}

void app_uart_pro(void) {
	while (riflag) {
		riflag--;
		if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE >= 4) {
			if (((rcv_T.rxBuf[rcv_T.pRead]) == 0x55)
					&& ((rcv_T.rxBuf[(rcv_T.pRead + 1) % RCV_BUFSIZE]) == 0xAA)) {
				len = rcv_T.rxBuf[(rcv_T.pRead + 2) % RCV_BUFSIZE];
				if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE
						>= (len + 4)) {
					if (rcv_T.rxBuf[(rcv_T.pRead + len + 3) % RCV_BUFSIZE]
							!= app_CalcCRC8_cycle(rcv_T.rxBuf + rcv_T.pRead,
									len + 3, rcv_T.pRead, RCV_BUFSIZE)) {
						rcv_T.pRead++;
					} else {
						index = 0;
						memset(sendBuf, 0, PAYLOAD_WIDTH);
						switch (rcv_T.rxBuf[(rcv_T.pRead + 3) % RCV_BUFSIZE]) {
						case BLINK_METHOD_CMD:  //闪法
						{
							uint8_t index = 0;
							index =
									rcv_T.rxBuf[(rcv_T.pRead + 12) % RCV_BUFSIZE];

							if (index >= (DEFAULT_DOME_NUM - 1)) {
								break;
							}

							for (i = 0; i < (DEFAULT_DOME_NUM - 1 - index);
									i++) {
								app_eeprom_write_byte(
										index * sizeof(DOME_DEFAULT_T)
												+ (&dome_blink.header.index
														- &dome_blink), 0);
							}
							for (i = 0; i < sizeof(DOME_DEFAULT_T); i++) {
								app_eeprom_write_byte(
										index * sizeof(DOME_DEFAULT_T) + i,
										rcv_T.rxBuf[(rcv_T.pRead + 4 + i)
												% RCV_BUFSIZE]);
							}
							app_uart_send(BLINK_METHOD_CMD, &index, 1);
						}
							break;
						case RCV_VOL_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_VOL_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_POWER_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_POWER_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#if 0
							case RCV_X_BOX_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_X_BOX_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#endif
						case RCV_BT_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_BT_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case RCV_PREV_NEXT_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PREV_NEXT_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_USB_PLAY_TIME_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_USB_PLAY_TIME_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case RCV_FM_HZ_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_FM_HZ_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case MODE_CHANGE_CMD:   //MODE
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = MODE_CHANGE_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PLAY_PAUSE_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PLAY_PAUSE_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
							/// app --start
						case APP_COLOR_ATLA_CMD:
#if 1
							app_dome_rgb(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 5) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 6) % RCV_BUFSIZE]);
#else
							app_dome_rgb(0xFFFF, 0xFFFF, 0xFFFF);
#endif
							break;
						case APP_BRIGHT_CMD:
							dome_running_param.bright = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							Light_bright_set(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]);
							break;
						case APP_SPEED_CMD:
							dome_running_param.speed = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							break;
						case APP_FLASH_INDEX_CMD:
							app_dome_start(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]);
							break;
							/// app --end
						default:
							break;
						}
						rcv_T.pRead += len + 4;
#if 1
						rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
//						break;
						return;
#endif
					}
				}
			} else {
				rcv_T.pRead++;
			}
			rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
		}
	}

}
