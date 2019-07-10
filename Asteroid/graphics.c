//graphics
#include "include/helper.h"

enum { safe = false };



// If SDL fails, print the SDL error message, and stop the program.
static void fail() {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
}

// Check return values from SDL functions (Integer and Pointer versions).  These
// make error handling less intrusive.
static int I(int n) { if (n < 0) fail(); return n; }
static void *P(void *p) { if (p == NULL) fail(); return p; }

// Create a renderer - in software for safety or hardware for efficiency.
static void createRenderer(display *d) {
    if (safe) {
        SDL_Surface *surface = P(SDL_GetWindowSurface(d->window));
        d->renderer = P(SDL_CreateSoftwareRenderer(surface));
    }
    else d->renderer = P(SDL_CreateRenderer(d->window, -1, 0));
}

// Make recent changes appear on screen.
void show(display *d) {
    if (safe) I(SDL_UpdateWindowSurface(d->window));
    else SDL_RenderPresent(d->renderer);
}

// Create a new display object.
display *newDisplay(char *title, int width, int height) {
    setbuf(stdout, NULL);
    display *d = malloc(sizeof(display));
    I(SDL_Init(SDL_INIT_VIDEO));
    I(TTF_Init());
    int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
    d->window = P(SDL_CreateWindow(title, x, y, width, height, 0));
    createRenderer(d);
    I(SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, 255));
    I(SDL_RenderClear(d->renderer));
    show(d);
    I(SDL_SetRenderDrawColor(d->renderer, 255, 255, 255, 255));
    return d;
}

void line(display *d, int x0, int y0, int x1, int y1) {
    SDL_RenderDrawLine(d->renderer, x0, y0, x1, y1);
    
}

void circle(display *d, int x, int y, int r){
    for (int t = 0; t < 360; t++)
    {
        int a = (360/(2*3.1415));
        int point_x = x + (r * cos(t*a));
        int point_y = y + (r * sin(t*a));
        SDL_RenderDrawPoint(d->renderer, point_x, point_y);
    }
	
}

void colour(display *d, int rgba) {
    Uint8 r = (rgba >> 24) & 0xFF;
    Uint8 g = (rgba >> 16) & 0xFF;
    Uint8 b = (rgba >> 8) & 0xFF;
    Uint8 a = rgba & 0xFF;
    I(SDL_SetRenderDrawColor(d->renderer, r, g, b, a));
}

void clear(display *d) {
    Uint8 r, g, b, a;
    I(SDL_GetRenderDrawColor(d->renderer, &r, &g, &b, &a));
    I(SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE));
    I(SDL_RenderClear(d->renderer));
    //show(d);
    I(SDL_SetRenderDrawColor(d->renderer, r, g, b, a));
}

void pause(display *d, int ms) {
   if (ms > 0) SDL_Delay(ms);
}

void end(display *d) {
    TTF_Quit();
    SDL_Quit();
}

#ifdef test_graphics

int main(int argc, char const *argv[])
{
    display *d;
    d = newDisplay("graphicsTest",1000,1000);
    circle(d,500,500,2);
    line(d,60,60,30,30);
    end(d);

    return 0;
}

#endif
