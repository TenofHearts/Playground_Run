#include "game.h"

static int score = 0;

void Transition_Animation_2()
{
    SDL_Surface *character_surf = IMG_Load("res/image/character_1.png");
    if (character_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    SDL_Texture *character_texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
    if (character_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *background_surf = IMG_Load("res/image/runway_v3.jpg");
    if (background_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(app.rdr, background_surf);
    if (background_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    for (; app.character.character.x < CHARACTER_START; app.character.character.x++)
    {
        SDL_RenderClear(app.rdr);
        SDL_RenderCopy(app.rdr, background_texture, &app.win_rect, NULL);
        SDL_RenderCopy(app.rdr, character_texture, NULL, &app.character.character);
        SDL_RenderPresent(app.rdr);
        SDL_Delay(3);
    }
    SDL_Color fg_w = {255, 255, 255, 255};
    SDL_Rect numbers_rect[3] = {{285, 175, 100, 100}, {385, 175, 100, 100}, {485, 175, 100, 100}};
    Print_Text(numbers_rect[0], fg_w, "3..", 50);
    SDL_Delay(500);
    Print_Text(numbers_rect[1], fg_w, "2..", 50);
    SDL_Delay(500);
    Print_Text(numbers_rect[2], fg_w, "1..", 50);
    SDL_Delay(500);
    SDL_RenderClear(app.rdr);
    SDL_RenderCopy(app.rdr, background_texture, &app.win_rect, NULL);
    SDL_RenderCopy(app.rdr, character_texture, NULL, &app.character.character);
    SDL_Rect text_rect = {315, 175, 200, 100};
    Print_Text(text_rect, fg_w, "GO!!!!", 60);
    SDL_RenderPresent(app.rdr);
    SDL_Delay(1000);
    SDL_RenderClear(app.rdr);
    SDL_RenderCopy(app.rdr, background_texture, &app.win_rect, NULL);
    SDL_RenderCopy(app.rdr, character_texture, NULL, &app.character.character);
    SDL_RenderPresent(app.rdr);
    SDL_FreeSurface(character_surf);
    SDL_FreeSurface(background_surf);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(background_texture);
}
void Background_Motion()
{
    app.win_rect.x = (app.win_rect.x + app.speed) % 2000;
    SDL_Surface *background_surf = IMG_Load("res/image/runway_v3.jpg");
    if (background_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(app.rdr, background_surf);
    if (background_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_RenderCopy(app.rdr, background_texture, &app.win_rect, NULL);
    Character_Motion();
    Score_Update(score);
    SDL_RenderPresent(app.rdr);
    SDL_FreeSurface(background_surf);
    SDL_DestroyTexture(background_texture);
}

void Game()
{
    Transition_Animation_2();
    Score_Update(score);
    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
            default:
                break;
            }
        }
        Background_Motion();
        // score++; // For testing purposes only
    }
}