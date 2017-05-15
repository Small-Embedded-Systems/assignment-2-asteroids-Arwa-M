/* Asteroids view */

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "view.h"

extern "C" uint8_t flip(uint8_t);

Display *graphics = Display::theDisplay();

static void drawSidebar(int lives, int shields, int elapsed_time, int score);
static void drawShip(struct ship);
static void drawMissiles(struct missile *lst);
static void drawRocks(struct rock *lst);

uint8_t flip(uint8_t); //assembly function for flipping image bit pattern

static const colour_t background = rgb(0,51,102); /* Midnight Blue */
static const colour_t shipColour = rgb(255,255,255); /* White */
static const colour_t rockColour = rgb(32,32,32); /* Dark Grey */

static const coordinate_t shape[] = {
    {10,0}, {-5,5}, {-5,-5}
};

/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}

/* Reverses the bits */
unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

/* Draw the sidebar */
void drawSidebar(int lives, int shields, int elapsed_time, int score){
	graphics->setTextColor(WHITE);
	graphics->setTextSize(1);
	graphics->setCursor(5,2);
	graphics->printf("Lives Left:%i",player.lives);
	graphics->setCursor(100,2);
	graphics->printf("Shield:%i",player.shields);
	graphics->setCursor(220,2);
	graphics->printf("ASTEROIDS");
	graphics->setCursor(360,2);
	graphics->printf("Time:%i",elapsed_time);
	graphics->setCursor(410,2);
	graphics->printf("Score:%i",score);
}

/* Draw the ship */
void drawShip(ship){
	float theta = radians(player.angle);
	float x1, y1, x2, y2, x3, y3;
	
	x1 = player.p.x +((-7*cos(theta)) -  (7*sin(theta)));
	y1 = player.p.y +((-6*sin(theta)) +  (6*cos(theta)));
	
	x2 = player.p.x +((-6*cos(theta)) - (-6*sin(theta)));
	y2 = player.p.y +((-6*sin(theta)) + (-6*cos(theta)));	
	
	x3 = player.p.x +((10*cos(theta)) -  (sin(theta)));
	y3 = player.p.y +((10*sin(theta)) +  (cos(theta)));

	if (player.shields == 3) {
		graphics->drawCircle(player.p.x, player.p.y, 15, GREEN);
	}
	if (player.shields == 2) {
		graphics->drawCircle(player.p.x, player.p.y, 15, YELLOW);
	}
	if (player.shields == 1) {
		graphics->drawCircle(player.p.x, player.p.y, 15, RED);
	}
	graphics->drawTriangle(x1, y1, x2, y2, x3, y3, shipColour);
	graphics->fillTriangle(x1, y1, x2, y2, x3, y3, shipColour);
}

/* Draw the list of missiles */ 
void drawMissiles(struct missile *lst){
	while(lst){
		graphics->fillCircle(lst->p.x, lst->p.y, 1, shipColour);
		lst = lst->next;
	}
}

/* Draw the list of rocks */
void drawRocks(struct rock *lst){
	unsigned char pic[sizeof(rock_bits)];
	memcpy (pic, rock_bits, sizeof(pic));
	for (int c = 0; c < sizeof(rock_bits) ; c++) {
					pic[c] = reverse(pic[c]);
	}
	while(lst){
		graphics->drawBitmap(lst->p.x-20, lst->p.y-20, pic, rock_width, rock_height, rockColour);
		lst = lst->next;
	}	
}

/* Draw decoration on game menu scree */
void drawImg(){
	unsigned char pic[sizeof(rock_bits)];
		memcpy (pic, rock_bits, sizeof(pic));
		for (int c = 0; c < sizeof(rock_bits) ; c++) {
						pic[c] = reverse(pic[c]);
		}
		graphics->drawBitmap(320, 180, pic, rock_width, rock_height, rockColour);
		graphics->drawBitmap(230, 180, pic, rock_width, rock_height, rockColour);
		graphics->drawBitmap(140, 180, pic, rock_width, rock_height, rockColour);
}

/* Draw the game menu screen */
void gameMenu(){
	graphics->fillScreen(background);
	graphics->setCursor(140,80);
	graphics->setTextColor(WHITE,background);
	graphics->setTextSize(4);
	graphics->printf("ASTEROIDS");
	graphics->setTextSize(2);
	graphics->setCursor(110,150);
	graphics->printf("Press USERBTN to begin");
	drawImg();
}

/* Draw the game over screen */
void gameOver(){
	graphics->fillScreen(background);
	graphics->setTextColor(WHITE);
	graphics->setCursor(135,90);
	graphics->setTextSize(4);
	graphics->printf("GAME OVER");
	graphics->setCursor(160,150);
	graphics->setTextSize(2);
	graphics->printf("Final Total: %i ", score);
}

/* Draw the game paused screen */
void gamePaused(){
	graphics->setCursor(220,140);
	graphics->printf("PAUSED");
}

/* Draw the game played screen */
void gamePlayed(){
	graphics->setCursor(220,140);
	graphics->printf("      ");
}

/* Draw the game */
void draw(void){
	gameMenu();
	if(mode){
		graphics->fillScreen(background);
		drawSidebar(lives,shields,elapsed_time, score);
		drawShip(player);
		drawMissiles(shots);
		drawRocks(asteroids);
		if(paused == true){
			gamePaused();
		}
		if(paused == false){
			gamePlayed();
		}
		if(gameEnd == true && game== false){
			gameOver();
		}
	}
	swap_DBuffer();
}
