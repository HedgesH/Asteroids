//player.h

typedef struct {
  float angle;
  float size;
  float life, x, y,dx,dy;
  float radius;
  int destroy;
  int vertices;
  int verticesX[4];
  int verticesY[4];
} player;

typedef struct{
	float x1,y1,x2,y2,x3,y3;
} coords;

//creates a ship
player *createPlayer(float x, float y, float angle, float size);

//creates a bullet
player *createBullet(float x,float y, float angle, float radius);

//unused functions, but can be used for linear up down left right movement
void accelX(player *p, float a, float delta,float maxspeed);

void accelY(player *p, float a, float delta,float maxspeed);
//unused functions

//rotates the ship
void rotateShip(player *p, int angle);

//accelerates the ship forwards using its angle and speed
void accelForward(player *p, float accel, float delta, float maxspeed);

//determines if ship is at edge of window
void boundary(player *p, float width, float height);

//determines if bullet is at edge of window
void boundaryBullet(player *a, float width, float height);

//updates position of bullet
void shoot(player *p, int speed);

//rotates x and y coords about the origin
coords rotate(float angle, float x, float y);

//rotates a triangle centered about origin
coords rotateDefaultTriangle(float angle, float size);

//renders ship
void drawPlayer(display *d, player *p);

//renders bullet
void drawBullet(display *d,player *b);


