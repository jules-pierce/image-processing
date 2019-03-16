#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp_io.h"
#include "imgstuff.h"


int main (int argc, char *argv[]){
	int nrows, cols, ncols, rows;
	int i, j;
    unsigned char *picdat;
    int scols, srows;

	if( argc != 7 ){
		fprintf(stderr, "usage is: %s input.bmp output.bmp start_rows start_cols number_rows number_cols\n", argv[0] );
		exit(1);
	}
	
	input_bmp(argv[1], &cols, &rows, &picdat, RGB);
    printf ("success\n");
    
    ncols = atoi (argv [6]);
    nrows = atoi (argv [5]);
    scols = atoi (argv[4]);
    srows = atoi (argv[3]);
    
    printf ("%d   %d\n", srows, rows);
    
    if (srows > rows){
        fprintf (stderr, "start row too big\n");
        exit (1);
    }

    if (scols > cols){
        fprintf (stderr, "start col too big\n");
        exit (1);
    }

    if (ncols > (cols - scols)){
        fprintf (stderr, "too many cols\n");
        exit (1);
    }

    if (nrows > (rows - srows)){
        fprintf (stderr, "too many rows\n");
        exit (1);
    }
    
    for (i = 0; i < nrows; i++){
        for (j = 0; j < ncols; j++){
            picdat [ri (i, j, ncols)] = picdat [ri ((srows + i), (scols + j), cols)];
            picdat [gi (i, j, ncols)] = picdat [gi ((srows + i), (scols + j), cols)];
            picdat [bi (i, j, ncols)] = picdat [bi ((srows + i), (scols + j), cols)];
        }
    }
    
    output_bmp(argv[2], ncols, nrows, picdat, RGB);
    
        

	free(picdat);
}
