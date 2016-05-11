/*
Данный файл содержит интерфейсы аналитической части речевого кодера.
*/

#include "Analytic.h"
#include "stdio.h"

bool Search_pause(Voice_type VT)
{
	//Определяем: на входе была пауза (т.е. кодируем "пустоту") или речь?

	return false;
}

Voice_type LPC(Voice_type VT)
{
	BEST_ERROR = 1.0;

	get_signal_parameter(VOICE_CODER_TYPE, VT, Get_previous_sound());

	Set_current_sound(NEW_VOICE); //В задержку идёт новый звук.

	return NEW_VOICE;
}

void Set_current_sound(Voice_type VT)
{
	SOUND_DELAY = VT;
}

Voice_type Get_previous_sound()
{
	return SOUND_DELAY;
}

int Phoneme_number_generator(Voice_type VT)
{
	//По поступившим параметрам голоса определяем номер фонемы.
	BEST_ERROR = 1.0;

	get_signal_parameter(VOICE_CODER_TYPE, VT, VT);

	return BEST_PHONEM_ID;
}

void Save_best_phoneme_id(int id)
{
	BEST_PHONEM_ID = id;
}

void Compare_with_fixed_dictionary(Voice_type VT)
{
	//Сравниваем параметры поступившего сигнала с параметрами известных
	//фиксированному словарю фонем (в цикле по кол-ву фонем в словаре).

	//Прадлагаемый алгоритм: если при сравнении наша ошибка оказывается меньше 
	//текущей (по-умолчанию 1), то мы сохраняем в BEST_PHONEM_ID id фонемы,
	//которая дала меньшую ошибку, а в BEST_ERROR - значение лучшей ошибки.
	//Так до тех пор, пока не дойдём до конца. В итоге мы имеем ID фонемы,
	//которая лучше всего описывает звук на входе.
}

void Compare_with_adaptive_dictionary(Voice_type VT, Voice_type VT_old)
{
	//Сравниваем параметры поступившего сигнала с параметрами известных
	//адаптивному словарю фонем (и их корректировка). Скорректированные
	//значения помещаются в переменную NEW_VOICE.
}

void get_signal_parameter(char coder_type, Voice_type VT1, Voice_type VT2)
{
	//Получаем параметры сигнала (зависимо от типа кодера).
	switch (coder_type){
		case 'V':
			Compare_with_fixed_dictionary(VT1);
			break;

		case 'L':
			Compare_with_adaptive_dictionary(VT1, VT2);
			break;

		case 'H':
			Compare_with_fixed_dictionary(VT1);
			Compare_with_adaptive_dictionary(VT1, VT2);
			break;

		default:
			break;
	}
}
