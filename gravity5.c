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

#define XRANGE 20000.0
#define YRANGE 6000.0
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
    double y1; //y coordinate of one step earlier
    p_color_t color;
    p_state_t state;
    bool is_splittable;
    //enum "trigger": events causing split of object
    //int num_children; //on split, how many more objects?
    //double split_velocity;
}projectile_t;

void insert_object (unsigned char *picdat, projectile_t* p);
p_state_t xy2rc (double x, double y, int *r, int *c);
void prepare_pic (unsigned char *picdat);
void init_projectiles (projectile_t *p);

int cols = 640;
double meters_per_pixel_x;
double meters_per_pixel_y;
int rows = 360;


int main (int argc, char *argv[]){
    int i, j, k;
    int frame_ctr = 0;
    int np; //next projectile
    char filename [80];
    int num_img;
    unsigned char *picdat; //where should i free this?
    double T = 0.16;
    projectile_t p[MAX_PROJECTILES];
    int num_projectiles;
    bool keep_going = true;
    
    if (argc != 5){
        printf ("usage is: %s radius num_img output_name num_projectiles\n", argv [0]);
        exit (1);
    }
    
    init_projectiles (p);
    meters_per_pixel_x = XRANGE / cols;
    meters_per_pixel_y = YRANGE / rows;
    
    num_img = atoi (argv [2]);
		//printf( "rows = %d cols = %d\n", rows, cols);
    num_projectiles = 2;
    if (num_projectiles < 1 || num_projectiles > MAX_PROJECTILES){
        printf ("error: num_projectiles out of range\n");
        exit (1);
    }
    //printf ("num_projectiles = %d\n", num_projectiles);
    
    picdat = (unsigned char*) malloc (3 * rows * cols * sizeof (unsigned char));
    
    for (i = 0; i < MAX_PROJECTILES; i++){
        p[i].state = INACTIVE;
    }
    
    p[0].x = p[0].x0 = 10;
    p[0].y = p[0].y0 = 10;
    p[0].vy = p[0].vy0 = 100;
    p[0].vx = p[0].vx0 = 50;
    p[0].radius = atoi (argv[1]);
    p[0].color = RED;
    p[0].state = ACTIVE;
    p[0].is_splittable = false;
    
    p[1].x = p[1].x0 = 10;
    p[1].y = p[1].y0 = 10;
    p[1].vy = p[1].vy0 = 60;
    p[1].vx = p[1].vx0 = 100;
    p[1].radius = atoi (argv[1]);
    p[1].color = BLUE;
    p[1].state = ACTIVE;
    p[1].is_splittable = false;

    
    np = num_projectiles;
    p[0].is_splittable = true;
    p[1].is_splittable = true;
    
    //intialize starting projectiles: do this as input?
    while (keep_going){
        if (frame_ctr % 25 == 0 ) fprintf(stderr, "frame number = %d\r", frame_ctr);
        //fflush(stderr);
        frame_ctr++;
        //printf ("1\n");
        prepare_pic (picdat);
        //printf ("2\n");
        for (j = 0; j < np; j++){
            //printf ("%u\n", p[j].state);
            //printf ("np = %d\n", np);
            //printf ("here %d  %d\n", i, j);
            //updates positions with time increment 1/25
            //printf ("here\n");
            if (p[j].state == ACTIVE){
                p[j].y1 = p[j].y;
                insert_object (picdat, &p[j]);
                p[j].x = p[j].x + (p[j].vx * T);
                p[j].y = p[j].y + (p[j].vy * T);
                if (frame_ctr < 75){
                    p[j].vy = p[j].vy + (20 * T) - (9.8 * T);
                    p[j].vx = p[j].vx + (20 * T);
                }
                else {
                    p[j].vy = p[j].vy - (9.8 * T);
                }
                if (p[j].y <= 10){
                    p[j].state = INACTIVE;
                }
                //printf (" y1= %f, y = %f\n", p[j].y1, p[j].y);
                //problem: once projectile splits, nothing to stop projectiles from splitting again
                    //fixed with loop if j==0, needs better answer
                if (p[j].is_splittable){
                    if (p[j].y1 > p[j].y){
                        p[j].state = INACTIVE;
                        for (k = 0; k < 4; k++){
                            p[np].state = ACTIVE;
                            p[np].x0 = p[np].x = p[j].x;
                            p[np].y0 = p[np].y = p[np].y1 = p[j].y;
                            p[np].vx0 = p[np].vx = p[j].vx + (k * 10);
                            p[np].vy0 = p[np].vy = p[j].vy + (k * 10);
                            p[np].radius = p[j].radius/2;
                            p[np].color = p[j].color;
                            np++;
                            if (np == MAX_PROJECTILES) {
                                printf ("error: exceeded array bounds\n");
                                exit (1);
                            }
                            //printf ("after %d\n", np);
                        }
                    }
                }
            }
        }
        sprintf (filename, "%s%05d.bmp", argv[3], frame_ctr);
        //printf ("good\n");
        output_bmp (filename, cols, rows, picdat, RGB);
        keep_going = false;
        for (i = 0; i < np; i++){
            if (p[i].state == ACTIVE) keep_going = true;
        }
    }
    free (picdat);
}

p_state_t xy2rc (double x, double y, int *r, int *c){ //compute rows and cols
    //receiving x and y in meters, w/ bottom left corner as (0,0)
    *c = floor(x/meters_per_pixel_x + 0.5);
    //printf ("x = %f  meters_per_pixel_x = %f\n", x, meters_per_pixel_x);
    *r = floor(rows - 1 - (y/meters_per_pixel_y) + 0.5);
    if (*r > rows || r < 0 || *c > cols || c < 0){
        printf ("warning: exceeded bounds of picture\n");
        return (INACTIVE);
    }
    return (ACTIVE);
    
}


void insert_object (unsigned char *picdat, projectile_t* p){
    //radius is in pixels, must call prepare_pic first
    //printf ("%d\n", p.color);
    //printf ("insert_object called\n");
    int i, j;
    double length;
    int c, r;
    p_state_t  p_s;

    p_s = xy2rc (p->x, p->y, &r, &c);
    if( p_s == INACTIVE){
        p->state = p_s;
        return;
    }
    
    //printf ("r = %d  c = %d\n", r, c);
    for (i = r - p->radius; i <= r + p->radius; i++){
        for (j = c - p->radius; j <= c + p->radius; j++){
            if( i < 0 || i > rows - 1 ||
                j < 0 || j > cols - 1) continue;
            length = sqrt( (double) ((j-c)*(j-c) + (i-r)*(i-r) ) );
            if (length <= p->radius){
                if (p->color == RED) {
                    //printf ("projectile is red\n");
                    picdat [ri (i, j, cols)] = 255;
                    picdat [gi (i, j, cols)] = 0;
                    picdat [bi (i, j, cols)] = 0;
                }
                if (p->color == GREEN) {
                    picdat [ri (i, j, cols)] = 0;
                    picdat [gi (i, j, cols)] = 255;
                    picdat [bi (i, j, cols)] = 0;
                }
                if (p->color == BLUE) {
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
            /*picdat [ri (i, j, cols)] = floor (picdat [ri (i, j, cols)] * .99);
            picdat [gi (i, j, cols)] = floor (picdat [gi (i, j, cols)] * .99);
            picdat [bi (i, j, cols)] = floor (picdat [bi (i, j, cols)] * .99);
            if (picdat [ri (i, j, cols)] < 10) picdat [ri (i, j, cols)] = 0;
            if (picdat [gi (i, j, cols)] < 10) picdat [gi (i, j, cols)] = 0;
            if (picdat [bi (i, j, cols)] < 10) picdat [bi (i, j, cols)] = 0;*/
            picdat [ri (i, j, cols)] = picdat [ri (i, j, cols)] > 2 ? picdat [ri (i, j, cols)] - 2 : 0;
            picdat [gi (i, j, cols)] = picdat [gi (i, j, cols)] > 2 ? picdat [gi (i, j, cols)] - 2 : 0;
            picdat [bi (i, j, cols)] = picdat [bi (i, j, cols)] > 2 ? picdat [bi (i, j, cols)] - 2 : 0;
        }
    }
    //printf ("prepare\n");
    return;
}

void init_projectiles (projectile_t *p){
    int i;
    for (i = 0; i < MAX_PROJECTILES; i++){
        p[i].x = p[i].x0 = 10;
        p[i].y = p[i].y0 = p[i].y1 = 10;
        p[i].vx0 = p[i].vy0 = p[i].vx = p[i].vy = 0;
        p[i].is_splittable = false;
        p[i].state = INACTIVE;
        p[i].color = GREEN;
    }
}


