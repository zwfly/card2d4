/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */
#include "app.h"
#include <string.h>
#include <ctype.h>

#include "app_2d4.h"

static uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

uint8_t tmpBuf[8] = { 0 };

//static uint8_t test_vol = 0;
//static uint8_t test_yinxiang_status = 0;

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
#if 1

	RF_RxMode();
#else
	RF_TxMode();
	sendRcv_flag = 1;
#endif

//	RF_Carrier(1);

}

void app_2d4_send(uint8_t *d, uint8_t len) {
//	if (len > PAYLOAD_WIDTH) {
//		return;
//	}
	uint8_t i = 0;
	for (i = 0; i < 10; i++) {
		nop
//		nop
//		nop
//		nop
	}
	RF_TxMode();
	sendRcv_flag = 1;

	for (i = 0; i < 10; i++) {
		nop
//		nop
//		nop
//		nop
	}

	if (sendBuf != d) {
		memset(sendBuf, 0, PAYLOAD_WIDTH);
		memcpy(sendBuf, d, len);
	}
}

static void app_2d4_Rcv(uint8_t *buf) {}

void app_2d4_pro(void) {

	if (sendRcv_flag) {

		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

//			printf("Send OK\r\n");

			sendRcv_flag = 0;
//			RF_RxMode();

//			Relay_toggle();

			break;
		case RX_DR_FLAG:		//发送成功且收到payload

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		case MAX_RT_FLAG:		// 增强型发送超时失败

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		default:		// rf 处于空闲状态才发送数据

			RF_TxData(sendBuf, sizeof(sendBuf));

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, sizeof(rcvBuf))) {
//			app_2d4_Rcv(rcvBuf);
		}
	}
}

