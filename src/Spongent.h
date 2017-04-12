#ifndef _SPONGENT_H_
#define _SPONGENT_H_

#define rate		128
#define capacity	256
#define hashsize	128
#define nRounds		195
#define version		128256128

#define R_SizeInBytes 	(rate / 8)
#define nBits 			(capacity + rate)
#define nSBox 			nBits/8

typedef unsigned char 		BitSequence;
typedef uint16_t 	DataLength;

typedef unsigned long long int bit64;
typedef unsigned long	bit32;
typedef unsigned short	bit16;
typedef unsigned char	bit8;

#define GET_BIT(x,y) (x >> y) & 0x1

typedef enum { HASH_SUCCESS = 0, HASH_FAIL = 1, BAD_HASHBITLEN = 2 } HashReturn;

typedef struct {
 	BitSequence value[nSBox];					/* current Spongent state */
 	BitSequence messageblock[R_SizeInBytes];	/* message block to be input/output */
	int remainingbitlen;						/* remaining data length */
	int hashbitlen;								/* # of hashed bits so far */
} hashState;

HashReturn SpongentHash(const BitSequence *data, DataLength databitlen, BitSequence *hashval);
HashReturn Init(hashState *state, BitSequence *hashval);
HashReturn Absorb(hashState *state);
HashReturn Squeeze(hashState *state);
HashReturn Pad(hashState *state);

int Pi(int i);
void pLayer(hashState *state);
void Permute(hashState *state);

bit16 lCounter(bit16 lfsr);
bit16 retnuoCl(bit16 lfsr);

#endif /* spongent.h */












