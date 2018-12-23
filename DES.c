#include <stdio.h>

#include "DES.h"

sub_and_CD_set key_set[17];


int IP_transform_table[64] = 	{58, 50, 42, 34, 26, 18, 10, 2,
								60, 52, 44, 36, 28, 20, 12, 4,
								62, 54, 46, 38, 30, 22, 14, 6,
								64, 56, 48, 40, 32, 24, 16, 8,
								57, 49, 41, 33, 25, 17,  9, 1,
								59, 51, 43, 35, 27, 19, 11, 3,
								61, 53, 45, 37, 29, 21, 13, 5,
								63, 55, 47, 39, 31, 23, 15, 7};

int inverse_IP_transform_table[64] =  {40,  8, 48, 16, 56, 24, 64, 32,
									39,  7, 47, 15, 55, 23, 63, 31,
									38,  6, 46, 14, 54, 22, 62, 30,
									37,  5, 45, 13, 53, 21, 61, 29,
									36,  4, 44, 12, 52, 20, 60, 28,
									35,  3, 43, 11, 51, 19, 59, 27,
									34,  2, 42, 10, 50, 18, 58, 26,
									33,  1, 41,  9, 49, 17, 57, 25};

int S1[64] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int S2[64] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int S3[64] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[64] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int S5[64] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int S6[64] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[64] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int S8[64] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};


int E_expansion_table[48] =  {32,  1,  2,  3,  4,  5,
						4,  5,  6,  7,  8,  9,
						8,  9, 10, 11, 12, 13,
						12, 13, 14, 15, 16, 17,
						16, 17, 18, 19, 20, 21,
						20, 21, 22, 23, 24, 25,
						24, 25, 26, 27, 28, 29,
						28, 29, 30, 31, 32,  1};

int P_transform_table[32] =    {16,  7, 20, 21,
						29, 12, 28, 17,
						1, 15, 23, 26,
						5, 18, 31, 10,
						2,  8, 24, 14,
						32, 27,  3,  9,
						19, 13, 30,  6,
						22, 11,  4, 25};


int PC1_transform_table[56] = {57, 49,  41, 33,  25,  17,  9,
						1, 58,  50, 42,  34,  26, 18,
						10,  2,  59, 51,  43,  35, 27,
						19, 11,   3, 60,  52,  44, 36,
						63, 55,  47, 39,  31,  23, 15,
						7, 62,  54, 46,  38,  30, 22,
						14,  6,  61, 53,  45,  37, 29,
						21, 13,   5, 28,  20,  12,  4};

int PC2_transform_table[48] =    {14, 17, 11, 24,  1,  5,
								 3, 28, 15,  6, 21, 10,
								23, 19, 12,  4, 26,  8,
								16,  7, 27, 20, 13,  2,
								41, 52, 31, 37, 47, 55,
								30, 40, 51, 45, 33, 48,
								44, 49, 39, 56, 34, 53,
								46, 42, 50, 36, 29, 32};

void test(unsigned char* str, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < 8; j++) {
			char temp = 0x01 << (7 - j);
			if(temp&str[i]) {
				printf("1");
			} else {
				printf("0");
			}
		}
	}
	printf("\n");
}

void process_IP_transform(unsigned char* origin_message, unsigned char* processed_message) {
	memset(processed_message, 0, 8);
	for(int i = 0; i < 64; i++) {
		int shift = IP_transform_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_message[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);
		processed_message[i/8] |= (shift_byte >> i%8);
	}
	/*
	test(processed_message_L,4);
	test(processed_message_R, 4);
	*/
}

void process_inverse_IP_transform(unsigned char* origin_message, unsigned char* processed_message) {
	memset(processed_message, 0, 8);
	for(int i = 0; i < 64; i++) {
		int shift = inverse_IP_transform_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_message[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);

		processed_message[i/8] |= (shift_byte >> i%8);
	}
}

void process_E_expansion(unsigned char* origin_message, unsigned char* processed_message) {
	memset(processed_message, 0, 6);
	for(int i = 0; i < 48; i++) {
		int shift = E_expansion_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_message[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);

		processed_message[i/8] |= (shift_byte >> i%8);
	}
}

void process_PC1_transform(unsigned char* origin_key, unsigned char* C0D0) {
	memset(C0D0, 0, 7);
	for(int i = 0; i < 56; i++) {
		int shift = PC1_transform_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_key[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);

		C0D0[i/8] |= (shift_byte >> i%8);
	}

}

void process_PC2_transform(unsigned char* origin_key, unsigned char* target_key) {
	memset(target_key, 0, 6);
	for(int i = 0; i < 48; i++) {
		int shift = PC2_transform_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_key[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);

		target_key[i/8] |= (shift_byte >> i%8);
	}
}

void get_sub_key_set(unsigned char* origin_key) {
	memset(key_set, 0, 17);
	unsigned char* CD = (unsigned char*)malloc(7*sizeof(unsigned char));
	memset(CD, 0, 7);
	process_PC1_transform(origin_key, CD);
	//test(CD, 7);
	for(int i = 0; i < 7; i++) {
		key_set[0].K[i] = CD[i];
	}
	//test(key_set[0].K, 7);
	for(int i = 0; i < 3; i++) {
		key_set[0].C[i] = key_set[0].K[i];
	}
	key_set[0].C[3] = key_set[0].K[3] & 0xF0;
	//test(key_set[0].C, 4);

	for (int i=0; i<3; i++) {
		key_set[0].D[i] = (key_set[0].K[i+3] & 0x0F) << 4;
		key_set[0].D[i] |= (key_set[0].K[i+4] & 0xF0) >> 4;
	}

	key_set[0].D[3] = (key_set[0].K[6] & 0x0F) << 4;
	//test(key_set[0].D, 4);

	unsigned char shift_byte;
	int tag = 0;
	for(int i = 1; i < 17; i++) {
		for(int j = 0; j < 4;  j++) {
			key_set[i].C[j] = key_set[i-1].C[j];
			key_set[i].D[j] = key_set[i-1].D[j];
		}

		if(i == 1||i == 2|| i== 9||i == 16) {
			shift_byte = 0x80;
			tag = 1;
		} else {
			shift_byte = 0xc0;
			tag = 2;
		}

		//left shift
		//first get left most shift
		unsigned char first_char_left_shift_c = key_set[i].C[0] & shift_byte;
		unsigned char second_char_left_shift_c = key_set[i].C[1] & shift_byte;
		unsigned char third_char_left_shift_c = key_set[i].C[2] & shift_byte;
		unsigned char fourth_char_left_shift_c = key_set[i].C[3] & shift_byte;

		//get C
		key_set[i].C[0] = key_set[i].C[0] << tag;
		key_set[i].C[0] = key_set[i].C[0] | (second_char_left_shift_c >> (8 - tag));
		key_set[i].C[1] = key_set[i].C[1] << tag;
		key_set[i].C[1] = key_set[i].C[1] | (third_char_left_shift_c >> (8 - tag));
		key_set[i].C[2] = key_set[i].C[2] << tag;
		key_set[i].C[2] = key_set[i].C[2] | (fourth_char_left_shift_c >> (8 - tag));
		key_set[i].C[3] = key_set[i].C[3] << tag;
		key_set[i].C[3] = key_set[i].C[3] | (first_char_left_shift_c >> (4 - tag));


		unsigned char first_char_left_shift_d = key_set[i].D[0] & shift_byte;
		unsigned char second_char_left_shift_d = key_set[i].D[1] & shift_byte;
		unsigned char third_char_left_shift_d = key_set[i].D[2] & shift_byte;
		unsigned char fourth_char_left_shift_d = key_set[i].D[3] & shift_byte;

		//get D
		key_set[i].D[0] = key_set[i].D[0] << tag;
		key_set[i].D[0] = key_set[i].D[0] | (second_char_left_shift_d >> (8 - tag));
		key_set[i].D[1] = key_set[i].D[1] << tag;
		key_set[i].D[1] = key_set[i].D[1] | (third_char_left_shift_d >> (8 - tag));
		key_set[i].D[2] = key_set[i].D[2] << tag;
		key_set[i].D[2] = key_set[i].D[2] | (fourth_char_left_shift_d >> (8 - tag));
		key_set[i].D[3] = key_set[i].D[3] << tag;
		key_set[i].D[3] = key_set[i].D[3] | (first_char_left_shift_d >> (4 - tag));

		unsigned char* temp_CD = (unsigned char*)malloc(7*sizeof(unsigned char));
		memset(temp_CD, 0, 7);
		for(int j = 0; j < 3; j++) {
			temp_CD[j] = key_set[i].C[j];
		}
		unsigned char get_fourth = 0xf0;
		unsigned char get_eighth = 0xff;
		temp_CD[3] = temp_CD[3] | (key_set[i].C[3] & get_fourth);
		unsigned char first = key_set[i].D[0] & get_fourth;
		unsigned char second = key_set[i].D[1] & get_fourth;
		unsigned char third = key_set[i].D[2] & get_fourth;
		unsigned char fourth = key_set[i].D[3] & get_fourth;


		temp_CD[3] |= (get_eighth & (first >> 4));
		temp_CD[4] |= ((key_set[i].D[0] << 4) | (second >> 4));
		temp_CD[5] |= ((key_set[i].D[1] << 4) | (third >> 4));
		temp_CD[6] |= ((key_set[i].D[2] << 4) | (fourth >> 4));

		/*
		if(i == 1) {
			test(key_set[1].C, 4);
			test(key_set[1].D, 4);
			test(temp_CD, 7);
		}
		*/
		process_PC2_transform(temp_CD, key_set[i].K);	
	}
	
}

void process_P_transform(unsigned char* origin_key, unsigned char* target_key) {
	memset(target_key, 0, 4);
	for(int i = 0; i < 32; i++) {
		int shift = P_transform_table[i];
		unsigned char shift_byte = 0x80 >> ((shift - 1)%8);
		shift_byte &= origin_key[(shift - 1)/8];
		shift_byte <<= ((shift - 1)%8);
		target_key[i/8] |= (shift_byte >> i%8);
	}
}

void feistel(unsigned char* R, unsigned char* sub_key, unsigned char* target_message) {
	memset(target_message, 0, 4);
	unsigned char* E_expansion_result = (unsigned char*)malloc(6*sizeof(unsigned char));
	memset(E_expansion_result, 0, 6);
	process_E_expansion(R, E_expansion_result);
	for(int i = 0; i < 6; i++) {
		E_expansion_result[i] ^= sub_key[i];
	}
	unsigned char row, column;
	unsigned char S_box_result[4];
	memset(S_box_result, 0, 4);

	// Byte 1
	row = 0;
	row |= ((E_expansion_result[0] & 0x80) >> 6);
	row |= ((E_expansion_result[0] & 0x04) >> 2);
	column = 0;
	column |= ((E_expansion_result[0] & 0x78) >> 3);
	S_box_result[0] |= ((unsigned char)S1[row*16+column] << 4);

	row = 0;
	row |= (E_expansion_result[0] & 0x02);
	row |= ((E_expansion_result[1] & 0x10) >> 4);
	column = 0;
	column |= ((E_expansion_result[0] & 0x01) << 3);
	column |= ((E_expansion_result[1] & 0xE0) >> 5);
	S_box_result[0] |= (unsigned char)S2[row*16+column];

	// Byte 2
	row = 0;
	row |= ((E_expansion_result[1] & 0x08) >> 2);
	row |= ((E_expansion_result[2] & 0x40) >> 6);
	column = 0;
	column |= ((E_expansion_result[1] & 0x07) << 1);
	column |= ((E_expansion_result[2] & 0x80) >> 7);
	S_box_result[1] |= ((unsigned char)S3[row*16+column] << 4);

	row = 0;
	row |= ((E_expansion_result[2] & 0x20) >> 4);
	row |= (E_expansion_result[2] & 0x01);
	column = 0;
	column |= ((E_expansion_result[2] & 0x1E) >> 1);
	S_box_result[1] |= (unsigned char)S4[row*16+column];

	// Byte 3
	row = 0;
	row |= ((E_expansion_result[3] & 0x80) >> 6);
	row |= ((E_expansion_result[3] & 0x04) >> 2);
	column = 0;
	column |= ((E_expansion_result[3] & 0x78) >> 3);
	S_box_result[2] |= ((unsigned char)S5[row*16+column] << 4);

	row = 0;
	row |= (E_expansion_result[3] & 0x02);
	row |= ((E_expansion_result[4] & 0x10) >> 4);
	column = 0;
	column |= ((E_expansion_result[3] & 0x01) << 3);
	column |= ((E_expansion_result[4] & 0xE0) >> 5);
	S_box_result[2] |= (unsigned char)S6[row*16+column];

	// Byte 4
	row = 0;
	row |= ((E_expansion_result[4] & 0x08) >> 2);
	row |= ((E_expansion_result[5] & 0x40) >> 6);
	column = 0;
	column |= ((E_expansion_result[4] & 0x07) << 1);
	column |= ((E_expansion_result[5] & 0x80) >> 7);
	S_box_result[3] |= ((unsigned char)S7[row*16+column] << 4);

	row = 0;
	row |= ((E_expansion_result[5] & 0x20) >> 4);
	row |= (E_expansion_result[5] & 0x01);
	column = 0;
	column |= ((E_expansion_result[5] & 0x1E) >> 1);
	S_box_result[3] |= (unsigned char)S8[row*16+column];

	process_P_transform(S_box_result, target_message);

}

void solution(unsigned char* origin_message, unsigned char* processed_message,int mode) {
	unsigned char* L = (unsigned char*)malloc(4*sizeof(unsigned char));
	unsigned char* R = (unsigned char*)malloc(4*sizeof(unsigned char));
	unsigned char* IP_transform_result = (unsigned char*)malloc(8*sizeof(unsigned char));
	unsigned char* data_to_process_inverse_IP = (unsigned char*)malloc(8*sizeof(unsigned char));
	memset(L, 0, 4);
	memset(R, 0, 4);
	memset(IP_transform_result, 0, 8);
	memset(processed_message, 0, 8);
	memset(data_to_process_inverse_IP, 0, 8);

	process_IP_transform(origin_message, IP_transform_result);
	for (int i = 0; i < 4; i++) {
		L[i] = IP_transform_result[i];
		R[i] = IP_transform_result[i+4];
	}
	//test(l, 4);

	unsigned char* next_L = (unsigned char*)malloc(4*sizeof(unsigned char));
	unsigned char* next_R = (unsigned char*)malloc(4*sizeof(unsigned char));
	memset(next_L, 0, 4);
	memset(next_R, 0, 4);

	int key_index;
	for (int i = 1; i < 17; i++) {
		memset(next_R, 0, 4);
		for(int j = 0; j < 4; j++) {
			next_L[j] = R[j];
		}

		if (mode == 0) {
			key_index = 17 - i;
		} else {
			key_index = i;
		}

		unsigned char* feistel_result = (unsigned char*)malloc(4*sizeof(unsigned char));
		feistel(R, key_set[key_index].K, next_R);
		
		for (int j = 0; j < 4; j++) {
			next_R[j] ^= L[j];
		}

		for (int j = 0; j < 4; j++) {
			L[j] = next_L[j];
			R[j] = next_R[j];
		}
	}

	for (int i = 0; i < 4; i++) {
		data_to_process_inverse_IP[i] = R[i];
		data_to_process_inverse_IP[4+i] = L[i];
	}

	process_inverse_IP_transform(data_to_process_inverse_IP, processed_message);
}