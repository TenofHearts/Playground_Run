#include "utils/score.h"

void Score_Update(int score)
{
    SDL_Color fg_w = {255, 255, 255, 255};
    Print_Text(app.score_board.unchange, fg_w, "Score:", 50);
    char score_stored[10] = {0};
    sprintf(score_stored, "%d", score);
    app.score_board.score.w = 20 * strlen(score_stored);
    Print_Text(app.score_board.score, fg_w, score_stored, 50);
}