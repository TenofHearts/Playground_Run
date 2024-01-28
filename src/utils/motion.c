#include "utils/motion.h"

void Background_Motion()
{
    app.win_rect.x = (app.win_rect.x + app.speed) % 2000;
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
}

void Motion()
{
    SDL_RenderClear(app.rdr);
    Background_Motion();
    Obstacle_Motion();
    Character_Motion();
    Score_Update();
    Baby_Mode();
    Display_Frame();
    Deal_Stage();
    Deal_Fogtrap();
    Deal_Mute();
    SDL_RenderPresent(app.rdr);
}