/*
Данный файл содержит интерфейсы синтетической части речевого кодера.
*/

#include "Synthetic.h"

#define SIZE_OF_VOICE_TYPE 3

int PHONEME_NUMBER;
Voice_type CURRENT_VT;
int BLOCK_CODE[100];
int CONV_CODE[500];

void Set_filter_parametres(Voice_type VT)
{
	CURRENT_VT = VT;
}

void Set_phoneme_num(int phoneme_num)
{
	PHONEME_NUMBER = phoneme_num;
}

void Code_generator(char coder_type, int block_code_id, int conv_code_id)
{
	int data_to_encode[1 + SIZE_OF_VOICE_TYPE] = { 0, };//+фонема
	//Массив блочных ф-ций
	void(*b_mas[2])(int*, int*);
	b_mas[0] = bm_1;
	b_mas[1] = bm_2;
	//Массив свёрточных ф-ций
	void(*c_mas[2])(int*, int*);
	c_mas[0] = cm_1;
	c_mas[1] = cm_2;

	switch (coder_type){//Согласно типу кодера выбираем объекты для 
						//кодирования: фонему и/или параметры фильтра.
	case 'V':
		data_to_encode[0] = PHONEME_NUMBER;
		break;

	case 'L':
		data_to_encode[1] = CURRENT_VT.amplitude;
		data_to_encode[2] = CURRENT_VT.frequency;
		break;

	case 'H':
		data_to_encode[0] = PHONEME_NUMBER;
		data_to_encode[1] = CURRENT_VT.amplitude;
		data_to_encode[2] = CURRENT_VT.frequency;
		break;

	default:
		break;
	}

	//Определяем блочный код
	switch (block_code_id){
	case 1:
		b_mas[0](data_to_encode, BLOCK_CODE);
		break;

	case 2:
		b_mas[1](data_to_encode, BLOCK_CODE);
		break;

	default:
		break;
	}

	//Определяем свёрточный код
	switch (conv_code_id){
	case 1:
		c_mas[0](BLOCK_CODE, CONV_CODE);
		break;

	case 2:
		c_mas[1](BLOCK_CODE, CONV_CODE);
		break;

	default:
		break;
	}

	Interleaving(CONV_CODE);
}