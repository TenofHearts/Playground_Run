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
    app.character.fog = 0;
    app.character.magnet = 0;
    app.speed = 5;
    app.runway.head = NULL;
    app.runway.tail = NULL;
    app.score = 0;
    app.runway.prev_type = OBST_NUM;
}

void Init_Window()
{
    app.baby_mode = 0;
    app.win_rect.x = 1750;
    app.win_rect.y = 0;
    app.win_rect.h = WIN_H;
    app.win_rect.w = WIN_W;
    app.score_board.x = 100;
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
    Init_Audio();
    app.obstacle_texture = (SDL_Texture **)malloc(OBST_NUM * sizeof(SDL_Texture *));
    Init_Texture();
    srand(time(NULL));
}

void Destroy_Texture()
{
    if (app.background_texture)
    {
        SDL_DestroyTexture(app.background_texture);
    }
    if (app.character.texture)
    {
        SDL_DestroyTexture(app.character.texture);
    }
    if (app.character.fog_texture)
    {
        SDL_DestroyTexture(app.character.fog_texture);
    }
    for (int i = 0; i < OBST_NUM; i++)
    {
        if (app.obstacle_texture[i])
        {
            SDL_DestroyTexture(app.obstacle_texture[i]);
        }
    }
}
void Init_Texture()
{
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
    SDL_Surface *fog_surf = IMG_Load("res/image/fog_1.png");
    if (fog_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.character.fog_texture = SDL_CreateTextureFromSurface(app.rdr, fog_surf);
    if (app.character.fog_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *jump_surf = IMG_Load("res/image/obstacle_1.png");
    if (jump_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_JUMP] = SDL_CreateTextureFromSurface(app.rdr, jump_surf);
    if (app.obstacle_texture[OBST_JUMP] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *duck_surf = IMG_Load("res/image/obstacle_2.png");
    if (duck_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_DUCK] = SDL_CreateTextureFromSurface(app.rdr, duck_surf);
    if (app.obstacle_texture[OBST_DUCK] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *wall_surf = IMG_Load("res/image/obstacle_3.png");
    if (wall_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_WALL] = SDL_CreateTextureFromSurface(app.rdr, wall_surf);
    if (app.obstacle_texture[OBST_WALL] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *coin_surf = IMG_Load("res/image/coin_1.png");
    if (coin_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_COIN] = SDL_CreateTextureFromSurface(app.rdr, coin_surf);
    if (app.obstacle_texture[OBST_COIN] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *shield_surf = IMG_Load("res/image/shield_1.png");
    if (shield_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_SHIELD] = SDL_CreateTextureFromSurface(app.rdr, shield_surf);
    if (app.obstacle_texture[OBST_SHIELD] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *fogtrap_surf = IMG_Load("res/image/fogtrap_1.png");
    if (fogtrap_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_FOG] = SDL_CreateTextureFromSurface(app.rdr, fogtrap_surf);
    if (app.obstacle_texture[OBST_FOG] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *football_surf = IMG_Load("res/image/football_1.png");
    if (football_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_FOOTBALL] = SDL_CreateTextureFromSurface(app.rdr, football_surf);
    if (app.obstacle_texture[OBST_FOOTBALL] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Surface *magnet_surf = IMG_Load("res/image/magnet_1.png");
    if (magnet_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.obstacle_texture[OBST_MAGNET] = SDL_CreateTextureFromSurface(app.rdr, magnet_surf);
    if (app.obstacle_texture[OBST_MAGNET] == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(magnet_surf);
    SDL_FreeSurface(football_surf);
    SDL_FreeSurface(fogtrap_surf);
    SDL_FreeSurface(shield_surf);
    SDL_FreeSurface(coin_surf);
    SDL_FreeSurface(wall_surf);
    SDL_FreeSurface(duck_surf);
    SDL_FreeSurface(jump_surf);
    SDL_FreeSurface(fog_surf);
    SDL_FreeSurface(character_surf);
}