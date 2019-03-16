#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char *argv[] ){
	int i, j;
    int rows, cols;
    unsigned char *picdat, *picdat2;
    double *sd;
    double min, max;
    double h, v;
    double delta;
    double thresh;
    
    if ( argc != 5){
        fprintf( stderr, "usage is: %s in.bmp percentage out1.bmp out2.bmp\n", argv[0]);
        exit (1);
    }
    //printf ("check\n");

    input_bmp (argv [1], &cols, &rows, &picdat, MONO);
    
    picdat2 = (unsigned char*) malloc (rows * cols * sizeof(unsigned char));
    sd = (double*) malloc (rows * cols * sizeof(double));
    
    h = 0;
    v = 0;

    for (i = 1; i < rows-1; i ++){
        for (j = 1; j < cols-1; j++){
            h = picdat [mi(i-1, j+1, cols)] - 
						    picdat [mi (i-1, j-1, cols)] + 
								2 * (  picdat [mi (i, j+1, cols)] -
								picdat [mi (i, j-1, cols)]   ) +
								picdat [mi (i+1, j+1, cols)] -
								picdat [mi (i+1, j-1, cols)];

            v = picdat [mi (i-1, j-1, cols)] - 
						    picdat [mi (i+1, j-1, cols)] + 
								2 * (picdat [mi (i-1, j, cols)] - 
								     picdat [mi (i+1, j, cols)]) + 
										 picdat [mi (i-1, j+1, cols)] - 
										 picdat [mi (i+1, j+1, cols)];
            sd [mi (i, j, cols)] = sqrt ((h*h) + (v*v));
        }
    }

    for (j = 0; j < cols; j++){
        sd [mi (0, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        sd [mi (i, 0, cols)] = 0;
    }
    for (j = 0; j < cols; j++){
        sd [mi (rows-1, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        sd [mi (i, cols-1, cols)] = 0;
    }

    min = 1e50;
    max = -1e50;
    for (i = 1; i < (rows-1); i++){
        for (j = 1; j < (cols-1); j++){
            if (sd[mi (i, j, cols)] < min) min = sd[mi (i, j, cols)];
            if (sd[mi (i, j, cols)] > max) max = sd[mi (i, j, cols)];
        }
    }
    
    delta = (max - min) /255.0;
    printf ("min = %10.4lf max = %10.4lf  delta = %10.4lf\n", min, max, delta);
    for (i = 1; i < rows-1; i++){
        for (j = 1; j < cols-1; j++){
            picdat2 [mi (i, j, cols)] = clip_double(
						         (sd[mi (i, j, cols)] - min)/delta
										                               );
        }
    }
    
    for (j = 0; j < cols; j++){
        picdat2 [mi (0, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        picdat2 [mi (i, 0, cols)] = 0;
    }
    for (j = 0; j < cols; j++){
        picdat2 [mi (rows-1, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        picdat2 [mi (i, cols-1, cols)] = 0;
    }
   
    output_bmp (argv [3], cols, rows, picdat2, MONO);
    
    thresh = min + (atof (argv [2])) * (max - min);
    for (i = 1; i < (rows-1); i++){
        for (j = 1; j < (cols-1); j++){
            if (sd [mi (i, j, cols)] > thresh){
                picdat2 [mi (i, j, cols)] = 255;
            }
            else {
                picdat2 [mi (i, j, cols)] = 0;
            }
        }
    }
    
    for (j = 0; j < cols; j++){
        picdat2 [mi (0, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        picdat2 [mi (i, 0, cols)] = 0;
    }
    for (j = 0; j < cols; j++){
        picdat2 [mi (rows-1, j, cols)] = 0;
    }
    for (i = 0; i < rows; i++){
        picdat2 [mi (i, cols-1, cols)] = 0;
    }
    
    output_bmp (argv [4], cols, rows, picdat2, MONO);
    
    free (picdat);
    free (picdat2);
    free (sd);
}



