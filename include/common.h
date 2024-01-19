#ifndef SDL_INCLUDE_COMMON_H
#define SDL_INCLUDE_COMMON_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "utils/print_text.h"
#include "utils/character_motion.h"
#include "utils/score.h"

#define HANDLE_ERROR(msg)                         \
    SDL_Log(msg " failed: %s\n", SDL_GetError()); \
    exit(EXIT_FAILURE);
#define WIN_W 830
#define WIN_H 450
#define SQR_LEN 100
#define CHARACTER_START 30

#define LINE_ONE_Y 60
#define LINE_TWO_Y 175
#define LINE_THREE_Y 290

#define CHARACTER_MODE_RUN 0
#define CHARACTER_MODE_JUMP 1
#define CHARACTER_MODE_DUCK 2

#define SCORE_BOARD_H 40
#define SCORE_BOARD_W 100

#define ESC 41
#define SPACE 44
#define R 21

typedef struct
{
    int mode, speed_y, acceleration_y;
    SDL_Rect character;
} character;

typedef struct
{
    int type;
    SDL_Rect obstacle;
} obstacle;

typedef struct
{
    obstacle obst;
    obstacle *next;
} runway;

typedef struct
{
    SDL_Rect score, unchange;
} score_board;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *rdr;
    character character;
    runway *head;
    SDL_Rect win_rect;
    int speed;
    score_board score_board;
} App;

extern App app;

#endif