#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char *argv[] ){
	int i, j;
    double x;
	unsigned int start_seed;
    double count = 0;
    double prob;
    int rows, cols;
    unsigned char *picdat;

    
    if ( argc != 5){
        fprintf( stderr, "usage is: %s start_seed prob in.bmp out.bmp\n", argv[0]);
        exit (1);
    }

    start_seed = atoi( argv[1] );
	srand( start_seed );
    prob = atof ( argv [2] );
    printf ("prob = %f\n", prob);
    input_bmp (argv [3], &cols, &rows, &picdat, RGB);
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            x = (double)rand()/ (double) RAND_MAX;
            if (x < prob){
                picdat [ri ( i, j, cols)] = 255;
                picdat [gi ( i, j, cols)] = 255;
                picdat [bi ( i, j, cols)] = 255;
            }
        }
    }
    output_bmp (argv [4], cols, rows, picdat, RGB);
    free (picdat);
}

