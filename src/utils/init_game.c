#include "utils/init_game.h"
#include "utils/character_motion.h"

void Init_Game()
{
    for (int i = 0; i < 2; i++)
    {
        app.character[i].acceleration_y = -1;
        app.character[i].mode = CHARACTER_MODE_RUN;
        app.character[i].speed_y = 0;
        app.character[i].character.x = -SQR_LEN;
        app.character[i].lane = 1;
        app.character[i].character.y = LANE_TWO_Y;
        app.character[i].character.w = SQR_LEN;
        app.character[i].character.h = SQR_LEN;
        app.character[i].invincible = 0;
        app.character[i].death = 0;
        app.character[i].magnet = 0;
        app.character[i].score = 0;
    }
    Character_Motion();
    app.fog = 0;
    app.speed = 5;
    app.runway.head = NULL;
    app.runway.tail = NULL;
    app.runway.prev_type = OBST_NUM;
}

void Init_Window()
{
    app.mute = 0;
    app.player = 0;
    app.baby_mode = 1;
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
    app.character = (character *)malloc(2 * sizeof(character));
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
    for (int i = 0; i < 2; i++)
    {
        if (app.character[i].texture)
        {
            SDL_DestroyTexture(app.character[i].texture);
        }
    }
    if (app.fog_texture)
    {
        SDL_DestroyTexture(app.fog_texture);
    }
    for (int i = 0; i < OBST_NUM; i++)
    {
        if (app.obstacle_texture[i])
        {
            SDL_DestroyTexture(app.obstacle_texture[i]);
        }
    }
    if (app.nothing)
    {
        SDL_DestroyTexture(app.nothing);
    }
}
void Init_Texture()
{
    for (int i = 0; i < 2; i++)
    {
        char temp[30] = {0};
        sprintf(temp, "res/image/character_%d.png", i + 1);
        SDL_Surface *character_surf = IMG_Load(temp);
        if (character_surf == NULL)
        {
            HANDLE_ERROR("IMG_Load");
        }
        app.character[i].texture = SDL_CreateTextureFromSurface(app.rdr, character_surf);
        if (app.character[i].texture == NULL)
        {
            HANDLE_ERROR("SDL_CreateTextureFromSurface");
        }
        SDL_FreeSurface(character_surf);
    }
    SDL_Surface *fog_surf = IMG_Load("res/image/fog_1.png");
    if (fog_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.fog_texture = SDL_CreateTextureFromSurface(app.rdr, fog_surf);
    if (app.fog_texture == NULL)
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
    SDL_Surface *nothing_surf = IMG_Load("res/image/nothing_1.png");
    if (nothing_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    app.nothing = SDL_CreateTextureFromSurface(app.rdr, nothing_surf);
    if (app.nothing == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(nothing_surf);
    SDL_FreeSurface(magnet_surf);
    SDL_FreeSurface(football_surf);
    SDL_FreeSurface(fogtrap_surf);
    SDL_FreeSurface(shield_surf);
    SDL_FreeSurface(coin_surf);
    SDL_FreeSurface(wall_surf);
    SDL_FreeSurface(duck_surf);
    SDL_FreeSurface(jump_surf);
    SDL_FreeSurface(fog_surf);
}