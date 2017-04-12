/*
 * hex-loader.h
 *
 *  Created on: 06 ott 2015
 *      Author: mariobarbareschi
 */

#ifndef HEX_LOADER_H_
#define HEX_LOADER_H_

#include <stdint.h>
#include <stdio.h>
#include "types.h"

enum hex_loader_error{
	EMPTY_CONTENT,
	WRONG_FORMAT,
	UNEXPECTED_EOF,
	SUCCESS_PARSING,
	CHECKSUM_FAILED
};

typedef enum hex_loader_error hex_loader_error_t;

enum hex_record_types{
	DATA= 0x00,
	END_OF_HEX = 0x01,
	EXTENDED_SEGMENT_ADDRESS = 0x02,
	START_SEGMENT_ADDRESS = 0x03,
	EXTENDED_LINEAR_ADDRESS = 0x04,
	START_LINEAR_ADDRESS = 0x05
};

typedef struct{
	uint16_t upper_address;
	uint32_t length;
	uint32_t pc;
} hex_data;

typedef enum hex_record_types hex_record_types_t;

hex_loader_error_t interpretRecord(char * record, uint16_t length, hex_data* hex);
//hex_loader_error_t interpretRecord(Buffer * buffer, uint16_t length, hex_data* hex);
int hexstring2byte(char*, uint8_t *);
int hexstring2bytearray(char*, uint8_t*, int);



#endif /* HEX_LOADER_H_ */
