/*
 * types.h
 *
 *  Created on: 10/giu/2014
 *      Author: HyperText
 */

#include "stm32f4xx.h"

#ifndef TYPES_H_
#define TYPES_H_

/***
 *      ____   _    _  ______  ______  ______  _____
 *     |  _ \ | |  | ||  ____||  ____||  ____||  __ \
 *     | |_) || |  | || |__   | |__   | |__   | |__) |
 *     |  _ < | |  | ||  __|  |  __|  |  __|  |  _  /
 *     | |_) || |__| || |     | |     | |____ | | \ \
 *     |____/  \____/ |_|     |_|     |______||_|  \_\
 *
 *
 */

#define BUFFER_SIZE 1200
//#define BUFFER_PROTECTION 1

typedef struct Buffer {
	uint16_t head;
	uint16_t tail;
	uint16_t count;
	uint8_t content[BUFFER_SIZE];
} Buffer;

void initBuffer(Buffer *);
uint8_t isBufferEmpty(Buffer *);
uint8_t isBufferFull(Buffer *);
void writeBuffer(Buffer *, uint8_t);
uint8_t readBuffer(Buffer *);
uint64_t readBuffer8(Buffer *);
uint8_t readBufferNoConsume(Buffer * buffer);

#endif /* TYPES_H_ */
