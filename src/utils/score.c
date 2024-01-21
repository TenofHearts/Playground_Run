#include "utils/score.h"

int stage = 0;

void Score_Update()
{
    Score_Handle();
#ifndef DISPLAY_TIME_
    const SDL_Color fg_w = {255, 255, 255, 255};
    char score_stored[20] = {0};
    sprintf(score_stored, "Score: %d", app.score);
    app.score_board.w = 20 * strlen(score_stored);
    Print_Text(app.score_board, fg_w, score_stored, 50);
#endif
}

void Score_Handle()
{
    if (stage <= 0 && app.score > 20)
    {
        stage = 1;
        app.speed = 10;
    }
    if (stage <= 1 && app.score > 100)
    {
        stage = 2;
        app.speed = 20;
    }
    if (stage <= 2 && app.score > 150)
    {
        stage = 3;
        app.speed = 25;
    }
}