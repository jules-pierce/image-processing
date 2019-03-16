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
	double new_y, new_x;
	double x, y;
	double theta;
	unsigned char *picdat, *picdat_r;

	if( argc != 4 ){
		fprintf(stderr, "usage is: %s input.bmp output.bmp theta_deg\n", argv[0] );
		exit(1);
	}
    
  theta = atof (argv [3]);
	theta *= M_PI/180.0;
  printf ("hi: theta_deg = %lf  theta_rad = %lf\n", atof(argv[3]), theta);
	input_bmp(argv[1], &cols, &rows, &picdat, RGB);
  printf ("here\n");

	picdat_r = (unsigned char*)malloc(3*rows*cols*sizeof(unsigned char) );
    
	for (i = 0; i < rows; i++){
		for (j = 0; j < cols; j++){
				x = j - cols/2;
				y = rows/2 - i;
				new_x = x * cos(theta) + y * sin(theta);
				new_y = -x * sin(theta) + y * cos(theta);
				new_x += cols/2;
				new_y = rows/2 - new_y;
				new_x = floor(new_x + 0.5);
				new_y = floor(new_y + 0.5);

				if(new_x >= cols || new_x < 0 ||
				   new_y >= rows || new_y < 0 ){
					picdat_r[ ri(i, j, cols) ] = 0;
                    picdat_r[ gi(i, j, cols) ] = 0;
                    picdat_r[ bi(i, j, cols) ] = 0;
				}
				else {
					picdat_r[ ri(i, j, cols) ]=
						picdat[ri ((int)new_y, (int)new_x, cols)];
                    picdat_r[ gi(i, j, cols) ]=
                        picdat[gi ((int)new_y, (int)new_x, cols)];
                    picdat_r[ bi(i, j, cols) ]=
                        picdat[bi ((int)new_y, (int)new_x, cols)];
				}
			}
    }

	output_bmp(argv[2], cols, rows, picdat_r, RGB);
    
	free (picdat);
	free (picdat_r);
}
