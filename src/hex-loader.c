/*
 * hex-loader.c
 *
 *  Created on: 06 ott 2015
 *      Author: mariobarbareschi
 */

#include "hex-loader.h"
#include "stdlib.h"

uint16_t error_hex = 0;

int hexstring2bytearray(char* hex, uint8_t* buf, int length){
	int i;
	for(i=0; i<length; i++){
		if(hexstring2byte(&hex[2*i], &buf[length-i-1])==-1){
			return -1;
		}
	}
	return 0;
}

int hexstring2byte(char* hex, uint8_t *buf){
	*buf = 0;
	int i;
	for(i=0; i<2; i++){
		if(hex[i] >= '0' && hex[i] <= '9'){
			*buf |= (hex[i]-'0')<<4*(1-i);
		}else if(hex[i] >= 'A' && hex[i]<= 'F'){
			*buf |= (hex[i]-55)<<4*(1-i);
		}else if(hex[i] >= 'a' && hex[i]<= 'f'){
			*buf |= (hex[i]-97)<<4*(1-i);
		}else{
			return -1;
		}
	}
	return 0;
}

hex_loader_error_t interpretRecord(char * record, uint16_t length, hex_data* hex){

	if(!length || record[0] == '\n' || record[0] =='\r'){
		return EMPTY_CONTENT;
	}
	if(length < 11 || record[0] != ':'){
		return WRONG_FORMAT;
	}
	uint8_t checksum=0;
	uint8_t buf;
	int i;
	for(i=1; i<length-1; i+=2){
		if(hexstring2bytearray(record+i, &buf, 1)!=0){
			return WRONG_FORMAT;
		}
		checksum += buf;
	}

	if(checksum != 0){
		return CHECKSUM_FAILED;
	}

	uint8_t* memory_ptr;
	uint8_t record_ptr = 1;
	uint8_t record_length;
	uint16_t address;
	hex_record_types_t type;
	/*if(sscanf(record+record_ptr, "%2x%4x%2x%*s", &record_length, &address, &type)!=3){
		return WRONG_FORMAT;
	}*/
	if(hexstring2bytearray(record+record_ptr, &buf, 1)!=0){
			return WRONG_FORMAT;
	}
	record_length = buf;
	record_ptr+=2;
	if(hexstring2bytearray(record+record_ptr, &address, 2)!=0){
			return WRONG_FORMAT;
	}
	record_ptr+=4;
	if(hexstring2bytearray(record+record_ptr, &buf, 1)!=0){
			return WRONG_FORMAT;
	}
	type = buf;
	record_ptr+=2;
	if(length >= record_length+record_ptr){
		switch(type){
		case DATA:
			memory_ptr = (uint8_t*) (((hex->upper_address & 0x0000FFFF) << 16) | address);
			for(i=0; i<record_length; i++){
				if(i==7)
				{
					int kappa;
				}
				if(hexstring2bytearray(record+record_ptr, memory_ptr, 1)!=0){
					return WRONG_FORMAT;
				}
				memory_ptr+=1;
				record_ptr+=2;
			}
			break;
		case END_OF_HEX:
			return SUCCESS_PARSING;
			break;
		case EXTENDED_SEGMENT_ADDRESS:
			break;
		case START_SEGMENT_ADDRESS:
			break;
		case EXTENDED_LINEAR_ADDRESS:
			if(record_length != 2){
				return WRONG_FORMAT;
			}
			hex->upper_address = 0;
			for(i=0; i<2; i++){
				if(hexstring2bytearray(record+record_ptr, &buf, 1)!=0){
					return WRONG_FORMAT;
				}
				hex->upper_address|=buf<<(8*(1-i));
				record_ptr+=2;
			}
			break;
		case START_LINEAR_ADDRESS:
			if(record_length != 4){
				return WRONG_FORMAT;
			}
			hex->pc=0;
			for(i=0; i<4; i++){
				if(hexstring2bytearray(record+record_ptr, &buf, 1)!=0){
					return WRONG_FORMAT;
				}
				hex->pc|=buf<<(8*(3-i));
				record_ptr+=2;
			}
			break;
		}
	}else{
		return WRONG_FORMAT;
	}
	return SUCCESS_PARSING;
}
