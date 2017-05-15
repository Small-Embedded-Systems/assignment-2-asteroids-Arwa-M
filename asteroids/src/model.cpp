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

/* Ship collision detected */
void shipCollision(struct rock *l){
	for( ; l ; l = l->next ) {
		if(l->p.x<(player.p.x+8) && l->p.x>(player.p.x- 8)){
			if(l->p.y<(player.p.y + 8) && l->p.y>(player.p.y - 8)){
				if (player.shields <= 0){
					player.shields = 0;
					player.lives--;
				} else {
					player.shields--;
				}
				elapsed_time=0;
				player.p.x = 250;
				player.p.y = 100;
			}
		}
	}
}

/* Missile collision detected */
void missileCollision(struct missile *l, struct rock *r){
	for ( ; l ; l = l->next){ 
		for( ; r ; r =r->next){ 
			if(l->p.x > (r->p.x - 10) && l->p.x < (r->p.x + 10)){
				if(l->p.y > (r->p.y - 10) && l->p.y < (r->p.y + 10)){
					l->ttl = 0;
					r->ttl = 0;
					score += 5;
				}
			}
		}
	}
}

/* Missile system */
void missileSystem(){
	if(player.shoot ==true){
		struct missile *newShot = allocate_missile_node();
		if(newShot){
			newShot->next = shots;
			shots = newShot;
			newMissile(newShot);
		}
	}
}

/* Constructs new missiles */
void newMissile(struct missile *l){
	l->angle = player.angle;
	l->p.x = player.p.x;
	l->p.y = player.p.y;
	l->v.x = 200 * (-cos(radians(player.angle)));
	l->v.y = 200 * (sin(radians(player.angle)));
	l->ttl = 200;
}

/* Updates missile list */
void updateMissileList(struct missile *l){
	for ( ; l ; l = l->next){
		if (l->next->ttl <= 0){
			struct missile *expiredM = l->next;
			l->next = l->next->next;
			missileFreeNode(expiredM);
		}		
	}
}

void moveMissiles(struct missile *l){
	for ( ; l ; l = l->next){
		l->p.x += l->v.x * Dt;
		l->p.y += l->v.y * Dt;
		if( l->p.x <0 || 480 <l->p.x ) l->ttl=0;
		if( l->p.y<10 || 260 <l->p.y ) l->ttl=0;

		l->ttl -= Dt;	
	}	
}

/* Loads missiles */
void loadMissiles(){
	int n;
	for(n=0; n<(heapsize-1) ; n++){
		missile_data[n].next = &missile_data[n+1];
	}
	missile_data[n].next = NULL;
	freeMissileNodes = &missile_data[0];
}

shot_t *allocate_missile_node(void){
	shot_t *node = NULL;
	if (freeMissileNodes){
		node = freeMissileNodes;
		freeMissileNodes = freeMissileNodes->next;
	}
	return node;
}

void missileFreeNode(shot_t *n){
	n->next = freeMissileNodes;
	freeMissileNodes = n;
}

/* Asteroid System*/
struct rock * newAsteroids(){
	int i;
	for(i = 0; i < heapsize-1; i++){
		struct rock *newRock = allocate_rock_node();
		if(newRock){
			newRock->next = asteroids;
			asteroids = newRock;
			
			switch (randrange(1,5)){
				case 1 :
					newRock->p.x = randrange(0,100);
					newRock->p.y = randrange(0,270);
					newRock->v.x = 1;
					if(newRock->p.y > 140) newRock->v.y = -5;
					if(newRock->p.y <= 140) newRock->v.y = 5;
				break;
				case 2 :
					newRock->p.x = randrange(280,480);
					newRock->p.y = randrange(0,270);
					newRock->v.x = -1;
					if(newRock->p.y > 140) newRock->v.y = -5;
					if(newRock->p.y <= 140) newRock->v.y = 5;
				break;	
				case 3 :
					newRock->p.x = randrange(0,480);
					newRock->p.y = randrange(0,100);
					newRock->v.y = 1;
					if(newRock->p.x > 200) newRock->v.x = -5;
					if(newRock->p.y <= 200) newRock->v.x = 5;
				break;	
				case 4 :
					newRock->p.x = randrange(0,480);
					newRock->p.y = randrange(170,270);
					newRock->v.y = 1;
					if(newRock->p.x > 200) newRock->v.x = -5;
					if(newRock->p.y <= 200) newRock->v.x = 5;
				break;
				default:
				break;
			}
			newRock->ttl = 200;
		}
	}
	return asteroids;
}

/* Loads asteriods */
void loadAsteroids(){
	int n;
	for(n=0; n<(heapsize-1) ; n++){
		rock_data[n].next = &rock_data[n+1];
	}
	rock_data[n].next = NULL;
	freeRockNodes = &rock_data[0];	
}

rock_t *allocate_rock_node(void){
	rock_t *node = NULL;
	if (freeRockNodes){
		node = freeRockNodes;
		freeRockNodes = freeRockNodes->next;
	}
	return node;
}

void rockFreeNode(rock_t *n){
	n->next = freeRockNodes;
	freeRockNodes = n;
}

/* Updates rock list */
void updateRockList(struct rock *l){
	for ( ; l ; l = l->next){
		if (l->next->ttl <= 0){
			struct rock *expiredR = l->next;
			l->next = l->next->next;
			rockFreeNode(expiredR);
		}		
	}
}

void moveRocks(struct rock *l){
	for ( ; l ; l = l->next){
		l->p.x += l->v.x * Dt;
		l->p.y += l->v.y * Dt;
		if( l->p.x<-20 || 500<l-> p.x ) l->ttl=0;
		if( l->p.y<25 || 280<l-> p.y ) l->ttl=0;
		l->ttl -= Dt;
	}	
}

void physics(void)
{
	if (mode){
		elapsed_time = elapsed_time + Dt;
		score += (int) elapsed_time;
		
		moveShip(player);
		
		missileSystem();
		loadMissiles();
		moveMissiles(shots);
		
		asteroids = newAsteroids();
		loadAsteroids();
		moveRocks(asteroids);
		
		shipCollision(asteroids);
		missileCollision(shots, asteroids);
		
		updateMissileList(shots);
		updateRockList(asteroids);
		
		if(player.lives==0 && player.shields==0){
			score = score;
			elapsed_time = 0;
			gameEnd = true;
			game = false;
			
		}
	} 
}
