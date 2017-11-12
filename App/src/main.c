#include "app.h"

static uint8_t dome_cnt = 0;

void main(void) {

	/****************/
	bsp_Init();

	/****************/
	app_eeprom_Init();
	app_2d4_init();
//	app_work_Init();
//	app_uart_Init();
//	app_dome_Init();
	/****************/
//	Show_FW_Version_Number_To_PC();
	while (1) {

//		Relay_toggle();
		if (Task_time.flag_1ms) {
			Task_time.flag_1ms = 0;
			//////////////////


		}

		if (Task_time.flag_10ms) {
			Task_time.flag_10ms = 0;
			//////////////////

		}
		if (Task_time.flag_100ms) {
			Task_time.flag_100ms = 0;
			//////////////////
			app_2d4_pro();

//			Repeat_Pro();

		}
		if (Task_time.flag_500ms) {
			Task_time.flag_500ms = 0;
			//////////////////

		}
		if (Task_time.flag_1s) {
			Task_time.flag_1s = 0;
			//////////////////

		}
	}
}
