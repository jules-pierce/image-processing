#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp_io.h"
#include "imgstuff.h"

typedef unsigned char byte;

int main(int argc, char *argv[]){
	int rows, cols;
	int i, j;
	byte *picdat;

	if( argc != 3 ){
		fprintf(stderr, "usage is: %s input.bmp output.bmp\n", argv[0] );
		exit(1);
	}
	
	// Pull the image in as monochrome, not RGB
	input_bmp(argv[1], &cols, &rows, &picdat, MONO);

	fprintf(stderr, "rows = %d\n", rows);
	fprintf(stderr, "cols = %d\n", cols);

	// Loop over pixels in the picture and insert a white grid with spacing 32
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if( (i % 32 == 0) || (j % 32 == 0) ) picdat[mi(i, j, cols)] = 255;
		}
	}

	output_bmp(argv[2], cols, rows, picdat, MONO);

	free(picdat);
}
