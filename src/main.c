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
    Init_Window();
}
static void Quit(void)
{
    SDL_Quit();
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.rdr);
    IMG_Quit();
    TTF_Quit();
    Destroy_Texture();
    Deinit_Audio();
    free(app.obstacle_texture);
    SDL_Log("Exit Success\n"); // for testing purposes only
}