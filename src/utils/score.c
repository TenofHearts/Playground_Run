#include "utils/score.h"

int stage = 0;

SDL_Rect Score_rect = {0, 0, SCORE_BOARD_H, SCORE_BOARD_W};

void Score_Update()
{
    Score_Handle();
#ifndef DISPLAY_TIME_
    const SDL_Color fg_w = {255, 255, 255, 255};
    char score_stored[10] = {0};
    Print_Text(Score_rect, fg_w, "Score:", 50);
    sprintf(score_stored, "%d", app.score);
    app.score_board.w = 20 * strlen(score_stored);
    Print_Text(app.score_board, fg_w, score_stored, 50);
#endif
}

void Score_Handle()
{
    if (app.score <= 20 && stage > 0)
    {
        stage = 0;
    }
    if (stage <= 0 && app.score > 100)
    {
        stage = 1;
        app.speed = 7;
    }
    if (stage <= 1 && app.score > 250)
    {
        stage = 2;
        app.speed = 9;
    }
    if (stage <= 2 && app.score > 500)
    {
        stage = 3;
        app.speed = 12;
    }
    if (stage <= 4 && app.score > 1000)
    {
        stage = 4;
        app.speed = 15;
    }
    if (stage <= 5 && app.score > 2000)
    {
        stage = 6;
        app.speed++;
    }
    if (stage == 6 && app.speed < 20)
    {
        app.speed++;
    }
}