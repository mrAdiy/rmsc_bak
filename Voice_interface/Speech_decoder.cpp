/*
������ ���� �������� ���������� �������� ��������.
*/

#include "Speech_decoder.h"

Voice_type channel_decoding(int input_data[], int block_code_id, int conv_code_id)
{

}

Voice_type get_filter_parameters(int input_data[], int block_code_id, int conv_code_id)
{
	Voice_type VT = { 1, 1, 1 };

	return VT;
}

int get_phoneme_number(int input_data[], int block_code_id, int conv_code_id)
{
	return 1;
}

Voice_type get_ALL(int input_data[], int block_code_id, int conv_code_id)
{
	Voice_type VT = {5, 5, 1};

	return VT;
}

Voice_type made_voise(int input_data[], int block_code_id, int conv_code_id)
{
	Voice_type VT;

	switch (VOICE_CODER_TYPE){
	case 'V':
		VT.phoneme = get_phoneme_number(input_data, block_code_id, conv_code_id);
		break;

	case 'L':
		VT = get_filter_parameters(input_data, block_code_id, conv_code_id);
		break;

	case 'H':
		VT = get_ALL(input_data, block_code_id, conv_code_id);
		break;

	default:
		break;
	}

	return VT;
}