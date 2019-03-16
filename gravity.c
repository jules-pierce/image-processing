//
//  test3.c
//  
//
//  Created by Jules Pierce on 7/7/15.
//
//
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "imgstuff.h"
#include "bmp_io.h"

#define XRANGE 1000.0
#define YRANGE 500.0
#define MAX_PROJECTILES 500

typedef enum {RED, GREEN, BLUE} p_color_t;
typedef enum {ACTIVE, INACTIVE} p_state_t;

typedef struct projectile{
    double x0; //start of x in meters
    double y0; //start of y in meters
    double vx0; //starting velocity
    double vy0; //starting velocity
    //add later: enum shape of object
    int radius; //in pixels
    double x; //current location
    double y; //current location
    double vx; //current velocity
    double vy; //current velocity
    p_color_t color;
    p_state_t state;
    //enum "trigger": events causing split of object
    //int num_children; //on split, how many more objects?
    //double split_velocity;
}projectile_t;

void insert_object (unsigned char *picdat, projectile_t p);
int xy2rc (double x, double y, int *r, int *c);
void prepare_pic (unsigned char *picdat);

int cols = 1280;
double meters_per_pixel_x;
double meters_per_pixel_y;
int rows;


int main (int argc, char *argv[]){
    int i, j;
    int np; //next projectile
    char filename [80];
    int num_img;
    unsigned char *picdat; //where should i free this?
    double T = 0.04;
    projectile_t p[MAX_PROJECTILES];
    
    if (argc != 4){
        printf ("usage is: %s radius num_img output_name\n", argv [0]);
        exit (1);
    }
    
    meters_per_pixel_x = XRANGE / cols;
    meters_per_pixel_y = meters_per_pixel_x;
    rows = floor (YRANGE / meters_per_pixel_y + 0.5);
    num_img = atoi (argv [2]);
		printf( "rows = %d cols = %d\n", rows, cols);
    
    picdat = (unsigned char*) malloc (3 * rows * cols * sizeof (unsigned char));
    
    for (i = 0; i < MAX_PROJECTILES; i++){
        p[i].state = INACTIVE;
    }
    p[0].x = p[0].x0 = 10;
    p[0].y = p[0].y0 = 10;
    p[0].vy = p[0].vy0 = 50;
    p[0].vx = p[0].vx0 = 50;
    p[0].radius = atoi (argv[1]);
    p[0].color = RED;
    
    np = 1;
    
    //intialize starting projectiles: do this as input?
    for (i = 0; i < num_img; i++){
        prepare_pic (picdat);
        for (j = 0; j < np; j++){
 //updates positions with time increment 1/25
            insert_object (picdat, p[j]);
            p[j].x = p[j].x + (p[j].vx * T);
            p[j].y = p[j].y + (p[j].vy * T);
            p[j].vy = p[j].vy - (9.8 * T);
            
        }
        sprintf (filename, "%s%05d.bmp", argv[3], i);
        output_bmp (filename, cols, rows, picdat, RGB);
    }
    free (picdat);
}
//is xy2rc right? and how do i reference it?
int xy2rc (double x, double y, int *r, int *c){ //compute rows and cols
    //receiving x and y in meters, w/ bottom left corner as (0,0)
    *c = floor(x/meters_per_pixel_x + 0.5);
    *r = floor(rows - 1 - (y/meters_per_pixel_y) + 0.5);
    //check bounds to make sure r and c are within the picture
    return (0);
    
}


void insert_object (unsigned char *picdat, projectile_t p){
    //radius is in pixels, must call prepare_pic first
    //printf ("%d\n", p.color);
    int i, j;
    double length;
    int c, r;

    xy2rc (p.x, p.y, &r, &c);
    //printf ("r = %d  c = %d\n", r, c);
    for (i = r - p.radius; i <= r + p.radius; i++){
        for (j = c - p.radius; j <= c + p.radius; j++){
            if( i < 0 || i > rows - 1 ||
                j < 0 || j > cols - 1) continue;
            length = sqrt( (double) ((j-c)*(j-c) + (i-r)*(i-r) ) );
            if (length <= p.radius){
                if (p.color == RED) {
                    picdat [ri (i, j, cols)] = 255;
                    picdat [gi (i, j, cols)] = 0;
                    picdat [bi (i, j, cols)] = 0;
                }
                if (p.color == GREEN) {
                    picdat [ri (i, j, cols)] = 0;
                    picdat [gi (i, j, cols)] = 255;
                    picdat [bi (i, j, cols)] = 0;
                }
                if (p.color == BLUE) {
                    picdat [ri (i, j, cols)] = 0;
                    picdat [gi (i, j, cols)] = 0;
                    picdat [bi (i, j, cols)] = 255;
                }
            }
        }
    }
    return;
}


void prepare_pic (unsigned char *picdat){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            picdat [ri (i, j, cols)] = 0;
            picdat [gi (i, j, cols)] = 0;
            picdat [bi (i, j, cols)] = 0;
        }
    }
    return;
}


