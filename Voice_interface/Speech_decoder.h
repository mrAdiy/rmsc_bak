/*
Данный файл содержит прототипы ф-ций для речевого декодера.
*/

#include "Voice_type.h"
#include "Channel_coding.h"

#ifndef SPEECH_DECODER
#define SPEECH_DECODER

Voice_type get_filter_parameters(int input_data[], int block_code_id, int conv_code_id);
int get_phoneme_number(int input_data[], int block_code_id, int conv_code_id);
Voice_type made_voise(int input_data[], int block_code_id, int conv_code_id);
Voice_type get_ALL(int input_data[], int block_code_id, int conv_code_id);
Voice_type channel_decoding(int input_data[], int block_code_id, int conv_code_id);

#endif