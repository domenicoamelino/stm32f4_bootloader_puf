/*
 * PUF_extraction.c
 *
 *  Created on: 09 ott 2015
 *      Author: mariobarbareschi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reedmuller.h"
#include "Spongent.h"

#define RM_R 1
#define RM_M 7
int extractPUFfromMemory(uint8_t* memory, uint8_t* helper_data, uint16_t length, uint8_t* key);
