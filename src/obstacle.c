#include "obstacle.h"

extern int lane_y[3];

SDL_Rect fog_rect = {WIN_W, 0, WIN_H, WIN_H};

void Create_Obstacle(int lane, int type)
{
    obstacle_node *p_ob = (obstacle_node *)malloc(sizeof(obstacle_node));
    app.runway.prev_type = type;
    p_ob->next = NULL;
    p_ob->obst.obstacle.x = WIN_W;
    p_ob->obst.obstacle.w = SQR_LEN;
    p_ob->obst.obstacle.h = SQR_LEN;
    p_ob->obst.obstacle.y = lane_y[lane];
    p_ob->obst.hitbox.x = p_ob->obst.obstacle.x + 40;
    p_ob->obst.hitbox.w = HITBOX_LEN;
    p_ob->obst.hitbox.h = HITBOX_LEN;
    p_ob->obst.type = type;
    p_ob->obst.lane = lane;
    p_ob->obst.texture = app.obstacle_texture[type];
    switch (type)
    {
    case OBST_JUMP:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_DUCK:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y;
        break;
    case OBST_WALL:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y;
        p_ob->obst.hitbox.h = SQR_LEN;
        break;
    case OBST_COIN:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_SHIELD:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_FOG:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y;
        p_ob->obst.hitbox.h = SQR_LEN;
        break;
    default:
        break;
    }
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
            if (app.character.death == 0)
            {
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
    SDL_Rect hitbox_character[3] = {{0, 0, 65, 100}, {0, 0, 65, 100}, {25, 75, 25, 25}};
    hitbox_character[app.character.mode].x += app.character.character.x;
    hitbox_character[app.character.mode].y += app.character.character.y;
    if (SDL_HasIntersection(&hitbox, &hitbox_character[app.character.mode]))
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
        Play_Coin_Soundeffect();
        app.score += 20;
        break;
    case OBST_SHIELD:
        app.score += 5;
        app.time.invincible_time = SDL_GetTicks64();
        app.character.invincible = 1;
        break;
    case OBST_FOG:
        app.score -= 10;
        app.character.fog = 1;
        app.time.fog_time = SDL_GetTicks64();
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
void Deal_Fogtrap()
{
    if (app.character.fog)
    {
        Uint32 temp = SDL_GetTicks64() - app.time.fog_time;
        if (temp >= FOG_TIME)
        {
            app.character.fog = 0;
            fog_rect.x = WIN_W;
        }
        else if (temp >= 6500)
        {
            fog_rect.x = FOG_X + (temp - 6500) * (WIN_W - FOG_X) / 500;
            SDL_RenderCopy(app.rdr, app.character.fog_texture, NULL, &fog_rect);
        }
        else if (temp >= 500)
        {
            fog_rect.x = FOG_X;
            SDL_RenderCopy(app.rdr, app.character.fog_texture, NULL, &fog_rect);
        }
        else if (fog_rect.x <= FOG_X)
        {
            fog_rect.x = FOG_X;
            SDL_RenderCopy(app.rdr, app.character.fog_texture, NULL, &fog_rect);
        }
        else
        {
            fog_rect.x = FOG_X + (500 - temp) * (WIN_W - FOG_X) / 500;
            SDL_RenderCopy(app.rdr, app.character.fog_texture, NULL, &fog_rect);
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
        type_coefficient = rand() % (OBST_NUM - 1);
        if (type_coefficient == app.runway.prev_type)
        {
            type_coefficient = (type_coefficient + 2) % OBST_NUM;
            Create_Obstacle(lane_coefficient, type_coefficient);
        }
        else if (type_coefficient == OBST_SHIELD)
        {
            type_coefficient = rand() % 10;
            if (type_coefficient >= 8)
            {
                Create_Obstacle(lane_coefficient, OBST_SHIELD);
            }
            else if (type_coefficient <= 1)
            {
                Create_Obstacle(lane_coefficient, OBST_FOG);
            }
            else
            {
                Create_Obstacle(lane_coefficient, OBST_COIN);
            }
        }
        else
        {
            Create_Obstacle(lane_coefficient, type_coefficient);
        }
    }
}