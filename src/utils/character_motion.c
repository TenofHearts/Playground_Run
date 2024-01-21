#include "utils/character_motion.h"

int lane_y[3] = {LANE_ONE_Y, LANE_TWO_Y, LANE_THREE_Y};

void Character_Motion(void)
{
    SDL_Surface *character_surf = NULL;
    switch (app.character.mode)
    {
    case CHARACTER_MODE_RUN:
        character_surf = IMG_Load("res/image/character_1.png");
        break;
    case CHARACTER_MODE_JUMP:
        character_surf = IMG_Load("res/image/character_2.png");
        break;
    case CHARACTER_MODE_DUCK:
        character_surf = IMG_Load("res/image/character_3.png");
        break;
    }
    if (character_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.character.texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
    if (app.character.texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_RenderCopy(app.rdr, app.character.texture, NULL, &app.character.character);
    SDL_FreeSurface(character_surf);
}

void Character_Move()
{
    switch (app.character.mode)
    {
    case CHARACTER_MODE_JUMP:
        app.character.character.y -= app.character.speed_y;
        app.character.speed_y += app.character.acceleration_y;
        if (app.character.character.y == lane_y[app.character.lane])
        {
            Character_Run();
        }
        break;
    case CHARACTER_MODE_DUCK:
        /* code */
        break;
    default:
        break;
    }
}

void Switch_Lane_L()
{
    if (app.character.lane != 0)
    {
        app.character.character.y -= 115;
        app.character.lane--;
    }
}
void Switch_Lane_R()
{
    if (app.character.lane != 2)
    {
        app.character.character.y += 115;
        app.character.lane += 1;
    }
}

void Character_Duck()
{
    if (app.character.mode != CHARACTER_MODE_DUCK)
    {
        app.character.mode = CHARACTER_MODE_DUCK;
        app.character.character.y = lane_y[app.character.lane];
    }
}
void Character_Jump()
{
    if (app.character.mode != CHARACTER_MODE_JUMP)
    {
        app.character.mode = CHARACTER_MODE_JUMP;
        app.character.speed_y = 30;
    }
}
void Character_Run()
{
    if (app.character.mode != CHARACTER_MODE_RUN)
    {
        app.character.mode = CHARACTER_MODE_RUN;
        app.character.character.y = lane_y[app.character.lane];
    }
}