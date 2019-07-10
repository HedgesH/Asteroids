//particle effects

#define max_particles 10
#define duration 1000

typedef struct{
	float x1,x2,y1,y2;
	float dx,dy;
	float angle;
	float accel;
	int timer;
} eline;

typedef struct{
	float x,y,dx,dy;
	float radius;
	float angle;
	float accel;
	int timer;
} ecircle;

typedef struct{
	ecircle **cs;
	eline **ls;
	int numOfCircles;
	int numOfLines;
	int timer;
} effect;

//gives the angle of the line relative to the ship
static float coordsToAngle(player *p, float x1, float y1, float x2, float y2);

//creates the explosion effect for an asteroid
effect *createAsteroidExplosion(float x, float y, float speed);

//creates the explosion effect for a ship
effect *createShipExplosion(player *p,float accel);

//draws the effect to the renderer
void drawEffect(display *d, effect *e);

//updates the position of the effect
void updateEffect(effect *e, int timer, int delta);

//frees all the allocated memory
void closeEffect(effect *e);

