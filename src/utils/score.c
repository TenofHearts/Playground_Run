#include "utils/score.h"

void Score_Update()
{
#ifndef DISPLAY_TIME_
    const SDL_Color fg_w = {255, 255, 255, 255};
    char score_stored[20] = {0};
    sprintf(score_stored, "Score: %d", app.score);
    app.score_board.w = 20 * strlen(score_stored);
    Print_Text(app.score_board, fg_w, score_stored, 50);
#endif
}