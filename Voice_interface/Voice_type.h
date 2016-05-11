/*
Данный файл содержит тип данных, который описывает человеческую речь.
*/

#ifndef VOICE_TYPE
#define VOICE_TYPE

typedef struct
{
	int amplitude;
	int frequency;	
	int phoneme;
} Voice_type;

//Для аналитической части:
Voice_type SOUND_DELAY;
Voice_type NEW_VOICE;
float BEST_ERROR;
int BEST_PHONEM_ID;

//Для синтетической части:
int PHONEME_NUMBER;
Voice_type CURRENT_VT;
int BLOCK_CODE[100];
int CONV_CODE[500];

//Тип кодера!
char VOICE_CODER_TYPE;

#endif