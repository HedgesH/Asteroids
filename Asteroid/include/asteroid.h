//asteroid.h

#define max_vertices 20

typedef struct {
  int verticesRadius[max_vertices];
  int vertices;
  int verticesX[max_vertices];
  int verticesY[max_vertices];
  float life, x, y,dx,dy,angle,maxr,width,height,minr;
} asteroid;

asteroid *generateAsteroid(float width, float height, int maxr, int speed);

float polarToCartX(float r, float a);

float polarToCartY(float r, float a);

void minRadius(asteroid *a);

void drawAsteroid(display *d, asteroid *a);

void moveAsteroid(asteroid *a);

void boundaryAsteroid(asteroid *a);







