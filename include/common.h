#ifndef SDL_INCLUDE_COMMON_H
#define SDL_INCLUDE_COMMON_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "utils/print_text.h"
#include "utils/score.h"
#include "utils/init_game.h"
#include "utils/time.h"
#include "utils/audio.h"

#define HANDLE_ERROR(msg)                         \
    SDL_Log(msg " failed: %s\n", SDL_GetError()); \
    exit(EXIT_FAILURE);

// #define DISPLAY_TIME_

#define WIN_W 830
#define WIN_H 450
#define SQR_LEN 100
#define HITBOX_LEN 25
#define CHARACTER_START 30
#define FOG_X 500
#define MAGNET_X 500

#define LANE_ONE_Y 60
#define LANE_TWO_Y 175
#define LANE_THREE_Y 290

#define CHARACTER_MODE_RUN 0
#define CHARACTER_MODE_JUMP 1
#define CHARACTER_MODE_DUCK 2

#define SCORE_BOARD_H 40
#define SCORE_BOARD_W 100

#define ESC 41
#define SPACE 44
#define R 21
#define W 26
#define A 4
#define S 22
#define D 7
#define T 23
#define B 5
#define M 16
#define UP 82
#define LEFT 80
#define DOWN 81
#define RIGHT 79

#define FR 50
#define FT (1000 / FR)

#define OBST_JUMP 0
#define OBST_DUCK 1
#define OBST_WALL 2
#define OBST_COIN 3
#define OBST_SHIELD 4
#define OBST_FOG 5
#define OBST_FOOTBALL 6
#define OBST_MAGNET 7
#define MOVING_FOOTBALL 1000
#define NOTHING 2000
#define OBST_NUM 8

#define INVINCIBLE_TIME 15000
#define FOG_TIME 7000
#define MAGNET_TIME 5000

#define DISTANCE 14

typedef struct
{
    Uint32 duck_time, magnet_time, invincible_time;
} Time_character;

typedef struct
{
    int mode, speed_y, acceleration_y, lane, invincible, death, magnet, score;
    SDL_Rect character;
    SDL_Texture *texture;
    Time_character time_character;
} character;

typedef struct
{
    int type, lane;
    SDL_Rect obstacle, hitbox;
    SDL_Texture *texture;
} obstacle;

typedef struct obstacle_node obstacle_node;

struct obstacle_node
{
    obstacle obst;
    obstacle_node *next;
};

typedef struct
{
    obstacle_node *head, *tail;
    int prev_type;
} runway;

typedef struct
{
    Uint32 frame_time, fog_time;
} Time;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *rdr;
    character *character;
    runway runway;
    SDL_Rect win_rect;
    int speed;
    SDL_Rect score_board;
    SDL_Texture *background_texture;
    Time time;
    SDL_Texture **obstacle_texture;
    int baby_mode;
    SDL_Texture *nothing;
    int mute;
    int player;
    int fog;
    SDL_Texture *fog_texture;
} App;

extern App app;

#endif