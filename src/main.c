#include "main.h"

App app;

#undef main

int main()
{
    atexit(&Quit);
    Init();
    Start();
    while (1)
    {
        Game();
    }
}

static void Init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        HANDLE_ERROR("SDL_Init");
    } // 初始化，对应SDL_QUIT()
    app.window = SDL_CreateWindow("Playground Run!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    if (app.window == NULL)
    {
        HANDLE_ERROR("SDL_CreateWindow");
    }
    app.rdr = SDL_CreateRenderer(app.window, -1, 0);
    if (app.rdr == NULL)
    {
        HANDLE_ERROR("SDL_CreateRenderer");
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        HANDLE_ERROR("IMG_Init");
    }
    if (TTF_Init() < 0)
    {
        HANDLE_ERROR("TTF_Init");
    }
    Init_Game();
    app.win_rect.x = 0;
    app.win_rect.y = 0;
    app.win_rect.h = WIN_H;
    app.win_rect.w = WIN_W;
}
static void Quit(void)
{
    SDL_Quit();
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.rdr);
    IMG_Quit();
    TTF_Quit();
    // SDL_Log("Exit Success\n"); // for testing purposes only
}
static void Init_Game()
{
    app.character.acceleration_y = -10;
    app.character.mode = CHARACTER_MODE_RUN;
    app.character.speed_y = 0;
    app.character.character.x = -SQR_LEN;
    app.character.character.y = LINE_TWO_Y;
    app.character.character.w = SQR_LEN;
    app.character.character.h = SQR_LEN;
    app.speed = 10;
    app.score_board.unchange.x = 0;
    app.score_board.unchange.y = 0;
    app.score_board.unchange.w = SCORE_BOARD_W;
    app.score_board.unchange.h = SCORE_BOARD_H;
    app.score_board.score.x = SCORE_BOARD_W;
    app.score_board.score.y = 0;
    app.score_board.score.w = SCORE_BOARD_W;
    app.score_board.score.h = SCORE_BOARD_H;
}