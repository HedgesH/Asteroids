//helper.h

#define max_asteroids 30
#define max_speed 5
#define widths 1080
#define heights 720
#define live_counter 3
#define ship_size 15
#define asteroid_maxr 40
#define asteroid_speed 2
#define smallAsteroid_maxr 20
#define ship_respawn_timer 1000
#define ship_spawn_angle 0
#define ship_accel 0.005
#define ship_rotate_speed 3
#define bullet_speed 10 
#define bullet_radius 2
#define score_increase 1000
#define score_decrease 1000
#define frames_per_second 60
#define aexplosion_accel 0.01
#define sexplosion_accel 0.002

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "graphics.h"
#include "player.h"
#include "scoreboard.h"
#include "asteroid.h"
#include "effects.h"
#include "asteroidGame.h"


