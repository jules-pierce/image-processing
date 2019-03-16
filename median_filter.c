#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"
/*
unsigned char median (unsigned char *x, int N){
    unsigned char *marker;
    unsigned char *y;
    int pos;
    int i, j;
    int min;
    unsigned char *sorted;
    
    y = (unsigned char*) malloc (N * sizeof(unsigned char));
    marker = (unsigned char*) malloc (N * sizeof(unsigned char));
    sorted = (unsigned char*) malloc (N * sizeof(unsigned char));
    
    for (i = 0; i < N; i++){
        marker [i] = 0;
    }
    for (i = 0; i < N; i++){
        min = 255;
        for (j = 0; j < N; j++){
            if (marker[j] == 1) continue;
            if (x [j] < min){
                min = x[j];
                pos = j;
                y [i] = min;
            }
        }
        marker [pos] = 1;
    }
    printf ("%s\n", y);
    return 0;
}
int main(int argc, char *argv[] ){
    if (argc != 3){
        printf ("usage is: %s  number_string total_numbers\n", argv[0]);
    }
    
    median (argv[1], atoi (argv[2]));
    return 0;
}

int jules (int x, int y){
    printf ("%d + %d = %d\n", x, y, x+y);
    return 0;
}

int main (int argc, char *argv[]){
    jules (3,2);
    return 0;
}
*/

unsigned char median (unsigned char *x, int N){
    unsigned char *marker;
    unsigned char *y;
    int pos;
    int i, j;
    int min;
    unsigned char *sorted;
    unsigned char med;
    
    y = (unsigned char*) malloc (N * sizeof(unsigned char));
    marker = (unsigned char*) malloc (N * sizeof(unsigned char));
    sorted = (unsigned char*) malloc (N * sizeof(unsigned char));
    
    for (i = 0; i < N; i++){
        marker [i] = 0;
    }
    for (i = 0; i < N; i++){
        min = 255;
        for (j = 0; j < N; j++){
            if (marker[j] == 1) continue;
            if (x [j] < min){
                min = x[j];
                pos = j;
            }
        }
        y [i] = min;
        marker [pos] = 1;
    }
    //printf ("%s\n", y);
    
    med = y[N/2];
    //printf ("%c\n", y[med]);
    free (y);
    free (marker);
    free (sorted);
    return med;
}
int main(int argc, char *argv[] ){
    int rows, cols;
    unsigned char *picdat, *picdat1;
    unsigned char *x;
    int i, j;
    
   if (argc != 3){
        printf ("usage is: %s  input.bmp ouptut.bmp\n", argv[0]);
        exit(1);
    }
    
    x = (unsigned char*) malloc (9 * sizeof(unsigned char));
    
    input_bmp (argv[1], &cols, &rows, &picdat, RGB);
    picdat1 = (unsigned char*) malloc (3 * rows * cols * sizeof(unsigned char));
    
    for (i = 1; i < (rows - 1); i++){
        for ( j = 1; j < (cols - 1); j++){
            x [0] = picdat [gi ((i-1), (j-1), cols)];
            x [1] = picdat [gi ((i-1), j, cols)];
            x [2] = picdat [gi ((i-1), (j+1), cols)];
            x [3] = picdat [gi (i, (j-1), cols)];
            x [4] = picdat [gi (i, j, cols)];
            x [5] = picdat [gi (i, (j+1), cols)];
            x [6] = picdat [gi ((i+1), (j-1), cols)];
            x [7] = picdat [gi ((i+1), j, cols)];
            x [8] = picdat [gi ((i+1), (j+1), cols)];
            picdat1 [gi (i, j, cols)] = median (x, 9);
            
            x [0] = picdat [bi ((i-1), (j-1), cols)];
            x [1] = picdat [bi ((i-1), j, cols)];
            x [2] = picdat [bi ((i-1), (j+1), cols)];
            x [3] = picdat [bi (i, (j-1), cols)];
            x [4] = picdat [bi (i, j, cols)];
            x [5] = picdat [bi (i, (j+1), cols)];
            x [6] = picdat [bi ((i+1), (j-1), cols)];
            x [7] = picdat [bi ((i+1), j, cols)];
            x [8] = picdat [bi ((i+1), (j+1), cols)];
            picdat1 [bi (i, j, cols)] = median (x, 9);
            
            x [0] = picdat [ri ((i-1), (j-1), cols)];
            x [1] = picdat [ri ((i-1), j, cols)];
            x [2] = picdat [ri ((i-1), (j+1), cols)];
            x [3] = picdat [ri (i, (j-1), cols)];
            x [4] = picdat [ri (i, j, cols)];
            x [5] = picdat [ri (i, (j+1), cols)];
            x [6] = picdat [ri ((i+1), (j-1), cols)];
            x [7] = picdat [ri ((i+1), j, cols)];
            x [8] = picdat [ri ((i+1), (j+1), cols)];
            picdat1 [ri (i, j, cols)] = median (x, 9);
        }
    }
    output_bmp (argv[2], cols, rows, picdat1, RGB);
    
    free(x);
    free(picdat);
    free(picdat1);
    return 0;
}

