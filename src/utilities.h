/*
 * utilities.h
 *
 *  Created on: 03 nov 2015
 *      Author: domenicoamelino
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#define ABS(x) ((x) > 0) ? (x) : -(x);


#include <stdio.h>
#include <stdint.h>
#include "reedmuller.h"

void HexToBin(int hex_number, uint8_t* bit_number);
void IntToBin(int val, int* binary_number,int size);
void GenMatrix_column(int val,int* binary_number,int m);
void HexToBin_int(uint8_t hex_number,int* bit_number,int);
uint8_t columnresult(uint8_t*, int*, int n);
void max_array(int* partial_vector,int* max,int* index,int h_size);
//TEST
void hadamard_transform(int * v,int n);
int new_hadamard(int** H,int size);
//SOLO PER I MIEI TEST
int BinToHex(uint8_t * bit);
#endif /* UTILITIES_H_ */
