/* Controller */

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"

/*Joystick 5-way switch*/
typedef enum {JLT = 0, JRT, JUP, JDN, JCR} btnId_t;
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);

void controls(void){
	player.shoot = false;
	if(jsPrsdAndRlsd(JLT)){
		//rotate ship anti-clockwise
		moveLeft();
	}
	else if(jsPrsdAndRlsd(JRT)){
		//rotate ship clockwise
		moveRight();
	}
	else if(jsPrsdAndRlsd(JUP)){
		//moves ship forward
		moveUp();
	}
	else if(jsPrsdAndRlsd(JDN)&& paused == false && mode == true){
		//pauses game
		paused = true;
		game =!game;
		wait_ms(200);
	}
	else if(jsPrsdAndRlsd(JCR) && paused == true && mode == true){
		//unpauses game
		paused = false;
		game = game;
		wait_ms(200);
	}
	else if(jsPrsdAndRlsd(JCR) && paused == false && mode == true){
		//shoot missiles
		player.shoot = true;
		missileSystem();
	}
}

/* Definition of Joystick press capture function
 * b is one of JLEFT, JRIGHT, JUP, JDOWN - from enum, 0, 1, 2, 3
 * Returns true if this Joystick pressed then released, false otherwise.
 *
 * If the value of the button’s pin is 0 then the button is being pressed,
 * just remember this in savedState.
 * If the value of the button’s pin is 1 then the button is released, so
 * if the savedState of the button is 0, then the result is true, otherwise
 * the result is false. */
bool jsPrsdAndRlsd(btnId_t b) {
	bool result = false;
	uint32_t state;
	static uint32_t savedState[5] = {1,1,1,1,1};
        //initially all 1s: nothing pressed
	state = jsBtns[b].read();
  if (savedState[b] == 0) {
		result = true;
	}
	savedState[b] = state;
	return result;
}
