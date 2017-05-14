/* Asteroids View */

/* support double buffering */
void init_DBuffer(void);
void swap_DBuffer(void);

/* Functions */
void draw(void);
void drawSidebar(int lives, int shields, int elapsed_time, int score);
void drawShip(struct player);
void drawMissiles(struct missile *lst);
void drawRocks(struct rock *lst);
void drawImg();
void gameMenu();
void gameOver();
void gamePaused();
void gamePlayed();

/* Bitmap image XBM format code */
#define rock_width 40
#define rock_height 40
static unsigned char rock_bits[] = {
	0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0xc0,
  0xff, 0x03, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00, 0x00, 0xe0, 0xff, 0x0f,
  0x00, 0x00, 0xe0, 0xff, 0x0f, 0x00, 0xf0, 0xe0, 0xff, 0x1f, 0x00, 0xf8,
  0xf1, 0xff, 0x3f, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff,
  0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x0f,
  0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff,
  0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff,
  0x03, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff,
  0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff,
  0xff, 0x07, 0xfe, 0xff, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0xff, 0x07,
  0xfc, 0x07, 0xf8, 0xff, 0x07, 0xfc, 0x01, 0xe0, 0xff, 0x07, 0xfc, 0x00,
  0x80, 0xff, 0x07, 0x38, 0x00, 0x00, 0xff, 0x03 };
