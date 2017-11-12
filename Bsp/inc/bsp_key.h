/*
 *********************************************************************************************************
 *
 *	模块名称 : 按键驱动模块
 *	文件名称 : bsp_key.h
 *	版    本 : V1.0
 *	说    明 : 头文件
 *
 *********************************************************************************************************
 */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#define KEY_COUNT    24

/* 根据应用程序的功能重命名按键宏 */
#define KEY_DOWN_K1		KEY_1_DOWN
#define KEY_UP_K1		KEY_1_UP
#define KEY_LONG_K1		KEY_1_LONG

#define KEY_DOWN_K2		KEY_2_DOWN
#define KEY_UP_K2		KEY_2_UP
#define KEY_LONG_K2		KEY_2_LONG

#define KEY_DOWN_K3		KEY_3_DOWN
#define KEY_UP_K3		KEY_3_UP
#define KEY_LONG_K3		KEY_3_LONG

#define KEY_DOWN_K4		KEY_4_DOWN
#define KEY_UP_K4		KEY_4_UP
#define KEY_LONG_K4		KEY_4_LONG

#define KEY_DOWN_K5		KEY_5_DOWN
#define KEY_UP_K5		KEY_5_UP
#define KEY_LONG_K5		KEY_5_LONG

#define KEY_DOWN_K6		KEY_6_DOWN
#define KEY_UP_K6		KEY_6_UP
#define KEY_LONG_K6		KEY_6_LONG

#define KEY_DOWN_K7		KEY_7_DOWN
#define KEY_UP_K7		KEY_7_UP
#define KEY_LONG_K7		KEY_7_LONG

#define KEY_DOWN_K8		KEY_8_DOWN
#define KEY_UP_K8		KEY_8_UP
#define KEY_LONG_K8		KEY_8_LONG

#define KEY_DOWN_K9		KEY_9_DOWN
#define KEY_UP_K9		KEY_9_UP
#define KEY_LONG_K9		KEY_9_LONG

#define KEY_DOWN_K10	KEY_10_DOWN
#define KEY_UP_K10		KEY_10_UP
#define KEY_LONG_K10	KEY_10_LONG

#define KEY_DOWN_K11	KEY_11_DOWN
#define KEY_UP_K11		KEY_11_UP
#define KEY_LONG_K11	KEY_11_LONG

#define KEY_DOWN_K12	KEY_12_DOWN
#define KEY_UP_K12		KEY_12_UP
#define KEY_LONG_K12	KEY_12_LONG

#define KEY_DOWN_K13	KEY_13_DOWN
#define KEY_UP_K13		KEY_13_UP
#define KEY_LONG_K13	KEY_13_LONG

#define KEY_DOWN_K14	KEY_14_DOWN
#define KEY_UP_K14		KEY_14_UP
#define KEY_LONG_K14	KEY_14_LONG

#define KEY_DOWN_K15	KEY_15_DOWN
#define KEY_UP_K15		KEY_15_UP
#define KEY_LONG_K15	KEY_15_LONG

#define KEY_DOWN_K16	KEY_16_DOWN
#define KEY_UP_K16		KEY_16_UP
#define KEY_LONG_K16	KEY_16_LONG

#define KEY_DOWN_K17	KEY_17_DOWN
#define KEY_UP_K17		KEY_17_UP
#define KEY_LONG_K17	KEY_17_LONG

#define KEY_DOWN_K18	KEY_18_DOWN
#define KEY_UP_K18		KEY_18_UP
#define KEY_LONG_K18	KEY_18_LONG

#define KEY_DOWN_K19	KEY_19_DOWN
#define KEY_UP_K19		KEY_19_UP
#define KEY_LONG_K19	KEY_19_LONG

#define KEY_DOWN_K20	KEY_20_DOWN
#define KEY_UP_K20		KEY_20_UP
#define KEY_LONG_K20	KEY_20_LONG

#define KEY_DOWN_K21	KEY_21_DOWN
#define KEY_UP_K21		KEY_21_UP
#define KEY_LONG_K21	KEY_21_LONG

#define KEY_DOWN_K22	KEY_22_DOWN
#define KEY_UP_K22		KEY_22_UP
#define KEY_LONG_K22	KEY_22_LONG

#define KEY_DOWN_K23	KEY_23_DOWN
#define KEY_UP_K23		KEY_23_UP
#define KEY_LONG_K23	KEY_23_LONG

#define KEY_DOWN_K24	KEY_24_DOWN
#define KEY_UP_K24		KEY_24_UP
#define KEY_LONG_K24	KEY_24_LONG

/* 按键ID, 主要用于bsp_KeyState()函数的入口参数 */
typedef enum {
	KID_K1 = 0,
	KID_K2,
	KID_K3,
	KID_K4,
	KID_K5,
	KID_K6,
	KID_K7,
	KID_K8,
	KID_K9,
	KID_K10,
	KID_K11,
	KID_K12,
	KID_K13,
	KID_K14,
	KID_K15,
	KID_K16,
	KID_K17,
	KID_K18,
	KID_K19,
	KID_K20,
	KID_K21,
	KID_K22,
	KID_K23,
	KID_K24,
} KEY_ID_E;

/*
 按键滤波时间50ms, 单位10ms。
 只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
 即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
 */
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     200			/* 单位10ms， 持续1秒，认为长按事件 */

/*
 每个按键对应1个全局的结构体变量。
 */
typedef struct {
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

	uint8_t Count; /* 滤波器计数器 */
	uint16_t LongCount; /* 长按计数器 */
	uint16_t LongTime; /* 按键按下持续时间, 0表示不检测长按 */
	uint8_t State; /* 按键当前状态（按下还是弹起） */
	uint8_t RepeatSpeed; /* 连续按键周期 */
	uint8_t RepeatCount; /* 连续按键计数器 */
} KEY_T;

/*
 定义键值代码, 必须按如下次序定时每个键的按下、弹起和长按事件

 推荐使用enum, 不用#define，原因：
 (1) 便于新增键值,方便调整顺序，使代码看起来舒服点
 (2) 编译器可帮我们避免键值重复。
 */
typedef enum {
	KEY_NONE = 0, /* 0 表示按键事件 */

	KEY_1_DOWN, /* 1键按下 */
	KEY_1_UP, /* 1键弹起 */
	KEY_1_LONG, /* 1键长按 */

	KEY_2_DOWN, /* 2键按下 */
	KEY_2_UP, /* 2键弹起 */
	KEY_2_LONG, /* 2键长按 */

	KEY_3_DOWN, /* 3键按下 */
	KEY_3_UP, /* 3键弹起 */
	KEY_3_LONG, /* 3键长按 */

	KEY_4_DOWN, /* 4键按下 */
	KEY_4_UP, /* 4键弹起 */
	KEY_4_LONG, /* 4键长按 */

	KEY_5_DOWN, /* 5键按下 */
	KEY_5_UP, /* 5键弹起 */
	KEY_5_LONG, /* 5键长按 */

	KEY_6_DOWN, /* 6键按下 */
	KEY_6_UP, /* 6键弹起 */
	KEY_6_LONG, /* 6键长按 */

	KEY_7_DOWN, /* 7键按下 */
	KEY_7_UP, /* 7键弹起 */
	KEY_7_LONG, /* 7键长按 */

	KEY_8_DOWN, /* 8键按下 */
	KEY_8_UP, /* 8键弹起 */
	KEY_8_LONG, /* 8键长按 */

	KEY_9_DOWN, /* 9键按下 */
	KEY_9_UP, /* 9键弹起 */
	KEY_9_LONG, /* 9键长按 */

	KEY_10_DOWN, /* 9键按下 */
	KEY_10_UP, /* 9键弹起 */
	KEY_10_LONG, /* 9键长按 */

	KEY_11_DOWN, /* 9键按下 */
	KEY_11_UP, /* 9键弹起 */
	KEY_11_LONG, /* 9键长按 */

	KEY_12_DOWN, /* 9键按下 */
	KEY_12_UP, /* 9键弹起 */
	KEY_12_LONG, /* 9键长按 */

	KEY_13_DOWN, /* 9键按下 */
	KEY_13_UP, /* 9键弹起 */
	KEY_13_LONG, /* 9键长按 */

	KEY_14_DOWN, /* 9键按下 */
	KEY_14_UP, /* 9键弹起 */
	KEY_14_LONG, /* 9键长按 */

	KEY_15_DOWN, /* 9键按下 */
	KEY_15_UP, /* 9键弹起 */
	KEY_15_LONG, /* 9键长按 */

	KEY_16_DOWN, /* 9键按下 */
	KEY_16_UP, /* 9键弹起 */
	KEY_16_LONG, /* 9键长按 */

	KEY_17_DOWN, /* 9键按下 */
	KEY_17_UP, /* 9键弹起 */
	KEY_17_LONG, /* 9键长按 */

	KEY_18_DOWN, /* 9键按下 */
	KEY_18_UP, /* 9键弹起 */
	KEY_18_LONG, /* 9键长按 */

	KEY_19_DOWN, /* 9键按下 */
	KEY_19_UP, /* 9键弹起 */
	KEY_19_LONG, /* 9键长按 */

	KEY_20_DOWN, /* 9键按下 */
	KEY_20_UP, /* 9键弹起 */
	KEY_20_LONG, /* 9键长按 */

	KEY_21_DOWN, /* 9键按下 */
	KEY_21_UP, /* 9键弹起 */
	KEY_21_LONG, /* 9键长按 */

	KEY_22_DOWN, /* 9键按下 */
	KEY_22_UP, /* 9键弹起 */
	KEY_22_LONG, /* 9键长按 */

	KEY_23_DOWN, /* 9键按下 */
	KEY_23_UP, /* 9键弹起 */
	KEY_23_LONG, /* 9键长按 */

	KEY_24_DOWN, /* 9键按下 */
	KEY_24_UP, /* 9键弹起 */
	KEY_24_LONG, /* 9键长按 */

} KEY_ENUM;

/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE	10
typedef struct {
	uint8_t Buf[KEY_FIFO_SIZE]; /* 键值缓冲区 */
	uint8_t Read; /* 缓冲区读指针1 */
	uint8_t Write; /* 缓冲区写指针 */
	uint8_t Read2; /* 缓冲区读指针2 */
} KEY_FIFO_T;

/* 供外部调用的函数声明 */
void bsp_InitKey(void);
void bsp_KeyScan(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed);
void bsp_ClearKey(void);

#endif

/*****************************(END OF FILE) *********************************/
