//asteroidGame.h

enum gameState {Game,Pause,Quit};
enum keys {Left,Right,Up,Down,Space,Esc,None};

bool running;
int delta;

typedef struct {
  player *ship;
  player *bullet;
  display *d;
  enum gameState gameState;
  int score;
  int numOfAsteroids;
  int lives;
  int timer;
  bool despawnedShip;
  effect *aexplode;
  effect *sexplode;
  scoreboard *scoreboard;
  scoreboard *livesCounter;
  asteroid **asteroid;
  SDL_Event *e;

} gameStateManager;

bool collisionDetect(player *p, asteroid *a);

enum keys *processKeys(SDL_Window *window, SDL_Event *event);

//pausegame

void doPause();

//playgame

void loadGame();
void doGame();
void drawGame();
void checkGame();
void endGame();

//menugame

void loadMenu();
void doMenu();
void drawMenu();
void checkMenu();
void endMenu();

void checkGameState(gameStateManager *g);

//main();

