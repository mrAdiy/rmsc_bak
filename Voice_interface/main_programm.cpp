/*
Данная программа является демонстрационной: она показывает, как настроить
предлагаемое API для работы с различными видами речевых кодеров.
*/
#include "stdio.h"
#include "stdlib.h"

#include "Analytic.h"
#include "Synthetic.h"
#include "Speech_decoder.h"

#include "HelloWorld.h"

void demo_vocoder(char coder_type, Voice_type VT);
void demo_leapreader(char coder_type, Voice_type VT);

int INPUT_CODE[500];

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
	
	for (int i = 0; i < 1; i++){ //3 итерации - для демонстрационной программы!
		//При работе надо или опрашивать вход микрофона с заданной частотой, 
		//или задействовать вектора прерываний.

		VT = get_voice();

		printf("Amplitude: %d \n\rFrequency: %d\n\r",
								VT.amplitude, VT.frequency);

		if (!Search_pause(VT)){ //Паузы не было
			//Вызов различных кодеров.
			demo_vocoder('V', VT);
			//demo_leapreader('L', VT);
		}
		else continue;

	}
	Hello();
	system("pause");
}

void demo_vocoder(char coder_type, Voice_type VT)
{
	Set_phoneme_num(Phoneme_number_generator(coder_type, VT));
	Code_generator(coder_type, 2, 1);
	//Результат лежит в массиве на 500 эл-тов CONV_CODE.

	//ДЕкодирование считываем принятые данные в INPUT_CODE
	Voice_type result_voice = made_voice(coder_type, BLOCK_CODE, 2, 1);
	printf("Phoneme number is %d\n", result_voice.phoneme);
}

void demo_leapreader(char coder_type, Voice_type VT)
{
	Set_filter_parametres(LPC(coder_type, VT));
	Code_generator(coder_type, 1, 1);
	//Результат лежит в массиве на 500 эл-тов CONV_CODE.

	//ДЕкодирование считываем принятые данные в INPUT_CODE
	Voice_type result_voice = made_voice(coder_type, BLOCK_CODE, 1, 1);
}