#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp_io.h"
#include "imgstuff.h"


int main (int argc, char *argv[]){
	int cols, rows, scols, srows;
	int i, j;
    unsigned char *picdat, *spicdat;
    int sr, sc;

	if( argc != 6 ){
		fprintf(stderr, "usage is: %s small_pic.bmp big_pic.bmp  output.bmp start_rows start_cols\n", argv[0] );
		exit(1);
	}
    
    sr = atoi (argv[4]);
    sc = atoi (argv[5]);
	
	input_bmp (argv[1], &scols, &srows, &spicdat, RGB);
    input_bmp (argv[2], &cols, &rows, &picdat, RGB);
    
    for (i = 0; i < srows; i++){
        for (j = 0; j < scols; j++){
            picdat [ri ((sr + i),(sc + j), cols)] = spicdat [ri (i, j, scols)];
            picdat [gi ((sr + i),(sc + j), cols)] = spicdat [gi (i, j, scols)];
            picdat [bi ((sr + i),(sc + j), cols)] = spicdat [bi (i, j, scols)];
        }
    }
    
    output_bmp(argv[3], cols, rows, picdat, RGB);
    
	free(picdat);
}
