#include "include/helper.h"

asteroid *generateAsteroid(float width, float height, int maxr, int speed){
	asteroid *a = malloc(sizeof(asteroid));


	int vertices = (rand() % (max_vertices-4)) + 4;

	a->vertices = vertices;

	for (int i = 0; i < vertices; ++i)
	{
		//printf("%d\n",rand()% maxr );
		int angle = i*(360/vertices);
		float r = (rand()% (maxr/2)) + (maxr/2);

		a->verticesX[i] = polarToCartX(r, angle);
		a->verticesY[i] = polarToCartY(r, angle);
		a->verticesRadius[i] = r;

	}

	a->life = 100;
	a->maxr = maxr;
	a->width = width;
	a->height = height;

	minRadius(a);

	int r = rand() % (int)width;
	int r2 = rand() % (int)width;


	int sigx = (rand()%4) -2 ;
	if(sigx >= 0) a->x = width + 2*maxr + r;
	else a->x = 0 - 2*maxr - r;
	int sigy = (rand()%4) -2  ;
	if(sigy >= 0) a->y = height + 2*maxr + r2;
	else a->y = 0 - 2*maxr - r2;

	//printf("new asteroid x: %f  y:  %f \n",a->x,a->y );
	int angle = rand() % 360;
	a->dx = polarToCartX(speed,angle);
	a->dy = polarToCartY(speed,angle);

	return a;
}

void minRadius(asteroid *a){
	float max;
	a->minr = a->maxr;

	for (int i = 0; i < a->vertices; ++i)
	{
		if (a->verticesRadius[i] < a->minr) a->minr = a->verticesRadius[i];
	}
}

float polarToCartX(float r, float a){
	
	float b = ((2*3.1415)/360);
	float x = r * cos(a*b);
	return x;
}

float polarToCartY(float r, float a){
	
	float b = ((2*3.1415)/360);
	float y = r * sin(a*b);
	return y;
}

void drawAsteroid(display *d, asteroid *a){

	int v = a->vertices;

	float x = a->x;
	float y = a->y;

	for (int i = 0; i <  v - 1; ++i)
	{
		int x1 = x + (a->verticesX[i]);
		int y1 = y + (a->verticesY[i]);
		int x2 = x + (a->verticesX[i+1]);
		int y2 = y + (a->verticesY[i+1]);
		line(d, x1 , y1 , x2 , y2 );
	
		//printf("%d. %d. %d.  %d\n",x1,y1,x2,y2);
	}

	int x1 = x + (a->verticesX[0]);
	int y1 = y + (a->verticesY[0]);
	int x2 = x + (a->verticesX[v-1]);
	int y2 = y + (a->verticesY[v-1]);


	line(d,x1  ,y1  ,x2  ,y2 );
	
	//printf("%d. %d. %d.  %d\n",x1,y1,x2,y2);
}

void moveAsteroid(asteroid *a){
	a->x += a->dx;
	a->y += a->dy;
}

void boundaryAsteroid(asteroid *a){
	if(a->x < 0 - (2*a->maxr) ) a->x = a->width + (2*a->maxr);
    if(a->x > a->width + (2*a->maxr)  ) a->x = 0 - (2*a->maxr);
    if(a->y<  0  - (2*a->maxr)) a->y = a->height + (2*a->maxr);
    if(a->y > a->height + (2*a->maxr)) a->y = 0 - (2*a->maxr);
}

#ifdef test_asteroid

int main(int argc, char const *argv[])
{

	display *d;
    d = newDisplay("graphicsTest",1000,1000);
    float delta = 50/3;
    asteroid *a = generateAsteroid(500,500,100,4,0);
    int angle = 0;
    for (int i = 0; i < 1000; ++i)
    {
    	clear(d);

    	int angle = rand() % 360;
    	float speed = (rand() % 100)/50;

    	a->dx += speed * cos(angle*((2*3.1415)/360));
		a->dy += speed * sin(angle*((2*3.1415)/360));

    	moveAsteroid(a);

    	boundaryAsteroid(a,1000,1000);

    	drawAsteroid(d,a);
		show(d);
		pause(d,delta);
    }

    clear(d);
    end(d);

    return 0;
}

#endif
