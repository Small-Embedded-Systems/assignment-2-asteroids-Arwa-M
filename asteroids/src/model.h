/* Asteroids Model */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

extern double x1, y1, x2, y2, x3, y3, accel;

extern struct missile *shots;
extern struct rock *asteroids;

/* Some initial struct types if you want to usd them */
struct ship {
	coordinate_t p;
	vector_t     v;
	float angle;
	bool shoot;
	int direction; 
	int shields;
};

/* initial structs for building linked lists */
typedef struct rock {
	coordinate_t p;
	vector_t     v;
	float angle;
	int rockImg;
	float ttl;
	struct rock *next;
} rock_t;

typedef struct missile {
	coordinate_t p;
	vector_t     v;
	float angle;
	int hit;
	float ttl;
	struct missile *next;
} shot_t;

/* Methods */
void physics(void);
void moveLeft(void);
void moveRight(void);
void moveUp(void);

void missileSystem();
void newMissile(struct missile *r);
void newAsteroid(struct rock *r);

void loadMissiles();
void loadAsteroids();

void moveMissiles(struct missile *l);
void moveRocks(struct rock *l);

void updateMissileList(struct missile *l);
void updateRockList(struct rock *l);

struct rock *newAsteroids(void);
rock_t *allocate_rock_node(void);
shot_t *allocate_missile_node(void);

void rockFreeNode(rock_t *n);
void missileFreeNode(shot_t *n);

void missileCollision(struct missile *l, struct rock *k);
void shipCollision(struct rock *l);
