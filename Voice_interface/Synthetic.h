/*
Данный файл содержит прототипы ф-ций синтетической части речевого кодера.

Тип кодера задаётся символом (char):
V - обычный вокодер (определяет и передаёт № фонемы).
L - липредер (вокодер с линейным предсказанием - снимает и передаёт
параметры фильтра).
H - гибридный вариант (определяет как № фонемы, так и параметры фильтра).
*/

#ifndef SYNTHETIC
#define SYNTHETIC

#include "Voice_type.h"
#include "Channel_coding.h"

void Set_filter_parametres(Voice_type VT);
void Set_phoneme_num(int phoneme_num);
//Используем библиотеку для канального кодирования:
void Code_generator(char coder_type, int block_code_id, int conv_code_id);

#endif