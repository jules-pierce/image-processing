#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char *argv[] ){
	int i, j;
	unsigned int start_seed;
    unsigned char r[256], g[256], b[256];
    int rows, cols;
    unsigned char *picdat;
    
    if ( argc != 4){
        fprintf( stderr, "usage is: %s input.bmp output.bmp start_seed", argv[0]);
        exit (1);
    }

    printf("RAND_MAX= %u\n", RAND_MAX);
    start_seed = atoi( argv[3] );
	srand( start_seed );
    //printf ("Made it to here\n");

    
    for (i = 0; i < 256; i++){
        r[i] = rand () % 256;
        g[i] = rand () % 256;
        b[i] = rand () % 256;
    }
    
    
    input_bmp (argv[1], &cols, &rows, &picdat, RGB);
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            picdat [ri (i, j, cols)] = r[picdat [ri (i, j, cols)]];
            picdat [gi (i, j, cols)] = g[picdat [gi (i, j, cols)]];
            picdat [bi (i, j, cols)] = b[picdat [bi (i, j, cols)]];
        }
    }
    output_bmp (argv[2], cols, rows, picdat, RGB);
    free (picdat);

	}

