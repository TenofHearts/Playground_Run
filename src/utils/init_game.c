#include "utils/init_game.h"

void Init_Game()
{
    app.character.acceleration_y = -1;
    app.character.mode = CHARACTER_MODE_RUN;
    app.character.speed_y = 0;
    app.character.character.x = -SQR_LEN;
    app.character.lane = 1;
    app.character.character.y = LANE_TWO_Y;
    app.character.character.w = SQR_LEN;
    app.character.character.h = SQR_LEN;
    app.character.invincible = 0;
    app.character.death = 0;
    app.speed = 5;
    app.runway.head = NULL;
    app.runway.tail = NULL;
    SDL_Surface *character_surf = IMG_Load("res/image/character_1.png");
    if (character_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.character.texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
    if (app.character.texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *invincible_icon_surf = IMG_Load("res/image/shield_1.png");
    if (invincible_icon_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.character.invincible_icon_texture = SDL_CreateTextureFromSurface(app.rdr, invincible_icon_surf);
    if (app.character.invincible_icon_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(character_surf);
    SDL_FreeSurface(invincible_icon_surf);
    app.score = 0;
    app.runway.prev_type = OBST_NUM;
}

void Init_Window()
{
    app.win_rect.x = 1750;
    app.win_rect.y = 0;
    app.win_rect.h = WIN_H;
    app.win_rect.w = WIN_W;
    app.score_board.x = 0;
    app.score_board.y = 0;
    app.score_board.w = SCORE_BOARD_W;
    app.score_board.h = SCORE_BOARD_H;
    SDL_Surface *jpg_surf = IMG_Load("res/image/runway_v3.jpg");
    if (jpg_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    } // 导入图片，要释放
    app.background_texture = SDL_CreateTextureFromSurface(app.rdr, jpg_surf);
    if (app.background_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(jpg_surf);
    srand(time(NULL));
}