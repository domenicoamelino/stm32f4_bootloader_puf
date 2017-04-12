/*
 * present.h
 *
 *  Created on: 23 mag 2016
 *      Author: Damelino
 */

#ifndef PRESENT_H_
#define PRESENT_H_

#include <sys/types.h>
#include <stdint.h>



#define high1_64(h1in) 			( (uint64_t)h1in >> 63 )	//msb as lsb
#define high4_64(h4in) 			( (uint64_t)h4in >> 60 )	//4 msb as lsb
#define rotate1l_64(r1lin)	 ( high1_64(r1lin) | ( r1lin << 1 ) )	//input rotated left (1x)
#define rotate4l_64(r4lin)	 ( high4_64(r4lin) | ( r4lin << 4 ) )	//input rotated left (4x)

void present_encode(uint64_t * state, uint64_t keylow , uint64_t keyhigh);
void present_decode(uint64_t * state, uint64_t keylow , uint64_t keyhigh);


#endif /* PRESENT_H_ */
