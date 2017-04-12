/*
 * reedmuller.c
 *
 *  Created on: 03 nov 2015
 *      Author: domenicoamelino
 */

#include "reedmuller.h"
#include "utilities.h"



/*
 * input -> input byte vector
 * length -> input byte length
 * m -> the second parameter of reed muller implementation
 */

uint8_t  encode(uint8_t* input,int* result)
{
	int num_blocks,i, pos_i,j;
	int pos_r;
	int padding = 0;
	int input_length;

	uint32_t generator_column = 1;
	generator_column = generator_column<<M;

	//printf("Generator Column ->%d \n",generator_column);
	//Input vector (byte) is trasformed into a bit matrix (each bit element occupies one array field (8 bit)
	uint8_t input_vector [LENGTH]; //malloc
	for(i=0;i<BYTE_LENGTH;i++)	HexToBin(input[i],input_vector+i*8);

	/* -- TESTING --*/
	//printf("Input vector originale \n");
	//for(i=0;i<LENGTH;i++) printf("%d",input_vector[i]);
	//printf("\n");

	input_length=LENGTH;
	num_blocks = LENGTH/(M+1); // required block number for the next operations
	//printf("Num Blocks %d \n", num_blocks);
	//Input vector padding verification
	if(LENGTH%(M+1))//
	{
		//printf("C'è bisogno del padding \n");
		num_blocks=num_blocks+1;
		padding = ((num_blocks)*(M+1)-LENGTH); // Very bad multiplication!
		input_length = padding+LENGTH;
		// Input vector reallocation if padding is required.
		//input_vector = (uint8_t*) realloc(input_vector,input_length*sizeof(uint8_t)); //riflettere anche sull'uso di questa malloc
		for(i=LENGTH;i<input_length;i++) input_vector[i] = 0;
	}

	/* -- TESTING --*/
	//printf("Input vector post padding \n");
	//for(i=0;i<input_length;i++) printf("%d",input_vector[i]);
	//printf("\n");

	//Result vector memory allocation -- Its deallocation is made outside..is correct? TODO
	//result = (uint8_t*) malloc(num_blocks*generator_column*sizeof(uint8_t));

	//Don't erase this printf for now.
	//printf("Result Length %d \n",num_blocks*generator_column);
	//num_blocks = 22;

	//Starting che calculation cycle
	for(j=0,pos_i=0,pos_r=0;j<num_blocks;j++)
	{
		for(i=0;i<generator_column;i++)
		{
		  //Single column of generation matrix creation/allocation.
		  int generator_vector[M+1];
		  for(int k=0;k<M+1;k++) generator_vector[k] = 0; // i do the static calloc by myself.

		  //This function create automatically a right generation matrix column as bit vector
		  GenMatrix_column(i,generator_vector,M);
		  /* TESTING */
		  //printf("Vettore generato: --> ");
		  //for(int k=0;k<M+1;k++) printf(" %d \n", generator_vector[k]);
		  //printf("\n");
		  //printf("Verifica scorrimento corretto del vettore input \n");
		  //for(int k=0;k<M+1;k++) printf("%x \n", *(input_vector+pos_i+k));


		  result[pos_r+i] = columnresult(input_vector+pos_i, generator_vector, M+1); //one result element calculation
		   // generator_vector memory deallocation
		}
		//Pointer update for next cycle.
		pos_r = pos_r +i;
		pos_i = pos_i+(M+1);
	}

	return 0;
}

uint8_t decode(int* input_vector,uint8_t* result)
{
	//Hadamard square matrix size


	//This variable are created as long but maybe type "int" is enough
	long pos_i=0;
	long pos_r=0;

	//Hsized square Hadamard Matrix Generation
	// Determinare QUI la struttura DATI!!!!
	int h[H_SIZE][H_SIZE];
	//led_on(LED_BLUE);
	hadamard(h,H_SIZE);
	//led_on(LED_RED);


	//la dimensione in termini di BIT dell'ingresso.

	/*
	 * Number of blocks requires for next operations.
	 *  This division have not remainder because length and h_sizre are always power of 2.
	*/

	int num_blocks = RESULT_LENGTH/H_SIZE; // PRESTO DIVENTERà UNA DEFINE
	//printf("NumBlocks decode 1-> %d \n",num_blocks);
	//Result vector allocation -- bad multiplication -- the deallocation is made outside..is bad thing? TODO
	//result = (uint8_t*) malloc(num_blocks*(m+1)*sizeof(uint8_t));


	/* -- TESTING --
	 printf("Dimensione valore result : %d \n",num_blocks*(m+1));
	 printf("Dimensione blocchi %d \n",num_blocks);
	*/

	/* Input byte vector transformation, a very necessary bad operation. One bit occupies 8bit-field of the array.
	   The first step is memory allocation, the second the transformation. */



	//Vector transfor
	hadamard_transform(input_vector,RESULT_LENGTH);
	/*TODO la dinamica qui sopra può essere cambiata spostando l'inserimento del meno 1
	       durante i calcoli.
	*/
	//printf("Input trasformato hadamard \n");
	//for(int i=0;i<length;i++) printf("%d",input_vector[i]);

	// Max and index, used for hadamard decoding operations, are initialized as integer.
	int max;
	int index;

	//printf("NumBlocks decode 2-> %d \n",num_blocks);

	for(int i=0;i<num_blocks;i++)
	{
		max=0;
		//int* partial_vector = (int*) malloc(h_size*sizeof(int));
		int partial_vector [H_SIZE];
		for(int k=0;k<H_SIZE;k++) partial_vector[k]=0;

		/* -- TESTING
		printf("Vettore input parziale blocco %d \n",i);
		for(int k=0;k<h_size;k++) printf("%d ",input_vector[k+pos_i]);
		printf("\n \n \n"); */
		dotproduct(partial_vector,input_vector+pos_i,h,H_SIZE);

		/* -- TESTING
		  for(int j=0;j<h_size;j++) printf("%d\n", partial_vector[j]);
		  printf("\n \n \n");
		*/

		//Dot product max value and relative index evaluation
		max_array(partial_vector,&max,&index,H_SIZE);

		//Buffer memory allocation. This vector stores binary value (into integer vector) at the moment.
		//int * buffer = calloc(m,sizeof(int));
		int buffer[M];
		for(int k=0;k<M;k++) buffer[k]=0;

		//Index 8bit-binary vector transformation
		IntToBin(index,buffer,M);
		/* TESTING
		 printf("%d\n",index);
		 for(int k=0;k<m;k++) printf("%d",buffer[k]);
		 printf("\n"); */

		//Result value estimation and storing
		for(int k=0,j=pos_r+1;k<M;k++,j++) result[j]=buffer[k];
		if(max>0) result[pos_r] = 1;
		else result[pos_r] = 0;

		//Pointer update for the next cycle
		pos_i = pos_i + H_SIZE;
		pos_r = pos_r + M+1;

	}

	return 0;
}


int hadamard(int h[H_SIZE][H_SIZE])
{
	//int **h = (int**) calloc(n, sizeof(int*));


	int ii, xx, yy;

	h[0][0]=1;


	for(ii=2; ii<=H_SIZE; ii*=2) {
	    //Top right quadrant.
	    for(xx=0; xx<(ii/2); xx++) {
	        for(yy=(ii/2); yy<ii; yy++){
	            h[xx][yy]=h[xx][yy-(ii/2)];
	        }
	    }
	    //Bottom left quadrant.
	    for(yy=0; yy<(ii/2); yy++) {
	        for(xx=(ii/2); xx<ii; xx++) {
	            h[xx][yy]=h[xx-(ii/2)][yy];
	        }
	    }
	    //Bottom right quadrant, inverse of other quadrants.
	    for(xx=(ii/2); xx<ii; xx++) {
	        for(yy=(ii/2); yy<ii; yy++) {
	            h[xx][yy]=h[xx-(ii/2)][yy-(ii/2)];
	            if(h[xx][yy]==1) {
	                h[xx][yy]=-1;
	            }
	            else {
	                h[xx][yy]=1;
	            }
	        }
	    }
	}

	return 0;
}

void dotproduct(int* result,int* v,int u[H_SIZE][H_SIZE],int n)
{
	int sum;


	for(int i=0;i<n;i++)
	{
		sum = 0;
		for(int j=0;j<n;j++)
		{
			sum +=v[j]*u[i][j];
		}
		result[i]=sum;
	}

	//printf("Risultato \n");
	//for(int i;i<n;i++) printf("%d \n",result[i]);
	//printf("\n");

}

