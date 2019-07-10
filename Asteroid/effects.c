//effects.c
#include "include/helper.h"

// typedef struct{
// 	float x1,x2,y1,y2;
// 	float angle;
// 	float speed;
// } line;

// typedef struct{
// 	float x,y;
// 	float radius;
// 	float angle;
// 	float speed;
// } circle;

// typedef struct{
// 	circle **cs;
// 	line **ls;
// 	int timer;
// } effect;

static float coordsToAngle(player *p, float x1, float y1, float x2, float y2){
	int xx1 = p->x;
	int yy1 = p->y;
	int xx2 = (x1 + x2)/2 ;
	int yy2 = (y1 + y2)/2 ;
	if (xx1 - xx2 == 0) return 90;
	if (yy1 - yy2 == 0) return 180;
	float dydx = (yy2-yy1)/(xx2-xx1);
	float angle = atan(dydx);
	float scale = (360/(2*3.1415));
	angle = angle * scale;
	return angle;
}

effect *createAsteroidExplosion(float x, float y, float accel){

	int numOfCircles = (rand() % (max_particles-5)) + 5;
	float dx,dy;

	ecircle **e;

	e = malloc(max_particles * sizeof(ecircle));
	for (int i = 0; i < max_particles; ++i)
	{
		*(e+i) = NULL;
	}
	for (int k = 0; k < numOfCircles; k++) {

		*(e+k) = malloc(sizeof(ecircle));
		ecircle *c = *(e+k);
		float dxx = (rand() % 100);
		float dyy = (rand() % 100);
		dx = dxx/100;
		dy = dyy/100;
		c->x = x + dx;
		c->y = y + dy;
		c->angle = (rand() % 360);
		c->accel = accel;
		c->dx = 0;
		c->dy = 0;
		c->radius = 2;
		c->timer = rand()%500 + 300;
    	
	}

	effect *ef = malloc(sizeof(effect));
	ef->cs = e;
	ef->ls = NULL;
	ef->numOfCircles = numOfCircles;
	ef->numOfLines = 0;
	ef->timer = 0;


	return ef;
}

effect *createShipExplosion(player *p,float accel){

	int numOfLines = 3;
	float xs[p->vertices * 2];
	float ys[p->vertices * 2];
	float dx,dy;
	float x = p->x;
	float y = p->y;
	float vertices = p->vertices;

	int c = 0;
	for (int i = 0; i < p->vertices*2 ; i+=2)
	{
		float dxx = (rand() % 100);
		float dyy = (rand() % 100);
		dx = dxx/100;
		dy = dyy/100;

		xs[i] = p->verticesX[c % p->vertices] + dx;
		xs[i+1] = p->verticesX[(c + 1)% p->vertices] + dx;
		ys[i] = p->verticesY[c% p->vertices] + dy;
		ys[i+1] = p->verticesY[(c + 1)% p->vertices] + dy;
		
		c++;
		

	}


	eline **e;

	e = malloc(p->vertices * sizeof(ecircle));
	for (int i = 0; i < p->vertices; ++i)
	{
		*(e+i) = NULL;
	}

	int d = 0;
	for (int k = 0; k < p->vertices; k++) {

		*(e+k) = malloc(sizeof(eline));
		eline *c = *(e+k);
		c->x1 = xs[d];
		c->x2 = xs[d + 1];
		c->y1 = ys[d];
		c->y2 = ys[d + 1];
		c->angle = (int)(coordsToAngle(p,c->x1,c->y1,c->x2,c->y2)) % 360;
		c->accel = accel;
		c->dx = 0;
		c->dy = 0;
		c->timer = 1000 + rand()%500;
		d += 2;
    	
	}

	effect *ef = malloc(sizeof(effect));
	ef->cs = NULL;
	ef->ls = e;
	ef->numOfCircles = 0;
	ef->numOfLines = vertices;
	ef->timer = 0;

	return ef;
}

void drawEffect(display *d, effect *e){

	for (int i = 0; i < e->numOfCircles; ++i)
	{

		ecircle *c = *(e->cs + i);
		if(c != NULL) circle(d,c->x,c->y,c->radius);

		
	}
	for (int i = 0; i < e->numOfLines; ++i)
	{
		eline *l = *(e->ls + i);
		if(l != NULL) line(d,l->x1,l->y1,l->x2,l->y2);
	}	
}

void closeEffect(effect *e){

	for (int i = 0; i < e->numOfCircles; ++i)
	{
		ecircle *c = *(e->cs + i);
		if (c != NULL) free(c);
		
	}
	
	for (int i = 0; i < e->numOfLines; ++i)
	{
		eline *l = *(e->ls + i);
		if(l != NULL) free(l); 
	}

	free(e);
	e = NULL;
}

void updateEffect(effect *e, int timer, int delta){
	float a = ((2*3.1415)/360);

	for (int i = 0; i < e->numOfCircles; ++i)
	{
		ecircle *c = *(e->cs + i);
		if(c != NULL){
			c->dx += c->accel * cos(c->angle * a) * delta;
			c->dy += c->accel * sin(c->angle * a) * delta;
			c->x += c->dx;
			c->y += c->dy;
			if(timer > c->timer){
				free( *(e->cs + i));
				*(e->cs + i) = NULL;
			} 
		}
	}

	for (int i = 0; i < e->numOfLines; ++i)
	{
		eline *l = *(e->ls + i);
		if(l != NULL){
			l->dx += l->accel * cos(l->angle * a) * delta;
			l->dy += l->accel * sin(l->angle * a) * delta;
			l->x1 += l->dx;
			l->x2 += l->dx;
			l->y1 += l->dy;
			l->y2 += l->dy;
			if(timer > l->timer){
				free( *(e->ls + i));
				*(e->ls + i) = NULL;
			} 
		}
	}
}

#ifdef test_effects

int main(int argc, char const *argv[])
{
	srand(time(NULL));
    display *d;
    d = newDisplay("effectsTest",1000,1000);
    //effect *e = createAsteroidExplosion(500,500,0.01);
    player *p = createPlayer(450,300,45,50);
    effect *e = createShipExplosion(p,0.001);
    int delta = 50/3;
    int timer = 0;
    bool running = true;
    SDL_Event event;
    while (running) {
    	if (SDL_PollEvent(&event)) {
        	if (event.type == SDL_QUIT) {
            	running = false;
        	}

    	}
 
    	if (e != NULL){

    		clear(d);
    		updateEffect(e,timer,delta);
    		drawEffect(d,e);
    		drawPlayer(d,p);
    		show(d);

    	}
    	else closeEffect(e);

    	
    	if(timer == 5000) running = false;
    	timer += delta;
    	pause(d,delta);
	}	
	
    end(d);

    return 0;
}

#endif


