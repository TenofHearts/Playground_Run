#include "utils/motion.h"

void Background_Motion()
{
    app.win_rect.x = (app.win_rect.x + app.speed) % 2000;
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
}

void Motion()
{
    Background_Motion();
    Obstacle_Motion();
    Character_Motion();
    Score_Update();
    Display_Frame();
    Deal_Invincible();
    Deal_Fogtrap();
    SDL_RenderPresent(app.rdr);
}