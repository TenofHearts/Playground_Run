#include "utils/time.h"

void Frame_Control()
{
    Uint32 temp = SDL_GetTicks64() - app.time.frame_time;
    SDL_Delay(FT > temp ? FT - temp : FT);
}

void Display_Frame()
{
#ifdef DISPLAY_TIME_
    Uint32 temp = SDL_GetTicks64() - app.time.frame_time;
    int fps = 1000 / temp;
    char fps_stored[10] = {0};
    sprintf(fps_stored, "FPS: %d", fps);
    app.score_board.w = strlen(fps_stored) * 10;
    SDL_Color fg_w = {255, 255, 255, 255};
    Print_Text(app.score_board, fg_w, fps_stored, 50);
#endif
}