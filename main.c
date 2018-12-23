#include <stdio.h>
#include "DES.h"

int main(int argc,char*argv[]) {
	//unsigned char c[8] = "ad3de1gh";
	//unsigned char* target = (unsigned char*)malloc(6*sizeof(unsigned char));
	//sub_and_CD_set key_set[17];
	//memset(key_set, 0, 17);
	//test(c, 8);
	//printf("%lu\n", sizeof(c));
	/*
	
	memset(target,0,6);
	process_E_expansion(c, target);
	test(target, 6);
	*/
	//get_sub_key_set(c, key_set);
/*
	
	unsigned char origin[8] = "Q)^N <";
	get_sub_key_set("11111111");
	unsigned char* target1 = (unsigned char*)malloc(8*sizeof(unsigned char));
	unsigned char* temp = (unsigned char*)malloc(8*sizeof(unsigned char));
	solution(origin, target1, 0);
	test(origin, 8);
	test(target1, 8);
	solution(target1, temp, 1);
	test(temp, 8);
	*/

	if(argc != 3) {
		printf("Command error!\n");
		return -1;
	}

	FILE *fp = NULL;
	FILE *fp_w = NULL;
	int buffer_size = 0;
	int file_size;

	unsigned char* buffer = (unsigned char*)malloc(8*sizeof(unsigned char));
	unsigned char* target = (unsigned char*)malloc(8*sizeof(unsigned char));
	unsigned char* key = (unsigned char*)malloc(8*sizeof(unsigned char));
	memset(buffer, 0, 8);
	memset(target, 0, 8);
	memset(key, 0, 8);
	//file to storage origin data
	fp = fopen(argv[1], "rb");
	//file to storage encrytion data
	fp_w = fopen(argv[2], "wb");
	if(fp == NULL) {
		printf("Open file error!\n");
		return 1;
	}
	if(fp_w == NULL) {
		printf("Open file error!\n");
		return 1;
	}

	//set your key and get sub_key
	printf("Please enter your key : \n$ ");
	scanf("%s", key);
	get_sub_key_set(key);

	//to calculate the file size
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);

	unsigned char* origin_data = (unsigned char*)malloc(file_size*sizeof(unsigned char));
	int block_num = file_size/8;
	int the_last_block_size = file_size%8;
	int count = 0;

	//printf("file size %d\n", file_size);
	printf("***********************************************\n");
	printf("*New we read data from origin file to encrypt.*\n");
	printf("*The origin data is :                         *\n");
	printf("***********************************************\n");

	fread(origin_data, 1, file_size, fp);
	printf("%s\n", origin_data);
	//set point to begin
	rewind(fp);
	//read data from file and encrytion
	//everytime read a block with 8 bytes
	while(fread(buffer, 1, 8, fp)) {
		count++;
		//case a block is 64bits
		if(count <= block_num) {
			solution(buffer, target, 0);
		} else { //case a block is not 64bits, we expend it
			int left = 8 - the_last_block_size;
			memset(buffer + the_last_block_size, (unsigned char)left, left);
			solution(buffer, target, 0);
		}
		fwrite(target, 1, 8, fp_w);
	}
	//case the last block is 64bits
	if(the_last_block_size == 0) {
		memset(buffer, '8', 8);
		solution(buffer, target, 0);
		fwrite(target, 1, 8, fp_w);
	}
	printf("\n");
	fclose(fp_w);
	fclose(fp);


	//Decrypt part
	memset(target, 0, 8);
	fp = fopen(argv[1], "wb");
	fp_w = fopen(argv[2], "rb");
	if(fp == NULL) {
		printf("Open file error!\n");
		return 1;
	}
	if(fp_w == NULL) {
		printf("Open file error!\n");
		return 1;
	}

	printf("*************************************************************************************\n");
	printf("*New we read data from target file to decrypt. After decrypt, we get the origin text*\n");
	printf("*The origin data is :                                                               *\n");
	printf("*************************************************************************************\n");
//	printf("The ciphertext is : \n");
	fseek(fp_w, 0, SEEK_END);
	file_size = ftell(fp_w);
	rewind(fp_w);
	/*
	unsigned char* de_data = (unsigned char*)malloc(file_size*sizeof(char));
	//memset(de_data, 0, file_size);
	memset(de_data, 0, file_size);
	//printf("%d\n", file_size);
	fread(de_data, 1, file_size, fp_w);
	printf("%s\n", de_data);
	rewind(fp_w);
	*/
	int last = 0;
	count = 0;
	block_num = file_size/8;

	//printf("%d\n", file_size);

	//read block from file
	while(fread(buffer, 1,8,fp_w)) {
		//printf("%s", buffer);
		count++;
		//case a block is the last block, some data is not the origin data
		if(count == block_num) {
			solution(buffer, target, 1);
			last = target[7];

			//the last number is not 8, we delete some data we add in encryption
			if(last < 8) {
				fwrite(target, 1, 8-last, fp);
				//printf("%s", buffer);
			}
		}

		if(count < block_num) {
			solution(buffer, target, 1);
			fwrite(target, 1, 8, fp);
			//printf("%s", buffer);
		}
		//printf("%lu\n", sizeof(buffer));
		
	}

	fclose(fp);
	fclose(fp_w);

	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);
	
	//printf("last %d \n", last);
	unsigned char* temp = (unsigned char*)malloc((file_size)*sizeof(unsigned char));
	memset(temp, 0, file_size);
	fread(temp, 1, file_size, fp);
	printf("%s\n\n", temp);	

	fclose(fp);
	free(target);
	free(buffer);
	free(key);
	free(origin_data);
	//fclose(fp_w);

	return 0;
}