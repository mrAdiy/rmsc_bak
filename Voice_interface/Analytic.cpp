/*
������ ���� �������� ���������� ������������� ����� �������� ������.
*/

#include "Analytic.h"
#include "stdio.h"

bool Search_pause(Voice_type VT)
{
	//����������: �� ����� ���� ����� (�.�. �������� "�������") ��� ����?

	return false;
}

Voice_type LPC(Voice_type VT)
{
	BEST_ERROR = 1.0;

	get_signal_parameter(VOICE_CODER_TYPE, VT, Get_previous_sound());

	Set_current_sound(NEW_VOICE); //� �������� ��� ����� ����.

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
	//�� ����������� ���������� ������ ���������� ����� ������.
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
	//���������� ��������� ������������ ������� � ����������� ���������
	//�������������� ������� ����� (� ����� �� ���-�� ����� � �������).

	//������������ ��������: ���� ��� ��������� ���� ������ ����������� ������ 
	//������� (��-��������� 1), �� �� ��������� � BEST_PHONEM_ID id ������,
	//������� ���� ������� ������, � � BEST_ERROR - �������� ������ ������.
	//��� �� ��� ���, ���� �� ����� �� �����. � ����� �� ����� ID ������,
	//������� ����� ����� ��������� ���� �� �����.
}

void Compare_with_adaptive_dictionary(Voice_type VT, Voice_type VT_old)
{
	//���������� ��������� ������������ ������� � ����������� ���������
	//����������� ������� ����� (� �� �������������). �����������������
	//�������� ���������� � ���������� NEW_VOICE.
}

void get_signal_parameter(char coder_type, Voice_type VT1, Voice_type VT2)
{
	//�������� ��������� ������� (�������� �� ���� ������).
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
