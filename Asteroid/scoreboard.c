//scoreboard
#include "include/helper.h"

SDL_Color White = {255, 255, 255};

static char *intToScore(int score){

	if(score<=0){
		char *c = malloc((10)*sizeof(char));
		strcpy(c,"score 0");
		return c;
	}
	else 
	{
		
		int size = 10 + (int)log10(score);
		char *d = malloc(size*sizeof(char));
		char *c = malloc((size+10)*sizeof(char));
		sprintf(d, "%d", score);
		sprintf(c, "score ");
		strcat(c,d);
		free(d);
		return c;
	}	
}

scoreboard *createScoreboard(display *d, int score){
	scoreboard *s = malloc(sizeof(scoreboard));
	
	TTF_Font* Sans = TTF_OpenFont("ARCADECLASSIC.ttf", 900);
	TTF_SetFontHinting(Sans, TTF_HINTING_MONO);

	char *c = malloc(30*sizeof(char));
	sprintf(c,"score %d",score);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, c , White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	free(c);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(d->renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect *Message_rect = malloc(sizeof(SDL_Rect)); //create a rect
	Message_rect->x = 10;  //controls the rect's x coordinate 
	Message_rect->y = 10; // controls the rect's y coordinte
	Message_rect->w = 100; // controls the width of the rect
	Message_rect->h = 30; // controls the height of the rect

	
	s->font = Sans;
	s->surfaceMessage = surfaceMessage;
	s->Message = Message;
	s->Message_rect = Message_rect;
	s->score = score;

	return s;
}

scoreboard *createlivesCounter(display *d, int lives){
	scoreboard *s = malloc(sizeof(scoreboard));
	
	TTF_Font* Sans = TTF_OpenFont("ARCADECLASSIC.ttf", 900);
	TTF_SetFontHinting(Sans, TTF_HINTING_MONO);

	char *c = malloc(10*sizeof(char));
	
	sprintf(c,"lives %d",lives);
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, c , White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	free(c);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(d->renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect *Message_rect = malloc(sizeof(SDL_Rect)); //create a rect
	Message_rect->x = 10;  //controls the rect's x coordinate 
	Message_rect->y = 40; // controls the rect's y coordinte
	Message_rect->w = 100; // controls the width of the rect
	Message_rect->h = 30; // controls the height of the rect

	
	s->font = Sans;
	s->surfaceMessage = surfaceMessage;
	s->Message = Message;
	s->Message_rect = Message_rect;
	s->score = lives;

	return s;
}

scoreboard *createGameOver(display *d,int width, int height){

	scoreboard *s = malloc(sizeof(scoreboard));
	
	TTF_Font* Sans = TTF_OpenFont("ARCADECLASSIC.ttf", 900);
	TTF_SetFontHinting(Sans, TTF_HINTING_MONO);

	char *c = malloc(10*sizeof(char));
	
	sprintf(c,"Game Over");
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, c , White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	free(c);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(d->renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect *Message_rect = malloc(sizeof(SDL_Rect)); //create a rect
	Message_rect->x = (width/2)-100;  //controls the rect's x coordinate 
	Message_rect->y = (height/2)-30; // controls the rect's y coordinte
	Message_rect->w = 200; // controls the width of the rect
	Message_rect->h = 60; // controls the height of the rect

	
	s->font = Sans;
	s->surfaceMessage = surfaceMessage;
	s->Message = Message;
	s->Message_rect = Message_rect;
	s->score = 0;

	return s;
}

void drawScoreboard(display *d, scoreboard *s){

	SDL_RenderCopy(d->renderer, s->Message, NULL, s->Message_rect); 
}

void closeScoreboard(scoreboard *s){
	SDL_FreeSurface(s->surfaceMessage);
	SDL_DestroyTexture(s->Message);
	TTF_CloseFont(s->font);
	free(s->Message_rect);
}

#ifdef test_scoreboard

int main(int argc, char const *argv[])
{


	display *d;
    d = newDisplay("graphicsTest",1000,1000);
    float delta = 50/3;

    for (int i = 0; i < 2500; ++i)
    {
    	clear(d);
    	drawScoreboard(d,i);
    	show(d);	
    	pause(d,delta/2);
    	clear(d);

      
      
      
      
      



    }

    




	

	end(d);

	return 0;
}

#endif
