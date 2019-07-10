//asteroidGame.h
#include "include/helper.h"

bool collisionDetect(player *p, asteroid *a){

	float xp = p->x;
	float yp = p->y;
	float xa = a->x;
	float ya = a->y;
	float ra =  a->minr;
	float x = xp - xa;
	float y = yp - ya;

	if ((x*x) + (y*y) <= ra*ra)
	{
		return true;
	}

	return false;
}

enum keys *processKeys(SDL_Window *window, SDL_Event *event) {
  // Looping through all Events on every frame of the main Event Loop. Switch on the Event's "Type."

	enum keys *k = malloc(6*sizeof(enum keys));
	for (int i = 0; i < 6; ++i)
	{
		*(k+i) = None;
	}
	int counter = 0;

	const Uint8 *keystates = SDL_GetKeyboardState( NULL );
  
    switch (event->type) {

	  case SDL_WINDOWEVENT_CLOSE: 
	    if (window) {
	      
	      SDL_DestroyWindow(window);
	      *(k+counter) = Esc;
	      counter++;
	    }
	    

	  case SDL_KEYDOWN: 

        //If up is pressed
        if( keystates[ SDL_SCANCODE_UP ] )
        {
            *(k+counter) = Up;
	      	counter++;
        }

        //If down is pressed
        if( keystates[ SDL_SCANCODE_DOWN ] )
        {
            *(k+counter) = Down;
	      	counter++;
        }

        //If left is pressed
        if( keystates[ SDL_SCANCODE_LEFT ] )
        {
            *(k+counter) = Left;
	      	counter++;
        }

        //If right is pressed
        if( keystates[ SDL_SCANCODE_RIGHT ] )
        {
            *(k+counter) = Right;
	      	counter++;
        }

        if( keystates[ SDL_SCANCODE_SPACE ] )
        {
            *(k+counter) = Space;
	      	counter++;
        }

         if( keystates[ SDL_SCANCODE_ESCAPE ] )
        {
            *(k+counter) = Esc;
	      	counter++;
        }

      
    }

    return k;
}

//pausegame

void doPause(gameStateManager *g){
	
	bool running2 = true;
	enum keys *k = processKeys(g->d->window,g->e);
	while(running2){
		running2 = false;
		for (int i = 0; i < 6; ++i)
		{
			if (*(k+i) != None) running2 = true;
		}
		pause(g->d,delta);
		SDL_PollEvent(g->e);
		k = processKeys(g->d->window,g->e);
	}
	running2 = true;
	while(running2){
		SDL_PollEvent(g->e);
		k = processKeys(g->d->window,g->e);
		for (int i = 0; i < 6; ++i)
		{
			if (*(k+i) == Esc){
				running2 = false;
				g->gameState = Quit;
				break;
			}  
			if( *(k+i) != None){
				running2 = false; 
				g->gameState = Game;
			}	
		}
		pause(g->d,delta);

	}
}

//playgame

void loadGame(gameStateManager *g){
	clear(g->d);

	g->ship = createPlayer(widths/2,heights/2,0,ship_size);
	g->bullet = NULL;
	g->scoreboard = createScoreboard(g->d,0);
	g->livesCounter = createlivesCounter(g->d,3);
	g->score = 0;
	g->scoreboard->score = 0;
	g->livesCounter->score = live_counter;
	g->numOfAsteroids = max_asteroids/2;
	g->lives = live_counter;
	g->despawnedShip = false;
	g->aexplode = NULL;
	g->sexplode = NULL;
	g->timer = -1;

	asteroid **asteroid;

	asteroid = malloc(max_asteroids * sizeof(asteroid));
	for (int i = 0; i < max_asteroids; ++i)
	{
		*(asteroid+i) = NULL;
	}
	for (int k = 0; k < g->numOfAsteroids; k++) {
    	*(asteroid+k) = generateAsteroid(widths,heights,asteroid_maxr,asteroid_speed);
    	
	}	

	g->asteroid = asteroid;
}

void doGame(gameStateManager *g){

	//respawn ship

	if (g->timer >= ship_respawn_timer)
	{
		if(g->despawnedShip == true){

			g->despawnedShip = false;
			int x = widths/2;
			int y = heights/2;

			for (int i = 0; i < max_asteroids; ++i)
			{
				asteroid *a = *(g->asteroid + i);
				if(a != NULL){
					moveAsteroid(*(g->asteroid + i));
					boundaryAsteroid(*(g->asteroid + i));
					x = x - a->x;
					y = y - a->y;
					if((x*x) + (y*y) < 1000) g->despawnedShip = true;
				}
			}

			if(g->despawnedShip == false ) g->ship = createPlayer(widths/2,heights/2,ship_spawn_angle,ship_size); g->timer = -1;
		}
	}



	enum keys *k = processKeys(g->d->window,g->e);
	
	//key process

	for (int i = 0; i < 6; ++i)
	{

		switch (*(k+i)){

			case Left:
				if (g->despawnedShip == false){ rotateShip(g->ship, -1*ship_rotate_speed);}
				break;
				
			case Right:
				if (g->despawnedShip == false){ rotateShip(g->ship, ship_rotate_speed);}
				break;
				
			case Up:
				if (g->despawnedShip == false){ accelForward(g->ship,ship_accel,delta,max_speed);}
				break;

			case Down:
				break;
				
			case Space:
				if(g->bullet == NULL){
					if (g->despawnedShip == false) {g->bullet = createBullet(g->ship->x,g->ship->y,g->ship->angle,bullet_radius);}
				} 
				break;
				
			case Esc:
				g->gameState = Pause;
				return;
			case None:
				if (g->despawnedShip == false){ accelForward(g->ship,0,delta,max_speed); rotateShip(g->ship, 0);}
				break;

		}
	}

	//update bullet

	if(g->bullet != NULL){
		shoot(g->bullet, bullet_speed);
		boundaryBullet(g->bullet,widths,heights);
		//bullet hitting asteroid
		if(g->bullet->destroy == 1){
			free(g->bullet);
			g->bullet = NULL;
		}
	}

	//update asteroid
	for (int i = 0; i < max_asteroids; ++i)
	{
		if(*(g->asteroid + i) != NULL){
			moveAsteroid(*(g->asteroid + i));
			boundaryAsteroid(*(g->asteroid + i));
			if(g->bullet != NULL){
				if(collisionDetect(g->bullet,*(g->asteroid + i))){
					asteroid *a = *(g->asteroid + i);
					if(a->maxr > smallAsteroid_maxr){
						float x = a->x;
						float y = a->y;
						free(*(g->asteroid + i));
						*(g->asteroid + i) = generateAsteroid(widths,heights,smallAsteroid_maxr,asteroid_speed);
						a = *(g->asteroid + i);
						a->x = x;
						a->y = y;
						for (int i = 0; i < max_asteroids; ++i)
						{
							if (*(g->asteroid + i) == NULL)
							{
								*(g->asteroid + i) = generateAsteroid(widths,heights,smallAsteroid_maxr,asteroid_speed);
								a = *(g->asteroid + i);
								a->x = x + smallAsteroid_maxr;
								a->y = y + smallAsteroid_maxr;
								g->numOfAsteroids ++;
								break;
							}
						}
					}
					else{
						free(*(g->asteroid + i));
						*(g->asteroid + i) = NULL;
						g->numOfAsteroids --;
					}
					g->aexplode = createAsteroidExplosion(g->bullet->x,g->bullet->y,aexplosion_accel);
					free(g->bullet);
					g->bullet = NULL;
					g->score += score_increase;
				}
			}
		}
		if (g->despawnedShip == false)
		{
			if(*(g->asteroid + i) != NULL){
				if(collisionDetect(g->ship,*(g->asteroid + i))){
					g->sexplode = createShipExplosion(g->ship,sexplosion_accel);
					g->score -= score_decrease;
					free(*(g->asteroid + i));
					*(g->asteroid + i) = NULL;
					g->numOfAsteroids --;
					g->lives --;
					g->despawnedShip = true;
					g->timer = 0;
					free(g->ship);
					g->ship = NULL;

				}
			}
		}

	}

	//collision detect
	if (g->despawnedShip == false) boundary(g->ship,widths,heights);
	
	//score
	if (g->score < 0) g->score = 0;
	if (g->score != g->scoreboard->score)
	{
		closeScoreboard(g->scoreboard);
		free(g->scoreboard);
		g->scoreboard = createScoreboard(g->d,g->score);
	}

	//lives
	if (g->lives < 0) g->lives = 0;
	if (g->lives != g->livesCounter->score)
	{
		closeScoreboard(g->livesCounter);
		free(g->livesCounter);
		g->livesCounter = createlivesCounter(g->d,g->lives);
	}

	//game over
	if (g->lives == 0 || g->numOfAsteroids == 0)
	{
		scoreboard *s = createGameOver(g->d,widths,heights);
		drawGame(g);
		drawScoreboard(g->d,s);
		show(g->d);
		doPause(g);
		g->gameState = Quit;
		closeScoreboard(s);
		free(s);
		return;
	}

	//update effect
	if(g->aexplode != NULL){
		updateEffect(g->aexplode,g->aexplode->timer,delta);
    	g->aexplode->timer += delta;

	}
	if(g->sexplode != NULL){
		updateEffect(g->sexplode,g->sexplode->timer,delta);
    	g->sexplode->timer += delta;
		
	}
	if(g->timer >= 0) g->timer += delta;

	//draw game
	drawGame(g);
}

void drawGame(gameStateManager *g){

	clear(g->d);

	if(g->bullet != NULL){
		drawBullet(g->d,g->bullet);
	}

	for (int i = 0; i < max_asteroids; ++i)
	{
		if(*(g->asteroid + i) != NULL) drawAsteroid(g->d,*(g->asteroid + i));
	}

	if(g->aexplode != NULL){
    	drawEffect(g->d,g->aexplode);
	}
	if(g->sexplode != NULL){
    	drawEffect(g->d,g->sexplode);
	}

	if(g->despawnedShip == false){
		drawPlayer(g->d,g->ship);
	}

	drawScoreboard(g->d,g->scoreboard);
	drawScoreboard(g->d,g->livesCounter);
}

void endGame(gameStateManager *g){
	free(g->ship);
	if(g->bullet != NULL) free(g->bullet); 
	for (int i = 0; i < max_asteroids; ++i)
	{
		if(*(g->asteroid +i) != NULL)free(*(g->asteroid +i));
	}
	clear(g->d);
}

void checkGame(gameStateManager *g){
	switch(g->gameState){

		case Quit :
			endGame(g);
			running = false;
			break;

		default :
			break;
	} 
}

//game state checker
void checkGameState(gameStateManager *g){

	switch(g->gameState){

		case Game :
			doGame(g);
			checkGame(g);
			break;

		case Quit:
			running = false;

		case Pause :
			doPause(g);
			checkGame(g);
			break;

		default :
			break;


	}
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
  	gameStateManager *g;
  	g = malloc(sizeof(gameStateManager));
  	g->d = newDisplay("Asteroids",widths,heights);
  	g->gameState = Game;
	running = true;
	delta = 1000/frames_per_second;
	loadGame(g);
	SDL_Event *event;
	event = malloc(sizeof(SDL_Event));
	while (running) {
    	if (SDL_PollEvent(event)) {
        	if (event->type == SDL_QUIT) {
            	running = false;
        	}
        	g->e = event;
    	}
    	checkGameState(g);
    	show(g->d);
    	pause(g->d,delta);
	}	
	pause(g->d,300);
	printf("end of game\n");
	end(g->d);
	return 0;
}

