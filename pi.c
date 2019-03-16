#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char *argv[]){
	int rows, cols;
	int i, j;
	unsigned char *picdat;
    double distance;
    unsigned int start_seed;
    int x, y;
    double in, out;
    int num_iterations;
    
    in = 0;
    out = 0;

	if( argc != 4 ){
		fprintf(stderr, "usage is: %s out_name start_seed num_iterations\n", argv[0] );
		exit(1);
	}
    
    start_seed = atoi (argv [2]);
    srand (start_seed);
    num_iterations = atoi (argv [3]);
    
    rows = 501;
    cols = 501;
    picdat = (unsigned char*) malloc (3 * rows * cols * sizeof(unsigned char));
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            picdat [ri (i, j, cols)] = 0;
            picdat [gi (i, j, cols)] = 0;
            picdat [bi (i, j, cols)] = 0;
            
            distance = sqrt ((i - 250)*(i-250) + (j-250)*(j-250));
            
            if ( distance < 250){
                picdat [ri (i, j, cols)] = 255;
                picdat [gi (i, j, cols)] = 255;
                picdat [bi (i, j, cols)] = 255;
            }
        }
    }
    
    for (i = 0; i < num_iterations; i++){
        x = floor((double)rand()/ (double)RAND_MAX * 500);
        y = floor((double)rand()/ (double)RAND_MAX * 500);
        
        distance = sqrt ((x - 250)*(x-250) + (y-250)*(y-250));
        
        //fprintf (stderr, "x = %d   y = %d\n", x, y);
        
        if (distance > 250){
            picdat [ri (x, y, cols)] = 0;
            picdat [gi (x, y, cols)] = 0;
            picdat [bi (x, y, cols)] = 255;
            out ++;
            //fprintf (stderr, "value out of circle, x = %d   y = %d\n", x, y);
        }
        
        else if (distance < 250){
            picdat [ri (x, y, cols)] = 255;
            picdat [gi (x, y, cols)] = 0;
            picdat [bi (x, y, cols)] = 0;
            //fprintf (stderr, "value in circle, x = %d   y = %d\n", x, y);
            in ++;
        }
    }
    
    fprintf (stderr, " in = %lf  out = %lf\n", in, out);
    fprintf (stderr, "pi is %lf\n", in/(in+out) * 4 );

	output_bmp(argv[1], cols, rows, picdat, RGB);

	free(picdat);
}
