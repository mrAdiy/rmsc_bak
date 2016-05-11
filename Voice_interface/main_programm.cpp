/*
Данная программа является демонстрационной: она показывает, как настроить
предлагаемое API для работы с различными видами речевых кодеров.
*/
#include "stdio.h"
#include "stdlib.h"

#include "Analytic.h"
#include "Synthetic.h"
#include "Speech_decoder.h"

void demo_vocoder(Voice_type VT);
void demo_leapreader(Voice_type VT);

Voice_type get_voice()
{
	//Подразумевается, что мы приняли сигнал, в данной ф-ции считали с него
	//необходимые параметры	и заполнили ими наш тип (Voice_type). Далее мы 
	//будем оценивать полученный сигнал по данным параметрам.

	Voice_type VT = { 3, 5, 1 };

	return VT;
}

void main()
{
	Voice_type VT;
	
	for (int i = 0; i < 3; i++){ //3 итерации - для демонстрационной программы!
		//При работе надо или опрашивать вход микрофона с заданной частотой, 
		//или задействовать вектора прерываний.

		VT = get_voice();

		printf("Amplitude: %d \n\rFrequency: %d\n\r",
								VT.amplitude, VT.frequency);

		if (!Search_pause(VT)){ //Паузы не было
			//Вызов различных кодеров.
			demo_vocoder(VT);
			demo_leapreader(VT);
		}
		else continue;

	}
	system("pause");
}

void demo_vocoder(Voice_type VT)
{
	Set_phoneme_num(Phoneme_number_generator(VT));
	VOICE_CODER_TYPE = 'V';
	Code_generator(VOICE_CODER_TYPE, 1, 1);
	//Результат лежит в массиве на 500 эл-тов CONV_CODE.

	//ДЕкодирование:
	VOICE_CODER_TYPE = 'V'; //На приёмнике снова указываем тип кодера.
	Voice_type result_voise = made_voise(CONV_CODE, 1, 1);
}

void demo_leapreader(Voice_type VT)
{
	Set_filter_parametres(LPC(VT));
	VOICE_CODER_TYPE = 'L';
	Code_generator(VOICE_CODER_TYPE, 2, 1);
	//Результат лежит в массиве на 500 эл-тов CONV_CODE.

	//ДЕкодирование:
	VOICE_CODER_TYPE = 'L';//На приёмнике снова указываем тип кодера.
	Voice_type result_voise = made_voise(CONV_CODE, 1, 1);
}