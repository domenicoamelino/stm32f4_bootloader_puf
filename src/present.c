/*
 * present.c
 *
 *  Created on: 23 mag 2016
 *      Author: Damelino
 */

#include "present.h"

const uint16_t invsBox4[] = {0x5,0xe,0xf,0x8,0xC,0x1,0x2,0xD,0xB,0x4,0x6,0x3,0x0,0x7,0x9,0xA};
const uint64_t sBox4[] = {0xc,0x5,0x6,0xb,0x9,0x0,0xa,0xd,0x3,0xe,0xf,0x8,0x4,0x7,0x1,0x2};


void present_encode(uint64_t * state, uint64_t keylow , uint64_t keyhigh)
{
	int i=1;
//	Variables sBox
	uint16_t sBoxValue;
	int sBoxNr=0;
//	Variables pLayer
	uint64_t temp;
//  Variables key scheduling
	uint64_t subkey[32];
	int keyindex;
	//	****************** Key Scheduling **********************
			int round;
			for(round=0;round<32;round++)
			{
				subkey[round] = keyhigh;							//61-bit left shift
				temp = keyhigh;
				keyhigh <<= 61;
				keyhigh |= (keylow<<45);
				keyhigh |= (temp>>19);
				keylow = (temp>>3)&0xFFFF;

				temp = keyhigh>>60;									//S-Box application
				keyhigh &=	0x0FFFFFFFFFFFFFFF;
				temp = sBox4[temp];
				keyhigh |= temp<<60;

				keylow ^= ( ( (round+1) & 0x01 ) << 15 );			//round counter addition
				keyhigh ^= ( (round+1) >> 1 );
			}
	//	****************** End Key Scheduling ******************
	//	****************** Encryption **************************
			for(i=0;i<31;i++)
			{
	//	****************** addRoundkey *************************
				*state ^= subkey[i];
	//	****************** End addRoundkey *********************
	//	****************** sBoxLayer ***************************
				for(sBoxNr=0;sBoxNr<16;sBoxNr++)
				{
					sBoxValue = *state & 0xF;						//get lowest nibble
					*state &=	0xFFFFFFFFFFFFFFF0;					//kill lowest nibble
					*state |=	sBox4[sBoxValue];					//put new value to lowest nibble (sBox)
					*state = rotate4l_64(*state);						//next(rotate by one nibble)
				}
	//	****************** End sBoxLayer ***********************
	//	****************** pLayer ******************************
				temp = 0;
				int k;
				for(k=0;k<64;k++)
				{
					int position = (16*k) % 63;						//Arithmentic calculation of the p-Layer
					if(k == 63)										//Exception for bit 63
						position = 63;
					temp |= ((*state>>k) & 0x1) << position;			//result writing
				}
				*state=temp;
	//	****************** End pLayer **************************
			}
	//	****************** addRoundkey (Round 31) **************
			*state ^= subkey[31];
	//	****************** End addRoundkey (Round 31) **********
			//	****************** End Encryption **********************
}

void present_decode(uint64_t * state, uint64_t keylow , uint64_t keyhigh)
{
	int i=1;
//	Variables sBox
	uint16_t sBoxValue;
	int sBoxNr=0;
//	Variables pLayer
	uint64_t temp;
//  Variables key scheduling
	uint64_t subkey[32];
	int keyindex;
	int round;
	for(round=0;round<32;round++)
	{
		subkey[round] = keyhigh;							//61-bit left shift
		temp = keyhigh;
		keyhigh <<= 61;
		keyhigh |= (keylow<<45);
		keyhigh |= (temp>>19);
		keylow = (temp>>3)&0xFFFF;

		temp = keyhigh>>60;									//S-Box application
		keyhigh &=	0x0FFFFFFFFFFFFFFF;
		temp = sBox4[temp];
		keyhigh |= temp<<60;

		keylow ^= ( ( (round+1) & 0x01 ) << 15 );			//round counter addition
		keyhigh ^= ( (round+1) >> 1 );
	}
//	****************** End Key Scheduling ******************
//	****************** Decryption **************************
	keyindex = 31;
	for(i=0;i<31;i++)
	{
//	****************** addRoundkey *************************
		*state ^= subkey[keyindex];
		keyindex--;
//	****************** End addRoundkey *********************
//	****************** pLayer ******************************
		temp = 0;
		int k;
		for(k=0;k<64;k++)
		{
			int position = (4*k) % 63;						//Arithmentic calculation of the p-Layer
			if(k == 63)										//Exception for bit 63
				position = 63;
			temp |= ((*state>>k) & 0x1) << position;			//result writing
		}
		*state=temp;
//	****************** End pLayer **************************
//	****************** sBoxLayer ***************************
		for(sBoxNr=0;sBoxNr<16;sBoxNr++)
		{
			sBoxValue = *state & 0xF;						//get lowest nibble
			*state &=	0xFFFFFFFFFFFFFFF0;					//kill lowest nibble
			*state |=	invsBox4[sBoxValue];				//put new value to lowest nibble (sbox)
			*state = rotate4l_64(*state);						//next(rotate by one nibble)
		}
//	****************** End sBoxLayer ***********************
	}
//	****************** addRoundkey (Round 31) **************
	*state ^= subkey[0];
//	****************** End addRoundkey (Round 31) **********

//	****************** End Decryption **********************
}
