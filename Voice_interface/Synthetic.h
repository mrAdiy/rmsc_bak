/*
������ ���� �������� ��������� �-��� ������������� ����� �������� ������.

��� ������ ������� �������� (char):
V - ������� ������� (���������� � ������� � ������).
L - �������� (������� � �������� ������������� - ������� � �������
��������� �������).
H - ��������� ������� (���������� ��� � ������, ��� � ��������� �������).
*/

#ifndef SYNTHETIC
#define SYNTHETIC

#include "Voice_type.h"
#include "Channel_coding.h"

void Set_filter_parametres(Voice_type VT);
void Set_phoneme_num(int phoneme_num);
//���������� ���������� ��� ���������� �����������:
void Code_generator(char coder_type, int block_code_id, int conv_code_id);

#endif