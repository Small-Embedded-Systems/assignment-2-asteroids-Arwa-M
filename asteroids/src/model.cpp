/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"
#include "view.h"

/* Definitions */
#define turn 6
#define accMax 2
#define accAdd 0.2

static double accel = 1.0;
static const size_t heapsize = 10;
static rock_t rock_data[heapsize];
static shot_t missile_data[heapsize];

static shot_t *freeMissileNodes;
static rock_t *freeRockNodes;

struct missile * shots = NULL;
struct rock * asteroids = NULL;

/* If you want to initialise a linked list: You'll have to replace node_t with the right type*/
typedef struct node {
    struct node *next;
} node_t;

const size_t MAXSize = 10;
node_t data[MAXSize];
node_t *initialise()
{
    int c;
    for(c=0 ; c<(MAXSize-1) ; c++){
        data[c].next = &data[c+1];
    }
    data[c].next = NULL;
    return data;
}

/* Makes ship move */
void moveShip(ship){
	//updates position based on movement speed(velocity)
	player.p.x += player.v.x;
	player.p.y += player.v.y;
	
	//this moves the ship forward
	if(accel > 0.0){		
		player.p.x += accel*cos(radians(player.angle));
		player.p.y += accel*sin(radians(player.angle));
		
		if(accel > 0.5)
		{
			accel = accel-0.006;	
		}
		else
		{
			accel = accel-0.002;
		}			
	}	
	
	//makes the ship wrap-around the screen
	if(player.p.x < 0) 		player.p.x += 480;
	if(player.p.x >= 480) player.p.x -= 480;
	if(player.p.y < 0) 		player.p.y += 272;
	if(player.p.y >= 272) player.p.y -= 272;
}

/* Makes ship turn left */
void moveLeft(void){
	player.angle += turn;	
}

/* Makes ship turn right */
void moveRight(void){
	player.angle -= turn;	
}

/* Makes ship move up */
void moveUp(void){
	player.p.x += accel*cos(radians(player.angle));
	player.p.y += accel*sin(radians(player.angle));
	
	if(accel <= accMax)
	{					
		accel = accel + accAdd;
	}
}
