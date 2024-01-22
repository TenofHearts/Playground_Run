#include "obstacle.h"

extern int lane_y[3];

void Create_Obstacle(int lane, int type)
{
    obstacle_node *p_ob = (obstacle_node *)malloc(sizeof(obstacle_node));
    p_ob->next = NULL;
    p_ob->obst.obstacle.x = WIN_W;
    p_ob->obst.obstacle.w = SQR_LEN;
    p_ob->obst.obstacle.h = SQR_LEN;
    p_ob->obst.obstacle.y = lane_y[lane];
    p_ob->obst.hitbox.x = p_ob->obst.obstacle.x + 30;
    p_ob->obst.hitbox.w = HITBOX_LEN;
    p_ob->obst.hitbox.h = HITBOX_LEN;
    p_ob->obst.type = type;
    p_ob->obst.lane = lane;
    SDL_Surface *obst_surf = NULL;
    switch (type)
    {
    case OBST_JUMP:
        obst_surf = IMG_Load("res/image/obstacle_1.png");
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_DUCK:
        obst_surf = IMG_Load("res/image/obstacle_2.png");
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y;
        break;
    case OBST_WALL:
        obst_surf = IMG_Load("res/image/obstacle_3.png");
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y;
        break;
    case OBST_COIN:
        obst_surf = IMG_Load("res/image/coin_1.png");
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_SHIELD:
        obst_surf = IMG_Load("res/image/shield_1.png");
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    default:
        break;
    }
    if (obst_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    p_ob->obst.texture = SDL_CreateTextureFromSurface(app.rdr, obst_surf);
    if (app.runway.head == NULL)
    {
        app.runway.head = p_ob;
        app.runway.tail = p_ob;
    }
    else
    {
        app.runway.tail->next = p_ob;
        app.runway.tail = p_ob;
    }
    SDL_FreeSurface(obst_surf);
    // SDL_Log("Create_Obstacle Success!\n");
}

void Obstacle_Motion()
{
    while (app.runway.head && app.runway.head->obst.obstacle.x <= -SQR_LEN)
    {
        obstacle_node *temp = app.runway.head;
        app.runway.head = app.runway.head->next;
        Delete_Obstacle(temp);
    }
    obstacle_node *p_ob = app.runway.head, *prev = NULL;
    while (p_ob)
    {
        p_ob->obst.obstacle.x -= app.speed;
        p_ob->obst.hitbox.x = p_ob->obst.obstacle.x;
        if (app.character.lane == p_ob->obst.lane && Collition_Detect(p_ob->obst.hitbox))
        {
            Collition_Event(p_ob->obst.type);
            if (prev)
            {
                prev->next = p_ob->next;
            }
            else
            {
                app.runway.head = app.runway.head->next;
                if (app.runway.head == NULL)
                {
                    app.runway.tail = NULL;
                }
            }
            obstacle_node *temp = p_ob;
            p_ob = p_ob->next;
            Delete_Obstacle(temp);
        }
        else
        {
            SDL_RenderCopy(app.rdr, p_ob->obst.texture, NULL, &p_ob->obst.obstacle);
            prev = p_ob;
            p_ob = p_ob->next;
        }
    }
}

int Collition_Detect(SDL_Rect hitbox)
{
    if (SDL_HasIntersection(&hitbox, &app.character.character))
    {
        return 1;
    }
    return 0;
}

void Collition_Event(int type)
{

    switch (type)
    {
    case OBST_JUMP:
        if (app.character.mode != CHARACTER_MODE_JUMP && app.character.invincible == 0)
        {
            app.character.death = 1;
        }
        break;
    case OBST_DUCK:
        if (app.character.mode != CHARACTER_MODE_DUCK && app.character.invincible == 0)
        {
            app.character.death = 1;
        }
        break;
    case OBST_WALL:
        if (app.character.invincible == 0)
        {
            app.character.death = 1;
        }
        break;
    case OBST_COIN:
        app.score += 20;
        break;
    case OBST_SHIELD:
        app.score += 5;
        app.time.invincible_time = SDL_GetTicks64();
        app.character.invincible = 1;
        break;
    default:
        break;
    }
}

void Delete_Obstacle(obstacle_node *obstacle)
{
    SDL_Log("Delete_Obstacle success, type = %d\n", obstacle->obst.type);
    if (obstacle->next == NULL)
    {
        app.runway.tail = NULL;
    }
    else
    {
        obstacle->next = NULL;
    }
    SDL_DestroyTexture(obstacle->obst.texture);
    free(obstacle);
}
void Delete_Runway()
{
    obstacle_node *p_ob = app.runway.head;
    while (p_ob)
    {
        obstacle_node *temp = p_ob;
        p_ob = p_ob->next;
        Delete_Obstacle(temp);
    }
}

void Deal_Invincible()
{
    if (app.character.invincible)
    {
        if (SDL_GetTicks64() - app.time.invincible_time >= INVINCIBLE_TIME)
        {
            app.character.invincible = 0;
        }
        else
        {
            SDL_Rect img = {0, 410, 40, 40};
            SDL_RenderCopy(app.rdr, app.character.invincible_icon_texture, NULL, &img);
        }
    }
}

void Obstacle_Generate()
{ /**/
    int generate_coefficient = 0, lane_coefficient, type_coefficient;
    generate_coefficient = rand() % 4;
    if (generate_coefficient <= 2)
    {
        lane_coefficient = rand() % 3;
        type_coefficient = rand() % OBST_NUM;
        if (type_coefficient == OBST_SHIELD)
        {
            type_coefficient = rand() % OBST_NUM;
            if (type_coefficient == OBST_SHIELD)
            {
                Create_Obstacle(lane_coefficient, OBST_SHIELD);
            }
        }
        else
        {
            Create_Obstacle(lane_coefficient, type_coefficient);
        }
    }
    // Create_Obstacle(1, OBST_SHIELD);
}