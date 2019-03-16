#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

double sq_err (unsigned char *picdat1, unsigned char *picdat2, int start_i, int start_j, int end_i, int end_j, int cols);

int main(int argc, char *argv[] ){
    unsigned char *picdat1 = NULL, *picdat2 = NULL;
    char filename [80];
    int cols, rows;
    int i;
    int num_pic;
    //how do i create the variables for an unknown number of pictures?
    
    if (argc != 7){
        printf ("Usage is: %s basename num_pic start_i start_j end_i end_j\n", argv [0]);
        exit (0);
    }
    
    num_pic = atoi (argv[2]);
    
    for (i = 1; i < num_pic - 1; i++){
        sprintf (filename, "%s%04d.bmp", argv[1], i);
        input_bmp (filename, &cols, &rows, &picdat1, MONO);
        sprintf (filename, "%s%04d.bmp", argv[1], i + 1);
        input_bmp (filename, &cols, &rows, &picdat2, MONO);
        printf ("%lf    %lf\n", (double)i, sq_err (picdat1, picdat2, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), cols));
        free (picdat1);
        free (picdat2);
    }
    
}

//in given square, calculate diff between values squared divided by total #values
//i is rows, j is cols
double sq_err (unsigned char *picdat1, unsigned char *picdat2, int start_i, int start_j, int end_i, int end_j, int cols){
    double total = 0;
    double divide;
    int i, j;
    
    for (i = start_i; i <=end_i; i++){
        for (j = start_j; j <=end_j; j++){
            total += (picdat1 [mi (i, j, cols)] - picdat2 [mi (i, j, cols)]) * (picdat1 [mi (i, j, cols)] - picdat2 [mi (i, j, cols)]);
        }
    }
    divide = (end_i - start_i + 1) * (end_j - start_j + 1);
    return total/divide;
}



