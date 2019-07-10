//scoreboard.h

int score;

typedef struct{
	TTF_Font *font;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Rect *Message_rect;
	int score;

} scoreboard;



static char *intToScore(int s);

//creates the scoreboard in top left of screen
scoreboard *createScoreboard(display *d, int score);

//creates live counter in top left of screen
scoreboard *createlivesCounter(display *d, int lives);

//creates gameover text at the end of the game
scoreboard *createGameOver(display *d,int width, int height);

//draws a given scoreboard
void drawScoreboard(display *d, scoreboard *s);

//frees a scoreboard
void closeScoreboard(scoreboard *s);
