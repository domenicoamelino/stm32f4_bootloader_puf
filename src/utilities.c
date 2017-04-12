/*
 * utilities.c
 *
 *  Created on: 03 nov 2015
 *      Author: domenicoamelino
 */
#include "utilities.h"

void HexToBin(int hex_number,uint8_t* bit_number)
{
    int max = 128;
    for(int i = 0 ; i <8 ; i++){
        bit_number [i] = (hex_number & max ) ? 1 : 0;
        max >>=1;
    }
}

void IntToBin(int val, int* binary_number,int size)
{
	int j=size-1;
	while(val!=0)
	{
		 binary_number[j]= val % 2;
		 val = val / 2;
		 j--;
	}

	//for(int k=0;k<m-1;k++) printf("%d",binary_number[k]);
}

void GenMatrix_column(int val,int* binary_number,int m)
{
	binary_number[0] = 1;
	IntToBin(val,binary_number+1,m);
}
void HexToBin_int(uint8_t hex_number,int* bit_number,int m)
{
    int max = 128;
    for(int i = 0 ; i <m ; i++){
        bit_number [i] = (hex_number & max ) ? 1 : 0;
        max >>=1;
    }
    //printf("Valore del vettore intero index ");
    //for(int i=0;i<m;i++) printf("%d",bit_number[i]);
    //printf("\n");

}

uint8_t columnresult(uint8_t* v, int* u, int n)
{
    uint8_t sum = 0;
    //printf("Fattore 1: ");
    //for(int i=0;i<n;i++) printf("%d",v[i]);
    //printf("\n Fattore 2: ");
    //for(int i=0;i<n;i++) printf("%d",u[i]);
    //printf("\n");
   for (int i = 0; i < n; i++) sum += v[i]&u[i];
    //printf("Valore somma: %d \n",sum);
    sum = sum % 2; // se è pari da zero.
    //printf("Risultato %d \n \n",sum);
    return sum;
}

void hadamard_transform(int * v,int n)
{
	for(int i=0;i<n;i++)
	{
		if(v[i]==0)
		{
			v[i]=-1;
		}
	}
}



void max_array(int* partial_vector,int* max,int* index,int h_size)
{
	for (int k=0; k<h_size; k++)
    {
		//printf("Valore %d indice %d Max attuale %d \n ",partial_vector[k],k,*max);
		 int value = ABS(partial_vector[k]);
		 int abs_max = ABS(*max);
    	 if (value>abs_max)
    	 {
    		//printf("%d \n",k);
    	    *max=partial_vector[k];
    	    *index=k;
    	 //  printf("Nuovo massimo-> %d con indice--> %d \n",*max,*index);
    	 }

    }
	//printf("Sto ritornando il valore max %d \n",*max);
}




int BinToHex(uint8_t * bit)
{
	int c = bit[0]<<7 | bit[1]<<6 | bit[2]<<5 | bit[3]<<4| bit[4]<<3 | bit[5]<<2 | bit[6]<<1 | bit[7];
	return c;
}
