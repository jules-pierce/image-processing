#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char *argv[] ){
	int i, j, k, l;
    int rows, cols, cols2, rows2;
    unsigned char *picdat, *picdat2;
    
    if ( argc != 3){
        fprintf( stderr, "usage is: %s in.bmp out.bmp\n", argv[0]);
        exit (1);
    }

    input_bmp (argv [1], &cols, &rows, &picdat, RGB);
    
    cols2 = cols/2;
    rows2 = rows/2;
    
    picdat2 = (unsigned char*) malloc (3 * rows2 * cols2 * sizeof(unsigned char));
    
    for (i = 0; i < rows; i ++){
        for (j = 0; j <cols; j++){
            k = i/2;
            l = j/2;
            picdat2 [ri (k, l, cols2)] = (picdat [ri(i, j, cols)] + picdat [ri((i+1), j, cols)] + picdat [ri (i, (j+1), cols)] + picdat [ri ((i+1), (j+1), cols)])/4;
            
            picdat2 [gi (k, l, cols2)] = (picdat [gi(i, j, cols)] + picdat [gi((i+1), j, cols)] + picdat [gi (i, (j+1), cols)] + picdat [gi ((i+1), (j+1), cols)])/4;
            
            picdat2 [bi (k, l, cols2)] = (picdat [bi(i, j, cols)] + picdat [bi((i+1), j, cols)] + picdat [bi (i, (j+1), cols)] + picdat [bi ((i+1), (j+1), cols)])/4;
            
        }
    }
   
    output_bmp (argv [2], cols2, rows2, picdat2, RGB);
    free (picdat);
    free (picdat2);
}



