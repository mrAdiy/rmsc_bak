/*
Данный файл содержит прототипы ф-ций для канальных кодеков.
*/

#ifndef CHANNEL_CODING
#define CHANNEL_CODING

void bm_1(int to_encode[], int out[]);
void bm_2(int to_encode[], int out[]);
void cm_1(int to_encode[], int out[]);
void cm_2(int to_encode[], int out[]);
void De_bm_1(int to_encode[], int out[]);
void De_bm_2(int to_encode[], int out[]);
void De_cm_1(int to_encode[], int out[]);
void De_cm_2(int to_encode[], int out[]);
void Interleaving(int to_interleaving[]);
void DE_interleaving(int to_DEinterleaving[]);

#endif