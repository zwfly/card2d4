/*
 *********************************************************************************************************
 *
 *	ģ������ : ������������ģ��
 *	�ļ����� : bsp_key.c
 *	��    �� : V1.0
 *	˵    �� : ɨ�������������������˲����ƣ����а���FIFO�����Լ�������¼���
 *				(1) ��������
 *				(2) ��������
 *				(3) ������
 *				(4) ����ʱ�Զ�����
 *
 *********************************************************************************************************
 */

#include "bsp.h"
#include <string.h>

#if 0
static idata KEY_T s_tBtn[KEY_COUNT];
static idata KEY_FIFO_T s_tKey; /* ����FIFO����,�ṹ�� */
#else
static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey; /* ����FIFO����,�ṹ�� */
#endif

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

/*
 *********************************************************************************************************
 *	�� �� ��: IsKeyDownX
 *	����˵��: �жϰ����Ƿ���
 *	��    ��: ��
 *	�� �� ֵ: ����ֵ1 ��ʾ���£�0��ʾδ����
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
 *	�� �� ��: bsp_InitKey
 *	����˵��: ��ʼ������. �ú����� bsp_Init() ���á�
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_InitKey(void) {
	bsp_InitKeyVar(); /* ��ʼ���������� */
	bsp_InitKeyHard(); /* ��ʼ������Ӳ�� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_PutKey
 *	����˵��: ��1����ֵѹ�밴��FIFO��������������ģ��һ��������
 *	��    ��:  _KeyCode : ��������
 *	�� �� ֵ: ��
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
 *	�� �� ��: bsp_GetKey
 *	����˵��: �Ӱ���FIFO��������ȡһ����ֵ��
 *	��    ��:  ��
 *	�� �� ֵ: ��������
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
 *	�� �� ��: bsp_GetKey2
 *	����˵��: �Ӱ���FIFO��������ȡһ����ֵ�������Ķ�ָ�롣
 *	��    ��:  ��
 *	�� �� ֵ: ��������
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
 *	�� �� ��: bsp_GetKeyState
 *	����˵��: ��ȡ������״̬
 *	��    ��:  _ucKeyID : ����ID����0��ʼ
 *	�� �� ֵ: 1 ��ʾ���£� 0 ��ʾδ����
 *********************************************************************************************************
 */
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID) {
	return s_tBtn[_ucKeyID].State;
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_SetKeyParam
 *	����˵��: ���ð�������
 *	��    �Σ�_ucKeyID : ����ID����0��ʼ
 *			_LongTime : �����¼�ʱ��
 *			 _RepeatSpeed : �����ٶ�
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed) {
	s_tBtn[_ucKeyID].LongTime = _LongTime; /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed; /* �����������ٶȣ�0��ʾ��֧������ */
	s_tBtn[_ucKeyID].RepeatCount = 0; /* ���������� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_ClearKey
 *	����˵��: ��հ���FIFO������
 *	��    �Σ���
 *	�� �� ֵ: ��������
 *********************************************************************************************************
 */
void bsp_ClearKey(void) {
	s_tKey.Read = s_tKey.Write;
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_InitKeyHard
 *	����˵��: ���ð�����Ӧ��GPIO
 *	��    ��:  ��
 *	�� �� ֵ: ��
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
 *	�� �� ��: bsp_InitKeyVar
 *	����˵��: ��ʼ����������
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void bsp_InitKeyVar(void) {
	uint8_t i = 0;

	memset((uint8_t *) &s_tBtn, 0, sizeof(s_tBtn));

	/* �԰���FIFO��дָ������ */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* ��ÿ�������ṹ���Ա������һ��ȱʡֵ */
	for (i = 0; i < KEY_COUNT; i++) {
		s_tBtn[i].LongTime = KEY_LONG_TIME; /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2; /* ����������Ϊ�˲�ʱ���һ�� */
		s_tBtn[i].State = 0; /* ����ȱʡ״̬��0Ϊδ���� */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;				/* �������µļ�ֵ���� */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;				/* ��������ļ�ֵ���� */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;				/* �������������µļ�ֵ���� */
		s_tBtn[i].RepeatSpeed = 0; /* �����������ٶȣ�0��ʾ��֧������ */
		s_tBtn[i].RepeatCount = 0; /* ���������� */
	}

//	s_tBtn[3].RepeatSpeed = 50; /* �����������ٶȣ�0��ʾ��֧������ */
//	s_tBtn[4].RepeatSpeed = 50; /* �����������ٶȣ�0��ʾ��֧������ */

	/* �жϰ������µĺ��� */
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
 *	�� �� ��: bsp_DetectKey
 *	����˵��: ���һ��������������״̬�����뱻�����Եĵ��á�
 *	��    ��:  �����ṹ����ָ��
 *	�� �� ֵ: ��
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

				/* ���Ͱ�ť���µ���Ϣ */
				bsp_PutKey((uint8_t) (3 * i + 1));
			}

			if (pBtn->LongTime > 0) {
				if (pBtn->LongCount < pBtn->LongTime) {
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++pBtn->LongCount == pBtn->LongTime) {
						/* ��ֵ���밴��FIFO */
						bsp_PutKey((uint8_t) (3 * i + 3));
					}
				} else {
					if (pBtn->RepeatSpeed > 0) {
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
							pBtn->RepeatCount = 0;
							/* ��������ÿ��10ms����1������ */
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

				/* ���Ͱ�ť�������Ϣ */
				bsp_PutKey((uint8_t) (3 * i + 2));
			}
		}
		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_KeyScan
 *	����˵��: ɨ�����а���������������systick�ж������Եĵ���
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_KeyScan(void) {
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++) {
		bsp_DetectKey(i);
	}
}

/***************************** (END OF FILE) *********************************/
