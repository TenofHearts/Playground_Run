#include "utils/score.h"

void Score_Update(int score)
{
    SDL_Color fg_b = {0, 0, 0, 255};
    Print_Text(app.score_board.unchange, fg_b, "Score:", 50);
    char score_stored[10] = {0};
    sprintf(score_stored, "%d", score);
    app.score_board.score.w = 20 * strlen(score_stored);
    Print_Text(app.score_board.score, fg_b, score_stored, 50);
}