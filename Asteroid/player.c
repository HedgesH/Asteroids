//player
#include "include/helper.h"

player *createPlayer(float x, float y, float angle, float size){
  player *p = malloc(sizeof(player));
  p->angle = angle;
  p->life = 100;
  p->x = x;
  p->y = y;
  p->dx = 0;
  p->dy = 0;
  p->size = size;
  p->radius = size;
  p->vertices = 4;
  p->destroy = 0;

  float x1,x2,x3,y1,y2,y3;
  coords c;
  c = rotateDefaultTriangle(angle,size);
  x1 = p->x + c.x1;
  x2 = p->x + c.x2;
  x3 = p->x + c.x3;
  y1 = p->y + c.y1;
  y2 = p->y + c.y2;
  y3 = p->y + c.y3;
  p->verticesX[0] = x1;
  p->verticesX[1] = x2;
  p->verticesX[2] = x3;
  p->verticesX[3] = x;

  p->verticesY[0] = y1;
  p->verticesY[1] = y2;
  p->verticesY[2] = y3;
  p->verticesY[3] = y;
  return p;
}

player *createBullet(float x,float y, float angle, float radius){

  player *b = malloc(sizeof(player));
  b->x = x;
  b->y = y;
  b->dx = 0;
  b->dy = 0;
  b->radius = radius;
  b->angle = angle;
  b->destroy = 0;
  return b;
}

void accelX(player *p, float a, float delta,float maxspeed){
  p->dx += a*delta;

  if (p->dx > maxspeed) p->dx = maxspeed;
  if(p->dx < (-1)*maxspeed) p->dx = (-1)*maxspeed;
  
  p->x += p->dx;
}

void accelY(player *p,float a, float delta,float maxspeed){
  p->dy += a*delta;

  if (p->dy > maxspeed) p->dy = maxspeed;
  if(p->dy < (-1)*maxspeed) p->dy = (-1)*maxspeed;

  p->y += p->dy;
}

void rotateShip(player *p, int angle){p->angle += angle % 360;}

void accelForward(player *p, float accel, float delta, float maxspeed){
  float a = ((2*3.1415)/360);
  p->dx += accel * cos(p->angle * a) * delta;
  p->dy += accel * sin(p->angle * a) * delta;
  if((p->dx*p->dx) + (p->dy * p->dy) > maxspeed * maxspeed){
    p->dx -= accel * cos(p->angle * a) * delta;
    p->dy -= accel * sin(p->angle * a) * delta;
  }

  if( p->dx * p->dx  > 0) p->dx -= p->dx/100;
  if( p->dy * p->dy > 0)  p->dy -= p->dy/100;

 
 
  p->x += p->dx;
  p->y += p->dy;

  float x1,x2,x3,y1,y2,y3;
  coords c;
  c = rotateDefaultTriangle(p->angle,p->size);
  x1 = p->x + c.x1;
  x2 = p->x + c.x2;
  x3 = p->x + c.x3;
  y1 = p->y + c.y1;
  y2 = p->y + c.y2;
  y3 = p->y + c.y3;
  p->verticesX[0] = x1;
  p->verticesX[1] = x2;
  p->verticesX[2] = x3;
  p->verticesX[3] = p->x;

  p->verticesY[0] = y1;
  p->verticesY[1] = y2;
  p->verticesY[2] = y3;
  p->verticesY[3] = p->y;
}

void boundary(player *p, float width, float height){
  if(p->x < 0 - 2*(p->size) ) p->x = width + 2*(p->size);
  if(p->x > width + 2*(p->size) ) p->x = 0 - 2*(p->size);
  if(p->y < 0 - 2*(p->size)) p->y = height + 2*(p->size) ;
  if(p->y > height + 2*(p->size) ) p->y = 0 - 2*(p->size);
}

void boundaryBullet(player *a, float width, float height){
  

  int x = a->x;
  int y = a->y;
  //printf("%d --- %d\n",x,y );

    

  if(x < 0 ) a->destroy = 1;
  if(x > width ) a->destroy = 1;
  if(y < 0 ) a->destroy = 1;
  if(y > height ) a->destroy = 1; 
}

void shoot(player *p, int speed){
  float a = ((2*3.1415)/360);
  p->dx = speed * cos(p->angle * a);
  p->dy = speed * sin(p->angle * a);
  p->x += p->dx;
  p->y += p->dy;
}

coords rotate(float angle, float x, float y){
  coords c;
  float a = ((2*3.1415)/360);
  c.x1 = (cos(angle*a)*x) - (sin(angle*a)*y);
  c.y1 = (sin(angle*a)*x) + (cos(angle*a)*y);
  return c;
}

coords rotateDefaultTriangle(float angle, float size){
  coords t;
  coords c;
  c = rotate(angle-90,0,size);
  t.x1 = c.x1;
  t.y1 = c.y1;
  c = rotate(angle-90, size*((sqrt(3)/2)),-0.5*size);
  t.x2 = c.x1;
  t.y2 = c.y1;
  c = rotate(angle-90, -1*(size*((sqrt(3)/2))),-0.5*size);
  t.x3 = c.x1;
  t.y3 = c.y1;

  return t;
}

void drawPlayer(display *d, player *p){
	float x1,x2,x3,y1,y2,y3;
  float a = ((2*3.1415)/360);
  coords c;
  c = rotateDefaultTriangle(p->angle,p->size);
	x1 = p->x + c.x1;
  x2 = p->x + c.x2;
  x3 = p->x + c.x3;
  y1 = p->y + c.y1;
  y2 = p->y + c.y2;
  y3 = p->y + c.y3;
  //printf("%d\n",x1 );



  line(d,x1,y1,x2,y2);
  line(d,x2,y2,p->x,p->y);
  line(d,p->x,p->y,x3,y3);
  line(d,x3,y3,x1,y1);
  //line(d,p->x,p->y,p->x + p->size * cos(p->angle * a),p->y + p->size * sin(p->angle * a));
}

void drawBullet(display *d,player *b){
  for (int i = b->radius; i > 0; --i)
  {
    circle(d,b->x,b->y,i);
  }
}

#ifdef test_players

int main(int argc, char const *argv[])
{
    display *d;
    d = newDisplay("graphicsTest",1000,1000);
    float delta = 50/3;

    player *p = createPlayer(500,500,90,40);
    player *b = createBullet(500,500,0,30);
    for (int i = 0; i < 500; ++i)
    {
    
      
      clear(d);
      shoot(b,15);
      boundary(b,1000,1000);
      drawBullet(d,b);
      show(d);
      

      pause(d,(int)delta);
      
      
      



    }

    clear(d);
    end(d);

    return 0;
}

#endif
