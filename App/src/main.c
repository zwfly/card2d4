#include "app.h"

//static uint8_t dome_cnt = 0;

static uint8_t wireless_init_flag = 0;

static void into_powerDown(void) {
	uint16_t i = 0;

	set_P1M1_2;
	P1M2 &= ~SET_BIT2;
	P12 = 1;
	for (i = 0; i < 200; i++) {
		nop
	}

	set_P0M1_0;
	clr_P0M2_0;
	P00 = 0;

	set_P1M1_0;
	clr_P1M2_0;
	P10 = 0;

#if 1
	set_P1M1_1;
	clr_P1M2_1;
	P11 = 0;  //CSN
#endif

	P02 = 0;
	P03 = 0;
	P04 = 0;
	P05 = 0;
	P06 = 0;
	P07 = 0;

	P14 = 1;
	P15 = 1;
	P16 = 1;
	P17 = 1;

	Enable_INT_Port1

	//	Enable_BIT2_FallEdge_Trig
	//	;
	//	Enable_BIT3_FallEdge_Trig
	//	;
	Enable_BIT4_FallEdge_Trig
	;
	Enable_BIT5_FallEdge_Trig
	;
	Enable_BIT6_FallEdge_Trig
	;
	Enable_BIT7_FallEdge_Trig
	;

	set_EPI;				// Enable pin interrupt

	set_PD;

	SW_Reset();  //¸´Î»

//				clr_EPI;
//				PINEN = 0;
//				PIPEN = 0;
//				PICON = 0x00;

//	P12 = 0;
}

static void pd_init(void) {
	clr_P1M1_2;
//	set_P1M2_2;
	P1M2 |= SET_BIT2;

	P12 = 0;

}
uint16_t i = 0;
void main(void) {
	uint8_t PD_cnt = 0;
	uint8_t ucKeyCode;
	wireless_init_flag = 0;
	/****************/
	pd_init();
	for (i = 0; i < 500; i++) {
		nop
		nop
	}

	bsp_Init();

	/****************/
	app_eeprom_Init();
//	app_2d4_init();
//	app_work_Init();
//	app_uart_Init();
//	app_dome_Init();
#if 0
	Enable_INT_Port1

//	Enable_BIT2_FallEdge_Trig
//	;
//	Enable_BIT3_FallEdge_Trig
//	;
	Enable_BIT4_FallEdge_Trig
	;
	Enable_BIT5_FallEdge_Trig
	;
	Enable_BIT6_FallEdge_Trig
	;
	Enable_BIT7_FallEdge_Trig
	;

	set_EPI;// Enable pin interrupt
//	set_EX1;
#endif
	set_EA;

	/****************/
//	Show_FW_Version_Number_To_PC();
	while (1) {

		if (Task_time.flag_1ms) {
			Task_time.flag_1ms = 0;
			//////////////////

		}

		if (Task_time.flag_10ms) {
			Task_time.flag_10ms = 0;
			//////////////////
			app_2d4_pro();

			bsp_KeyScan();

		}
		if (Task_time.flag_100ms) {
			Task_time.flag_100ms = 0;
			//////////////////

			Repeat_Pro();

		}
		if (Task_time.flag_500ms) {
			Task_time.flag_500ms = 0;
			//////////////////

		}
		if (Task_time.flag_1s) {
			Task_time.flag_1s = 0;
			//////////////////

			app_work_1s_pro();
#if 1
			PD_cnt++;
			if (PD_cnt >= (g_tWork.match_code_mode ? 30 : 3)) {
				PD_cnt = 0;
				Repeat_Stop();
				into_powerDown();
			}
#endif
		}
#if 1
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {
			PD_cnt = 0;
			if (wireless_init_flag == 0) {
				wireless_init_flag = 1;

				g_tWork.match_code_mode = 0;
				app_2d4_switch_saved_address();
			}
			app_key_pro(ucKeyCode);

//			into_powerDown();
		}
#endif
	}
}
