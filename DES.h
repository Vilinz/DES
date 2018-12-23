#ifndef _DES_H
#define _DES_H
#include <stdlib.h>
#include <string.h>
/*
*sub keys used in encrypt and decrypt
*/
typedef struct {
	unsigned char K[6];
	unsigned char C[4];
	unsigned char D[4];
} sub_and_CD_set;
/*
*output data in binary to test
*/
void test(unsigned char* str, int size);
/*
*do IP transform
*/
void process_IP_transform(unsigned char* origin_message, unsigned char* processed_message);
/*
*do IP inverse transform
*/
void process_inverse_IP_transform(unsigned char* origin_message, unsigned char* processed_message);
/*
*do E expansion transform
*/
void process_E_expansion(unsigned char* origin_message, unsigned char* processed_message);
/*
*generate sub keys
*/
void get_sub_key_set(unsigned char* origin_key);
/*
*do PC1 transform
*/
void process_PC1_transform(unsigned char* origin_key, unsigned char* C0D0);
/*
*do PC2 transform
*/
void process_PC2_transform(unsigned char* origin_key, unsigned char* target_key);
/*
*do P transform
*/
void process_P_transform(unsigned char* origin_key, unsigned char* target_key);
/*
*combine all processes
*mode to tag encrypt or decrypt
*/
void solution(unsigned char* origin_message, unsigned char* processed_message,int mode);
/*
*combine feistel processes
*/
void feistel(unsigned char* R, unsigned char* sub_key, unsigned char* target_message);
#endif