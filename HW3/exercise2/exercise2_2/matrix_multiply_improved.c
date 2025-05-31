#include <stdlib.h>
void matrix_multiply(int *a, int *b, int *output, int i,
                           int k, int j) {
    int* b_trans = (int*)malloc(sizeof(int) * j * k);
    int blocks = 8;
    for(int I = 0; I < k; I += blocks){
	    for(int J = 0; J < j; J += blocks){
		    for(int y = I; y < I+blocks; y++){
			    for(int x = J; x < J+blocks; x++){
				    if((x < j)&&(y < k)){
					    b_trans[x*k + y] = b[y*j + x];
				    }
			    }
		    }
	    }
    }
    for(int x = 0; x < i; x++){ //row
	    for(int y = 0; y < j; y++){ //column
		    int sum = 0;
		    for(int  z = 0; z < k; z++){
			    sum += a[x*k + z] * b_trans[y*k + z];
		    }
		    output[x*j + y] = sum;
	    }
    }
}
