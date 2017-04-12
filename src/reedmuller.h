/*
 * reedmuller.h
 *
 *  Created on: 03 nov 2015
 *      Author: domenicoamelino
 */

#ifndef REEDMULLER_H_
#define REEDMULLER_H_
#include <stdio.h>
#include "utilities.h"
#include <stdint.h>

#define  M 7
#define  LENGTH 176
#define  BYTE_LENGTH 22 // This value is the size of the input vector  with padding (for ENCODE) and the output for decode.
#define  RESULT_LENGTH 2816 // This value is the size of the output vector for encode and input for encode.
#define  H_SIZE 128// 2^M
uint8_t  encode(uint8_t* input,int* result);
uint8_t decode(int* input,uint8_t* msg);
void dotproduct(int* result,int* v,int u[H_SIZE][H_SIZE],int n);
#endif /* REEDMULLER_H_ */
