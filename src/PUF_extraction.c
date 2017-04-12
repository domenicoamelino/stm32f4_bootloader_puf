/*
 * PUF_extraction.c
 *
 *  Created on: 09 ott 2015
 *      Author: mariobarbareschi
 */
#include "PUF_extraction.h"
int extractPUFfromMemory(uint8_t* memory, uint8_t* helper_data, uint16_t length, uint8_t* key){

	uint8_t result_xor[352];
	int dirty_codeword[2816];
	uint8_t secret_word_bin[176];
	uint8_t secret_word_hex[22];
	int codeword_bin[2816];
	uint8_t codeword_bin2[2816];
	uint8_t codeword_hex[352];
	int count;
	HashReturn res;
	int i;
	//memory_vector *original, *decoded, *codeword;
	//original=createMemoryVector(length);
	//original->values = (uint8_t*)memory;

	for (i = 0; i < 352; i++) {
		result_xor[i] = memory[i] ^ helper_data[i];
	}

//	for(i=0;i<352;i++) printf("%x ",result_xor[i]);
//	printf("\n");
	//decoded = decode(original, RM_R, RM_M);
	for(i=0;i<352;i++) HexToBin_int(result_xor[i], dirty_codeword+i*8,8);

	//for(i=0;i<2816;i++) printf("%d",dirty_codeword[i]);
	//printf("\n");
	decode(dirty_codeword,secret_word_bin);

	//for(i=0;i<176;i++) printf("%d",secret_word_bin[i]);
	//printf("\n");

	count=0;
	for(i=0;i<176;i+=8)
	{
		secret_word_hex[count] = BinToHex(secret_word_bin+i);
		count++;
	}
	//printf("Count = %d\n",count);
	encode(secret_word_hex,codeword_bin);

	//for(i=0;i<2816;i++) printf("%d",codeword_bin[i]);
	//printf("\n");
	//il risultato è in un vettore di 1 e 0...va convertito.

	count = 0;
	for(i=0;i<2816;i++) codeword_bin2[i] = codeword_bin[i];
	for(i=0;i<2816;i+=8)
	{
		codeword_hex[count] = BinToHex(codeword_bin2+i);
		count++;
	}
//
//	printf("Count = %d\n",count);
//	for(i=0;i<352;i++) printf("%x ",codeword_hex[i]);
//	printf("\n");
/*	unsigned int errors = 0;
	for(i=0; i< original->byteLength; i++){
		errors += __builtin_popcount(original->values[i] ^ codeword->values[i]);
	}*/
	for (i = 0; i < 352; i++) {
		result_xor[i] = codeword_hex[i] ^ helper_data[i];
		}

//	for(i=0;i<352;i++) printf("%x ",result_xor[i]);
//		printf("\n");



	/*
	for(i = 0; i<original->byteLength; i++)
	{
		key[i] = codeword->values[i];
	}
	*/

	res = SpongentHash(result_xor, length, key);

	for(i=0;i<352;i++) memory[i]=0;

	return 0;

}
