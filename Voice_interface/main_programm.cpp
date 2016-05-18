/*
������ ��������� �������� ����������������: ��� ����������, ��� ���������
������������ API ��� ������ � ���������� ������ ������� �������.
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
	//���������������, ��� �� ������� ������, � ������ �-��� ������� � ����
	//����������� ���������	� ��������� ��� ��� ��� (Voice_type). ����� �� 
	//����� ��������� ���������� ������ �� ������ ����������.

	Voice_type VT = { 3, 5, 1 };

	return VT;
}

void main()
{
	Voice_type VT;
	
	for (int i = 0; i < 1; i++){ //3 �������� - ��� ���������������� ���������!
		//��� ������ ���� ��� ���������� ���� ��������� � �������� ��������, 
		//��� ������������� ������� ����������.

		VT = get_voice();

		printf("Amplitude: %d \n\rFrequency: %d\n\r",
								VT.amplitude, VT.frequency);

		if (!Search_pause(VT)){ //����� �� ����
			//����� ��������� �������.
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
	//��������� ����� � ������� �� 500 ��-��� CONV_CODE.

	//������������� ��������� �������� ������ � INPUT_CODE
	Voice_type result_voice = made_voice(coder_type, BLOCK_CODE, 2, 1);
	printf("Phoneme number is %d\n", result_voice.phoneme);
}

void demo_leapreader(char coder_type, Voice_type VT)
{
	Set_filter_parametres(LPC(coder_type, VT));
	Code_generator(coder_type, 1, 1);
	//��������� ����� � ������� �� 500 ��-��� CONV_CODE.

	//������������� ��������� �������� ������ � INPUT_CODE
	Voice_type result_voice = made_voice(coder_type, BLOCK_CODE, 1, 1);
}