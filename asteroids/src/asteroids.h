/* Game state */

extern float elapsed_time; /* time this ship has been active */
extern int   score;        /* total score so far */
extern int   lives;        /* lives remaining */
extern int   shields;      /* shields remaining */
extern bool  paused;			 /* game is paused */
extern bool  gameEnd;			 /* game is Over */
extern bool  game;			 	 /* game state */
extern bool  mode;			 	 /* mode of game */

extern struct ship player;

extern struct rock *asteroids; /* array of rocks / pointer to linked-list */
extern struct missile *shots;  /* array of missiles / pointer to linked-list */

extern const float Dt; /* Time step for physics, needed for consistent motion */
