/*
Данный файл содержит прототипы ф-ций аналитической части речевого кодера.

Тип кодера задаётся символом (char): 
V - обычный вокодер (определяет и передаёт № фонемы).
L - липредер (вокодер с линейным предсказанием - снимает и передаёт 
	параметры фильтра).
H - гибридный вариант (определяет как № фонемы, так и параметры фильтра).
*/

#ifndef ANALYTIC
#define ANALYTIC

#include "Voice_type.h"

bool Search_pause(Voice_type VT);
Voice_type LPC(Voice_type VT); //Linear Prediction 
//Next 2 functions - for delay line: 
void Set_current_sound(Voice_type VT);
Voice_type Get_previous_sound();
void Compare_with_adaptive_dictionary(Voice_type VT, Voice_type VT_old);
void get_signal_parameter(char coder_type, Voice_type VT1, Voice_type VT2);
int Phoneme_number_generator(Voice_type VT);
void Save_best_phoneme_id(int id);
void Compare_with_fixed_dictionary(Voice_type VT);

#endif