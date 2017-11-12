/*
 *********************************************************************************************************
 *
 *	模块名称 : 独立按键驱动模块
 *	文件名称 : bsp_key.c
 *	版    本 : V1.0
 *	说    明 : 扫描独立按键，具有软件滤波机制，具有按键FIFO。可以检测如下事件：
 *				(1) 按键按下
 *				(2) 按键弹起
 *				(3) 长按键
 *				(4) 长按时自动连发
 *
 *********************************************************************************************************
 */

#include "bsp.h"
#include <string.h>

#if 0
static idata KEY_T s_tBtn[KEY_COUNT];
static idata KEY_FIFO_T s_tKey; /* 按键FIFO变量,结构体 */
#else
static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey; /* 按键FIFO变量,结构体 */
#endif

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

/*
 *********************************************************************************************************
 *	函 数 名: IsKeyDownX
 *	功能说明: 判断按键是否按下
 *	形    参: 无
 *	返 回 值: 返回值1 表示按下，0表示未按下
 *********************************************************************************************************
 */

static uint8_t IsKeyDown(uint8_t line, uint8_t column) {
	uint8_t ret = 0;

	switch (line) {
	case 0:
		P02 = 0;
		P03 = 1;
		P04 = 1;
		P05 = 1;
		P06 = 1;
		P07 = 1;

		P14 = 1;
		P15 = 1;
		P16 = 1;
		P17 = 1;
		switch (column) {
		case 0:
			ret = ~P17;
			break;
		case 1:
			ret = ~P16;
			break;
		case 2:
			ret = ~P15;
			break;
		case 3:
			ret = ~P14;
			break;
		default:
			break;
		}
		break;
	case 1:
		P02 = 1;
		P03 = 0;
		P04 = 1;
		P05 = 1;
		P06 = 1;
		P07 = 1;

		P14 = 1;
		P15 = 1;
		P16 = 1;
		P17 = 1;
		switch (column) {
		case 0:
			ret = ~P17;
			break;
		case 1:
			ret = ~P16;
			break;
		case 2:
			ret = ~P15;
			break;
		case 3:
			ret = ~P14;
			break;
		default:
			break;
		}
		break;
	case 2:
		P02 = 1;
		P03 = 1;
		P04 = 0;
		P05 = 1;
		P06 = 1;
		P07 = 1;

		P14 = 1;
		P15 = 1;
		P16 = 1;
		P17 = 1;
		switch (column) {
		case 0:
			ret = ~P17;
			break;
		case 1:
			ret = ~P16;
			break;
		case 2:
			ret = ~P15;
			break;
		case 3:
			ret = ~P14;
			break;
		default:
			break;
		}
		break;
	case 3:
		P02 = 1;
		P03 = 1;
		P04 = 1;
		P05 = 0;
		P06 = 1;
		P07 = 1;

		P14 = 1;
		P15 = 1;
		P16 = 1;
		P17 = 1;
		switch (column) {
		case 0:
			ret = ~P17;
			break;
		case 1:
			ret = ~P16;
			break;
		case 2:
			ret = ~P15;
			break;
		case 3:
			ret = ~P14;
			break;
		default:
			break;
		}
		break;
	case 4:
		P02 = 1;
		P03 = 1;
		P04 = 1;
		P05 = 1;
		P06 = 0;
		P07 = 1;

		P14 = 1;
		P15 = 1;
		P16 = 1;
		P17 = 1;
		switch (column) {
		case 0:
			ret = ~P17;
			break;
		case 1:
			ret = ~P16;
			break;
		case 2:
			ret = ~P15;
			break;
		case 3:
			ret = ~P14;
			break;
		default:
			break;
		}
		break;
	}

	return 0;
}

static uint8_t IsKeyDown1(void) {
	return IsKeyDown(0, 0);
}

static uint8_t IsKeyDown2(void) {

	return IsKeyDown(0, 1);
}

static uint8_t IsKeyDown3(void) {
	return IsKeyDown(0, 2);
}
//CH1, S4 ad = 884
static uint8_t IsKeyDown4(void) {
	return IsKeyDown(0, 3);
}

static uint8_t IsKeyDown5(void) {

	return IsKeyDown(1, 0);
}

static uint8_t IsKeyDown6(void) {
	return IsKeyDown(1, 1);
}

static uint8_t IsKeyDown7(void) {
	return IsKeyDown(1, 2);
}

static uint8_t IsKeyDown8(void) {
	return IsKeyDown(1, 3);
}

static uint8_t IsKeyDown9(void) {
	return IsKeyDown(2, 0);
}

static uint8_t IsKeyDown10(void) {
	return IsKeyDown(2, 1);
}
static uint8_t IsKeyDown11(void) {
	return IsKeyDown(2, 2);
}
static uint8_t IsKeyDown12(void) {
	return IsKeyDown(2, 3);
}
static uint8_t IsKeyDown13(void) {
	return IsKeyDown(3, 0);
}
static uint8_t IsKeyDown14(void) {
	return IsKeyDown(3, 1);
}
static uint8_t IsKeyDown15(void) {
	return IsKeyDown(3, 2);
}
static uint8_t IsKeyDown16(void) {
	return IsKeyDown(3, 3);
}
static uint8_t IsKeyDown17(void) {
	return IsKeyDown(4, 0);
}
static uint8_t IsKeyDown18(void) {
	return IsKeyDown(4, 1);
}
static uint8_t IsKeyDown19(void) {
	return IsKeyDown(4, 2);
}
static uint8_t IsKeyDown20(void) {
	return IsKeyDown(4, 3);
}
static uint8_t IsKeyDown21(void) {
	return IsKeyDown(5, 0);
}
static uint8_t IsKeyDown22(void) {
	return IsKeyDown(5, 1);
}
static uint8_t IsKeyDown23(void) {
	return IsKeyDown(5, 2);
}
static uint8_t IsKeyDown24(void) {
	return IsKeyDown(5, 3);
}
/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKey
 *	功能说明: 初始化按键. 该函数被 bsp_Init() 调用。
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_InitKey(void) {
	bsp_InitKeyVar(); /* 初始化按键变量 */
	bsp_InitKeyHard(); /* 初始化按键硬件 */
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_PutKey
 *	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
 *	形    参:  _KeyCode : 按键代码
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_PutKey(uint8_t _KeyCode) {
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write >= KEY_FIFO_SIZE) {
		s_tKey.Write = 0;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKey
 *	功能说明: 从按键FIFO缓冲区读取一个键值。
 *	形    参:  无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
uint8_t bsp_GetKey(void) {
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write) {
		return KEY_NONE;
	} else {
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE) {
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKey2
 *	功能说明: 从按键FIFO缓冲区读取一个键值。独立的读指针。
 *	形    参:  无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
uint8_t bsp_GetKey2(void) {
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write) {
		return KEY_NONE;
	} else {
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE) {
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKeyState
 *	功能说明: 读取按键的状态
 *	形    参:  _ucKeyID : 按键ID，从0开始
 *	返 回 值: 1 表示按下， 0 表示未按下
 *********************************************************************************************************
 */
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID) {
	return s_tBtn[_ucKeyID].State;
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_SetKeyParam
 *	功能说明: 设置按键参数
 *	形    参：_ucKeyID : 按键ID，从0开始
 *			_LongTime : 长按事件时间
 *			 _RepeatSpeed : 连发速度
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed) {
	s_tBtn[_ucKeyID].LongTime = _LongTime; /* 长按时间 0 表示不检测长按键事件 */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed; /* 按键连发的速度，0表示不支持连发 */
	s_tBtn[_ucKeyID].RepeatCount = 0; /* 连发计数器 */
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_ClearKey
 *	功能说明: 清空按键FIFO缓冲区
 *	形    参：无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
void bsp_ClearKey(void) {
	s_tKey.Read = s_tKey.Write;
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKeyHard
 *	功能说明: 配置按键对应的GPIO
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
static void bsp_InitKeyHard(void) {
	clr_P0M1_2;
	clr_P0M2_2;

	clr_P0M1_3;
	clr_P0M2_3;

	clr_P0M1_4;
	clr_P0M2_4;

	clr_P0M1_5;
	clr_P0M2_5;

	clr_P0M1_6;
	clr_P0M2_6;

	clr_P0M1_7;
	clr_P0M2_7;

	clr_P1M1_4;
	P1M2 &= ~0x10;

	clr_P1M1_5;
	P1M2 &= ~0x20;

	clr_P1M1_6;
	P1M2 &= ~0x40;

	clr_P1M1_7;
	P1M2 &= ~0x80;
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKeyVar
 *	功能说明: 初始化按键变量
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
static void bsp_InitKeyVar(void) {
	uint8_t i = 0;

	memset((uint8_t *) &s_tBtn, 0, sizeof(s_tBtn));

	/* 对按键FIFO读写指针清零 */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* 给每个按键结构体成员变量赋一组缺省值 */
	for (i = 0; i < KEY_COUNT; i++) {
		s_tBtn[i].LongTime = KEY_LONG_TIME; /* 长按时间 0 表示不检测长按键事件 */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2; /* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0; /* 按键缺省状态，0为未按下 */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;				/* 按键按下的键值代码 */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;				/* 按键弹起的键值代码 */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;				/* 按键被持续按下的键值代码 */
		s_tBtn[i].RepeatSpeed = 0; /* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0; /* 连发计数器 */
	}

//	s_tBtn[3].RepeatSpeed = 50; /* 按键连发的速度，0表示不支持连发 */
//	s_tBtn[4].RepeatSpeed = 50; /* 按键连发的速度，0表示不支持连发 */

	/* 判断按键按下的函数 */
	i = 0;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown1;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown2;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown3;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown4;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown5;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown6;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown7;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown8;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown9;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown10;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown11;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown12;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown13;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown14;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown15;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown16;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown17;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown18;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown19;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown20;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown21;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown22;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown23;
	s_tBtn[i++].IsKeyDownFunc = IsKeyDown24;

}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_DetectKey
 *	功能说明: 检测一个按键。非阻塞状态，必须被周期性的调用。
 *	形    参:  按键结构变量指针
 *	返 回 值: 无
 *********************************************************************************************************
 */
KEY_T *pBtn;
static void bsp_DetectKey(uint8_t i) {
	pBtn = &s_tBtn[i];
	if (pBtn->IsKeyDownFunc()) {
		if (pBtn->Count < KEY_FILTER_TIME) {
			pBtn->Count = KEY_FILTER_TIME;
		} else if (pBtn->Count < 2 * KEY_FILTER_TIME) {
			pBtn->Count++;
		} else {
			if (pBtn->State == 0) {
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				bsp_PutKey((uint8_t) (3 * i + 1));
			}

			if (pBtn->LongTime > 0) {
				if (pBtn->LongCount < pBtn->LongTime) {
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime) {
						/* 键值放入按键FIFO */
						bsp_PutKey((uint8_t) (3 * i + 3));
					}
				} else {
					if (pBtn->RepeatSpeed > 0) {
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
							pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
							bsp_PutKey((uint8_t) (3 * i + 1));
						}
					}
				}
			}
		}
	} else {
		if (pBtn->Count > KEY_FILTER_TIME) {
			pBtn->Count = KEY_FILTER_TIME;
		} else if (pBtn->Count != 0) {
			pBtn->Count--;
		} else {
			if (pBtn->State == 1) {
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				bsp_PutKey((uint8_t) (3 * i + 2));
			}
		}
		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_KeyScan
 *	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_KeyScan(void) {
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++) {
		bsp_DetectKey(i);
	}
}

/***************************** (END OF FILE) *********************************/
