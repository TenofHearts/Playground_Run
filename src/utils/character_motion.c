#include "utils/character_motion.h"

void Character_Motion(void)
{
    SDL_Surface *character_surf = NULL;
    switch (app.character.mode)
    {
    case CHARACTER_MODE_RUN:
        character_surf = IMG_Load("res/image/character_1.png");
        break;
    case CHARACTER_MODE_JUMP:
        character_surf = IMG_Load("res/image/character_1.png");
        break;
    case CHARACTER_MODE_DUCK:
        character_surf = IMG_Load("res/image/character_1.png");
        break;
    }
    if (character_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    SDL_Texture *character_texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
    if (character_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_RenderCopy(app.rdr, character_texture, NULL, &app.character.character);
    SDL_FreeSurface(character_surf);
    SDL_DestroyTexture(character_texture);
}