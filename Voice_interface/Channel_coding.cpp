/*
Данный файл содержит интерфейсы канальных кодеков.
*/

#include "Channel_coding.h"
#include "stdio.h"

void bm_1(int to_encode[], int out[])
{

}

void bm_2(int to_encode[], int out[])
{
	printf("\nHere is second ENcode method (Hamming: ENcode)\n");
	int to_encode_size = 1, i,
		bit_1, bit_2, bit_3, bit_4, bit_5, bit_6, bit_7;
	
	to_encode[0] = 11;
	/*
	Алгоритм кодирования Хэмминга (4,7): 	
	биты 3, 5, 6, 7 - информационные; биты 1, 2, 4 - контрольные.
	Контрольные биты образуются через сумму по модуль 2 между:
	1: 3, 5, 7 | 2: 3, 6, 7 | 4: 5, 6, 7)
	*/
	for (i = 0; i < to_encode_size; i++){
		printf("Data to ecnode: %d\n", to_encode[i]);
		//Информационные биты:
		bit_7 = (to_encode[i] & 1);
		bit_6 = (to_encode[i] & 2) >> 1;
		bit_5 = (to_encode[i] & 4) >> 2;
		bit_3 = (to_encode[i] & 8) >> 3;

		//Контрольные биты:
		bit_1 = bit_3 ^ bit_5 ^ bit_7;
		bit_2 = bit_3 ^ bit_6 ^ bit_7;
		bit_4 = bit_5 ^ bit_6 ^ bit_7;
		
		//Заполняем результат:
		out[i] = bit_1 | (bit_2 << 1) | (bit_3 << 2) | (bit_4 << 3) 
			| (bit_5 << 4) | (bit_6 << 5) | (bit_7 << 6);		
	}

}

void bm_3(int to_encode[], int out[])
{

}

void cm_1(int to_encode[], int out[])
{

}

void cm_2(int to_encode[], int out[])
{

}

void De_bm_1(int to_decode[], int out[])
{

}

void De_bm_2(int to_decode[], int out[])
{
	printf("\nHere is second DEcode method (Hamming: DEcode)\n");

	printf("Input block code:\n");
	for (int i = 0; i < 1; i++) printf("%d\n", to_decode[i]);
	/*
	Алгоритм декодирования Хэмминга (4, 7):
	Проверочный 3-х битовый код строится из суммы по модуль 2 между битами:
	1: 1, 3, 5, 7
	2: 2, 3, 6, 7
	3: 4, 5, 6, 7
	После если ошибки нет - мы получим код 000. В противном случае мы
	получим код, указывающий на позицию ошибки.
	*/
	int to_decode_size = 1, i,
		bit_1, bit_2, bit_3, bit_4, bit_5, bit_6, bit_7,
		control_bit_1, control_bit_2, control_bit_3, control_code = 0;


	for (i = 0; i < to_decode_size; i++){

		//Разбиваем на биты:
		bit_1 = (to_decode[i] & 1);
		bit_2 = (to_decode[i] & 2) >> 1;
		bit_3 = (to_decode[i] & 4) >> 2;
		bit_4 = (to_decode[i] & 8) >> 3;
		bit_5 = (to_decode[i] & 16) >> 4;
		bit_6 = (to_decode[i] & 32) >> 5;
		bit_7 = (to_decode[i] & 64) >> 6;
		
		//Составляем контрольные биты
		control_bit_1 = bit_1 ^ bit_3 ^ bit_5 ^ bit_7;
		control_bit_2 = bit_2 ^ bit_3 ^ bit_6 ^ bit_7;
		control_bit_3 = bit_4 ^ bit_5 ^ bit_6 ^ bit_7;
		control_code = control_bit_1 | (control_bit_2 << 1) | (control_bit_3 << 2);

		if (control_code == 0)
			out[i] = bit_3 | (bit_5 << 2) | (bit_6 << 1) | (bit_7 << 3);
		else{
			//Повреждён только контрольный бит
			if (control_code == 1 || control_code == 2 || control_code == 4)
				out[i] = bit_3 | (bit_5 << 2) | (bit_6 << 1) | (bit_7 << 3);
			else{//Повреждён информационный бит.
				switch (control_code){
				case 3:
					bit_3 = (~bit_3 & 1);
					break;
				case 5:
					bit_5 = (~bit_5 & 1);
					break;
				case 6:
					bit_6 = (~bit_6 & 1);
					break;
				case 7:
					bit_7 = (~bit_7 & 1);
					break;
				default:
					break;
				}
				out[i] = bit_3 | (bit_5 << 2) | (bit_6 << 1) | (bit_7 << 3);
			}

		}
		printf("Result of Hamming (4, 7) decode: %d\n", out[i]);
	}
}

void De_bm_3(int to_decode[], int out[])
{

}

void De_cm_1(int to_decode[], int out[])
{

}

void De_cm_2(int to_decode[], int out[])
{

}
