#include "utils/score.h"

int stage = 0;

SDL_Rect Score_rect = {0, 0, SCORE_BOARD_W, SCORE_BOARD_H};

void Score_Update()
{
    Score_Handle(0);
#ifndef DISPLAY_TIME_
    if (app.player == 1)
    {
        const SDL_Color fg_w = {255, 255, 255, 255};
        char score_stored[10] = {0};
        Print_Text(Score_rect, fg_w, "Score:", 50);
        sprintf(score_stored, "%d", app.character[0].score);
        app.score_board.w = 20 * strlen(score_stored);
        Print_Text(app.score_board, fg_w, score_stored, 50);
    }
#endif
}

void Score_Handle(int mode)
{
    int score = app.character[0].score > app.character[1].score ? app.character[0].score : app.character[1].score;
    if (mode)
    {
        stage = 0;
    }
    if (app.baby_mode)
    {
        if (score <= 100 && stage > 0)
        {
            stage = 0;
        }
        if (stage <= 0 && score > 100)
        {
            stage = 1;
            app.speed = 6;
        }
        if (stage <= 1 && score > 250)
        {
            stage = 2;
            app.speed = 7;
        }
        if (stage <= 2 && score > 500)
        {
            stage = 3;
            app.speed = 8;
        }
        if (stage <= 4 && score > 1000)
        {
            stage = 4;
            app.speed = 10;
        }
        if (stage <= 5 && score > 2000)
        {
            stage = 6;
            app.speed = 12;
        }
    }
    else
    {
        if (score <= 100 && stage > 0)
        {
            stage = 0;
        }
        if (stage <= 0 && score > 100)
        {
            stage = 1;
            app.speed = 7;
        }
        if (stage <= 1 && score > 250)
        {
            stage = 2;
            app.speed = 9;
        }
        if (stage <= 2 && score > 500)
        {
            stage = 3;
            app.speed = 12;
        }
        if (stage <= 4 && score > 1000)
        {
            stage = 4;
            app.speed = 15;
        }
        if (stage <= 5 && score > 2000)
        {
            stage = 6;
            app.speed++;
        }
        if (stage == 6 && app.speed < 20)
        {
            app.speed++;
        }
    }
}

void Baby_Mode()
{
    SDL_Rect baby_mode = {730, 410, SCORE_BOARD_W, SCORE_BOARD_H};
    SDL_Color fg_w = {255, 255, 255, 255};
    if (app.baby_mode)
    {
        Print_Text(baby_mode, fg_w, "Baby Mode", 30);
    }
}