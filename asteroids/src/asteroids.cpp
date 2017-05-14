/* Asteroids Assignment
Student Name: Arwa Mhannee
Student ID: 15007722		
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
int 	shields;
struct ship player;

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = false;
bool mode = false;
bool gameEnd = false;
bool game = false;

void initialiseShip(ship){
	player.p.x = 250;
	player.p.y = 100;
	player.shields = 3;
}

/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);
int main()
{
	init_DBuffer();
	
	view.attach( draw, 0.025);
	model.attach( physics, Dt);
	controller.attach( controls, 0.1);
	
	lives = 5;
	score = 0;
	shields = 3;
	elapsed_time = 0;
	
	/* Press to start */
	while( userbutton.read() ){ /* remember 1 is not pressed */
			mode = false;
			wait_ms(100);
	}
	mode = true;
	
	while(mode == true) {
		game = true;
		while(lives >0){
			initialiseShip(player);
		}
		/* When each life is lost detach all tickers and initate gameover screen*/
		if(lives==0 && shields==0){
			gameEnd = true;
			game = false;
			wait_ms(200);
			view.detach();
			model.detach();
			controller.detach();
		}	
	}
}
