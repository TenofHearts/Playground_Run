#include "utils/character_motion.h"

int lane_y[3] = {LANE_ONE_Y, LANE_TWO_Y, LANE_THREE_Y};

void Character_Motion(void)
{
    for (int i = 0; i < app.player; i++)
    {
        Character_Move(&app.character[i]);
        SDL_Surface *character_surf = NULL;
        char file[40] = {0};
        switch (app.character[i].mode)
        {
        case CHARACTER_MODE_RUN:
            sprintf(file, "res/image/character_%d.png", i + 1);
            break;
        case CHARACTER_MODE_JUMP:
            sprintf(file, "res/image/jump_%d.png", i + 1);
            break;
        case CHARACTER_MODE_DUCK:
            sprintf(file, "res/image/duck_%d.png", i + 1);
            break;
        }
        character_surf = IMG_Load(file);
        if (character_surf == NULL)
        {
            HANDLE_ERROR("IMG_Load");
        }
        SDL_DestroyTexture(app.character[i].texture);
        app.character[i].texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
        if (app.character[i].texture == NULL)
        {
            HANDLE_ERROR("SDL_CreateTextureFromSurface");
        }
        SDL_RenderCopy(app.rdr, app.character[i].texture, NULL, &app.character[i].character);
        SDL_FreeSurface(character_surf);
    }
}

void Character_Move(character *character_temp)
{
    switch (character_temp->mode)
    {
    case CHARACTER_MODE_JUMP:
        character_temp->character.y -= (character_temp->speed_y / 2.5);
        character_temp->speed_y += character_temp->acceleration_y;
        if (character_temp->character.y >= lane_y[character_temp->lane])
        {
            Character_Run(character_temp);
        }
        break;
    case CHARACTER_MODE_DUCK:
        if (SDL_GetTicks64() - character_temp->time_character.duck_time >= 700)
        {
            Character_Run(character_temp);
        }
        break;
    default:
        break;
    }
}

void Switch_Lane_L(character *character_temp)
{
    if (character_temp->lane != 0)
    {
        character_temp->character.y -= 115;
        character_temp->lane--;
    }
}
void Switch_Lane_R(character *character_temp)
{
    if (character_temp->lane != 2)
    {
        character_temp->character.y += 115;
        character_temp->lane += 1;
    }
}

void Character_Duck(character *character_temp)
{
    character_temp->mode = CHARACTER_MODE_DUCK;
    character_temp->character.y = lane_y[character_temp->lane];
    character_temp->time_character.duck_time = SDL_GetTicks64();
}
void Character_Jump(character *character_temp)
{
    if (character_temp->mode != CHARACTER_MODE_JUMP)
    {
        Play_Jump_Soundeffect();
        character_temp->mode = CHARACTER_MODE_JUMP;
        character_temp->speed_y = 20;
    }
}
void Character_Run(character *character_temp)
{
    if (character_temp->mode != CHARACTER_MODE_RUN)
    {
        character_temp->mode = CHARACTER_MODE_RUN;
        character_temp->character.y = lane_y[character_temp->lane];
    }
}