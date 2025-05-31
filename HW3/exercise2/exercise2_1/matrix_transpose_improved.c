void matrix_transpose(int n, int *dst, int *src) {
    int blocks = 8;
    for(int i = 0; i < n; i+= blocks){
	    for(int j = 0; j < n; j+= blocks){
		    for(int y = i; y < i+blocks; y++){
			    for(int x = j; x < j+blocks; x++){
				    if((x < n) && (y < n)){
					    dst[y + x*n] = src[x + y*n];
				    }
			    }
		    }
	    }
    }
    }
