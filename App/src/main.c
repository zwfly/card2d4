#include "app.h"

static uint8_t dome_cnt = 0;

void main(void) {
	uint8_t PD_cnt = 0;
	uint8_t ucKeyCode;
	/****************/
	bsp_Init();

	/****************/
	app_eeprom_Init();
	app_2d4_init();
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
			bsp_KeyScan();
		}
		if (Task_time.flag_100ms) {
			Task_time.flag_100ms = 0;
			//////////////////
			app_2d4_pro();

			Repeat_Pro();

		}
		if (Task_time.flag_500ms) {
			Task_time.flag_500ms = 0;
			//////////////////

		}
		if (Task_time.flag_1s) {
			Task_time.flag_1s = 0;
			//////////////////
#if 1
			PD_cnt++;
			if (PD_cnt >= 5) {
				PD_cnt = 0;

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

				continue;
			}
#endif
		}
#if 1
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {
			PD_cnt = 0;
			app_key_pro(ucKeyCode);
		}
#endif
	}
}
