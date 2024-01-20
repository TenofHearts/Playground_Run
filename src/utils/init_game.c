#include "utils/init_game.h"

void Init_Game()
{
    app.character.acceleration_y = -10;
    app.character.mode = CHARACTER_MODE_RUN;
    app.character.speed_y = 0;
    app.character.character.x = -SQR_LEN;
    app.character.character.y = LINE_TWO_Y;
    app.character.character.w = SQR_LEN;
    app.character.character.h = SQR_LEN;
    app.speed = 10;
}
void Init_Window()
{
    app.win_rect.x = 0;
    app.win_rect.y = 0;
    app.win_rect.h = WIN_H;
    app.win_rect.w = WIN_W;
    app.score_board.unchange.x = 0;
    app.score_board.unchange.y = 0;
    app.score_board.unchange.w = SCORE_BOARD_W;
    app.score_board.unchange.h = SCORE_BOARD_H;
    app.score_board.score.x = SCORE_BOARD_W;
    app.score_board.score.y = 0;
    app.score_board.score.w = SCORE_BOARD_W;
    app.score_board.score.h = SCORE_BOARD_H;
}