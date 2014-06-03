#include <stdio.h>
#include <stdint.h>

#define DIMENSION 8

static int i = 0; //identify each processor
static uint32_t *p = (uint32_t *)0xFFFFFFFF;

int m1[DIMENSION][DIMENSION]={  0, 1, 2, 3, 4, 5, 6, 7,
				8, 9, 10, 11, 12, 13, 14, 15,
				16, 17, 18, 19, 20, 21, 22, 23,
				24, 25, 26, 27, 28, 29, 30, 31,
				32, 33, 34, 35, 36, 37, 38, 39,
				40, 41, 42, 43, 44, 45, 46, 47,
				48, 49, 50, 51, 52, 53, 54, 55,
				56, 57, 58, 59, 60, 61, 62, 63};

int m2[DIMENSION][DIMENSION]={  0, 1, 2, 3, 4, 5, 6, 7,
				8, 9, 10, 11, 12, 13, 14, 15,
				16, 17, 18, 19, 20, 21, 22, 23,
				24, 25, 26, 27, 28, 29, 30, 31,
				32, 33, 34, 35, 36, 37, 38, 39,
				40, 41, 42, 43, 44, 45, 46, 47,
				48, 49, 50, 51, 52, 53, 54, 55,
				56, 57, 58, 59, 60, 61, 62, 63};

int mr[DIMENSION][DIMENSION]={}; 

int main(int argc, char *arg[]){
	int block = DIMENSION/8*i, j, k, l, print=i;

	if(i< 8) *p = (uint32_t) 1 << (++i); //wake up next processor

	for ( j=block; j< block+DIMENSION/8; j++)
		for( k=0 ; k < DIMENSION; k++)
			for( l=0 ; l < DIMENSION; l++)
				mr[j][k]+=m1[j][l]*m2[l][k];
		
	if (print==7) {
		for(j=0; j<DIMENSION; j++) {
			for(k=0; k<DIMENSION; k++) {
				printf("%d ", mr[j][k]);
			}

			printf("\n");
		}
	}	

	return 0;
}


