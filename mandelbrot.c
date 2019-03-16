#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"
#include "CN.h"

int main(int argc, char *argv[] ){
    CN_t ULC;
    double width, height;
    int rows, cols;
    CN_t z, c;
    unsigned char *picdat;
    double delt_x, delt_y;
    int i, j, k;
    int thresh;
    unsigned char *r, *g, *b;
    unsigned int start_seed;
    int color;
    
    if (argc != 7){
        printf ("usage is: %s threshold start_seed out.bmp color (as number) ULC.re ULC.im\n", argv[0]);
        exit (1);
    }
    
		/***********
		Good settings (whole set): -2.1, 1, 2.6, 2
		************/
    ULC.re = atoi (argv[5]);
    ULC.im = atoi (argv[6]);
    width = 2.6;
    height = 2;
    rows = 700;
    cols = 700;
    thresh = atoi (argv [1]);
    start_seed = atoi (argv [2]);
    srand (start_seed);
    color = atoi (argv [4]);
    
    if (color > 2){
        printf ("error: color must be 0 (red), 1(blue), 2(green)");
    }
    
    
    picdat = (unsigned char*) malloc (3 * rows * cols * sizeof(unsigned char));
    r = (unsigned char*) malloc (255 * sizeof (unsigned char));
    g = (unsigned char*) malloc (255 * sizeof (unsigned char));
    b = (unsigned char*) malloc (255 * sizeof (unsigned char));
    
    delt_x = width / cols;
    delt_y = height / rows;
    
    for (i = 0; i < 256; i++){
        r[i] = i;
        g[i] = (i + 128) % 100;
        b[i] = (i + 256) % 100;
    }
    
    for (i = 0; i < rows; i ++){
        for (j = 0; j < cols; j++){
            picdat [ri (i, j, cols)] = 255;
            picdat [gi (i, j, cols)] = 255;
            picdat [bi (i, j, cols)] = 255;
        }
    }
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            c.re = ULC.re + j * delt_x;
            c.im = ULC.im - i * delt_y;
            for (k = 0; k < 256; k++){
                if (k == 0) {
                    z.re = 0;
                    z.im = 0;
                }
                else{
                    z = CN_add (CN_pow (z, 2), c);
                }
                if (CN_mag (z) > thresh) {
                    if (color == 0){
                        picdat [ri (i, j, cols)] = k;
                        picdat [gi (i, j, cols)] = g[k];
                        picdat [bi (i, j, cols)] = b[k];
                    }
                    if (color == 1){
                        picdat [ri (i, j, cols)] = r[k];
                        picdat [gi (i, j, cols)] = g[k];
                        picdat [bi (i, j, cols)] = k;
                    }
                    if (color == 2){
                        picdat [ri (i, j, cols)] = r[k];
                        picdat [gi (i, j, cols)] = k;
                        picdat [bi (i, j, cols)] = b[k];
                    }
                }
            }
        }
    }
    output_bmp (argv [3], rows, cols, picdat, RGB);
    
    
    free (picdat);
    free (r);
    free (g);
    free (b);
}

