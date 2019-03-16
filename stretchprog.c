#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp_io.h"
#include "imgstuff.h"


int main (int argc, char *argv[]){
	int rows, cols;
	int i, j;
    int min, max;
    unsigned char *picdat;

	if( argc != 5 ){
		fprintf(stderr, "usage is: %s input.bmp output.bmp min max\n", argv[0] );
		exit(1);
	}
    min = atoi( argv[3] );
    max = atoi( argv[4] );
    
    if( (min < 0 || min > 255) ||
        (max < 0 || max > 255) ||
       ( min >= max) ){
        printf("Illegal min/max input values\n");
        exit(1);
    }
	
	// Pull the image in as monochrome, not RGB
	input_bmp(argv[1], &cols, &rows, &picdat, MONO);
 

	fprintf(stderr, "rows = %d    cols = %d \n", rows, cols);
    fprintf(stderr, "min = %d    max = %d\n", min, max);
    
    for (i=0; i<5; i++){
        printf("%u\n", picdat[mi(2, i, cols)]);
    }
    
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            if (picdat[mi(i, j, cols)] <= min) picdat [mi(i, j, cols)] = 0;
            if (picdat[mi(i, j, cols)] >= max) picdat [mi(i, j, cols)] = 255;
            else{
                picdat[mi(i, j, cols)] =
                  clip_double(   (255.0/(max - min)) * (picdat[mi(i, j, cols)] - min)    );
            }
        }
    }
    for (i=0; i<5; i++){
        printf("%u\n", picdat[mi(2, i, cols)]);
    }
    output_bmp(argv[2], cols, rows, picdat, MONO);
    
        

	free(picdat);
}
