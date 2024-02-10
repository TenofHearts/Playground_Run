#include "obstacle.h"

extern int lane_y[3];

SDL_Rect fog_rect = {WIN_W, 0, WIN_H, WIN_H};

int magnet_x = MAGNET_X;

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
    case OBST_FOOTBALL:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
        break;
    case OBST_MAGNET:
        p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
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
        // SDL_Log("Create Obstacle success! type = %d\n", p_ob->obst.type);
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
        if (app.runway.head == NULL)
        {
            app.runway.tail = NULL;
        }
        Delete_Obstacle(temp);
    }
    obstacle_node *p_ob = app.runway.head, *prev = NULL;
    while (p_ob)
    {
        if (p_ob->obst.type == MOVING_FOOTBALL)
        {
            p_ob->obst.obstacle.x += 10;
            p_ob->obst.hitbox.x = p_ob->obst.obstacle.x;
            Football_Collition(p_ob);
            if (p_ob->obst.obstacle.x >= WIN_W)
            {
                if (prev)
                {
                    prev->next = p_ob->next;
                }
                else
                {
                    app.runway.head = p_ob->next;
                }
                obstacle_node *temp = p_ob;
                p_ob = p_ob->next;
                if (p_ob == NULL)
                {
                    app.runway.tail = prev;
                }
                Delete_Obstacle(temp);
                continue;
            }
        }
        else
        {
            p_ob->obst.obstacle.x -= app.speed;
            if (app.character[0].magnet == 1 && p_ob->obst.type == OBST_COIN && p_ob->obst.obstacle.x <= magnet_x && p_ob->obst.obstacle.x >= -SQR_LEN)
            {
                p_ob->obst.obstacle.y += (app.character[0].character.y - p_ob->obst.obstacle.y) / 3;
                p_ob->obst.obstacle.x += (app.character[0].character.x - p_ob->obst.obstacle.x) / 3;
                p_ob->obst.hitbox.y = p_ob->obst.obstacle.y + 75;
                p_ob->obst.lane = app.character[0].lane;
                if (SDL_GetTicks64() - app.character[0].time_character.magnet_time >= MAGNET_TIME)
                {
                    magnet_x -= app.speed;
                    if (magnet_x <= 0)
                    {
                        app.character[0].magnet = 0;
                    }
                }
            }
            p_ob->obst.hitbox.x = p_ob->obst.obstacle.x;
            for (int i = 0; i < app.player; i++)
            {
                Collide(&app.character[i], p_ob);
            }
        }
        SDL_RenderCopy(app.rdr, p_ob->obst.texture, NULL, &p_ob->obst.obstacle);
        prev = p_ob;
        p_ob = p_ob->next;
    }
}

void Collide(character *character_temp, obstacle_node *obstacle_p)
{
    if ((*character_temp).lane == obstacle_p->obst.lane && Collition_Detect(obstacle_p->obst.hitbox, character_temp))
    {
        Collition_Event(&obstacle_p->obst.type, character_temp);
        if ((*character_temp).death == 0 && obstacle_p->obst.type != MOVING_FOOTBALL)
        {
            obstacle_p->obst.type = NOTHING;
            obstacle_p->obst.texture = app.nothing;
            obstacle_p->obst.lane = NOTHING;
        }
    }
}

int Collition_Detect(SDL_Rect hitbox, character *character_temp)
{
    SDL_Rect hitbox_character[3] = {{0, 0, 65, 100}, {0, 0, 65, 100}, {25, 75, 25, 25}};
    hitbox_character[character_temp->mode].x += character_temp->character.x - (character_temp - app.character) * 30;
    hitbox_character[character_temp->mode].y += character_temp->character.y;
    if (SDL_HasIntersection(&hitbox, &hitbox_character[character_temp->mode]))
    {
        return 1;
    }
    return 0;
}

void Collition_Event(int *type, character *character_temp)
{
    SDL_Log("Collide with %d\n", *type);
    switch (*type)
    {
    case OBST_JUMP:
        if ((*character_temp).mode != CHARACTER_MODE_JUMP && (*character_temp).invincible == 0)
        {
            (*character_temp).death = 1;
        }
        else if ((*character_temp).invincible > 0)
        {
            (*character_temp).invincible--;
            if (app.baby_mode == 0)
            {
                character_temp->time_character.invincible_time = SDL_GetTicks64();
            }
        }
        break;
    case OBST_DUCK:
        if ((*character_temp).mode != CHARACTER_MODE_DUCK && (*character_temp).invincible == 0)
        {
            (*character_temp).death = 1;
        }
        else if ((*character_temp).invincible > 0)
        {
            (*character_temp).invincible--;
            if (app.baby_mode == 0)
            {
                character_temp->time_character.invincible_time = SDL_GetTicks64();
            }
        }
        break;
    case OBST_WALL:
        if ((*character_temp).invincible == 0)
        {
            (*character_temp).death = 1;
        }
        else if ((*character_temp).invincible > 0)
        {
            (*character_temp).invincible--;
            if (app.baby_mode == 0)
            {
                character_temp->time_character.invincible_time = SDL_GetTicks64();
            }
        }
        break;
    case OBST_COIN:
        Play_Coin_Soundeffect();
        (*character_temp).score += 20 * app.player;
        break;
    case OBST_SHIELD:
        (*character_temp).score += 5 * app.player;
        if (app.baby_mode == 0 && (*character_temp).invincible == 0)
        {
            (*character_temp).time_character.invincible_time = SDL_GetTicks64();
        }
        (*character_temp).invincible++;
        break;
    case OBST_FOG:
        character_temp->score -= 10;
        app.fog = 1;
        app.time.fog_time = SDL_GetTicks64();
        break;
    case OBST_FOOTBALL:
        *type = MOVING_FOOTBALL;
        break;
    case OBST_MAGNET:
        (*character_temp).magnet = 1;
        magnet_x = MAGNET_X;
        character_temp->time_character.magnet_time = SDL_GetTicks64();
        break;
    default:
        break;
    }
}

void Delete_Obstacle(obstacle_node *obstacle)
{
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

void Deal_Stage()
{
    for (int i = 0; i < app.player; i++)
    {
        if (app.character[i].invincible)
        {
            SDL_Rect img = {0, 410, 40, 40};
            img.x = i * 40;
            SDL_Color fg_w = {255, 255, 255, 255};
            SDL_RenderCopy(app.rdr, app.obstacle_texture[OBST_SHIELD], NULL, &img);
            char invincible[4] = {0};
            sprintf(invincible, "%d", app.character[i].invincible);
            img.x += 10;
            img.y = 420;
            img.h = 20;
            img.w = 10 * strlen(invincible);
            Print_Text(img, fg_w, invincible, 20);
            if (app.baby_mode == 0 && SDL_GetTicks64() - app.character[i].time_character.invincible_time >= INVINCIBLE_TIME)
            {
                app.character[i].invincible--;
                app.character[i].time_character.invincible_time = SDL_GetTicks64();
            }
        }
        if (app.character[i].magnet)
        {
            SDL_Rect img = {40, 410, 40, 40};
            SDL_RenderCopy(app.rdr, app.obstacle_texture[OBST_MAGNET], NULL, &img);
        }
    }
}
void Deal_Fogtrap()
{
    if (app.fog)
    {
        Uint32 temp = SDL_GetTicks64() - app.time.fog_time;
        if (temp >= FOG_TIME)
        {
            app.fog = 0;
            fog_rect.x = WIN_W;
        }
        else if (temp >= 6500)
        {
            fog_rect.x = FOG_X + (temp - 6500) * (WIN_W - FOG_X) / 500;
            SDL_RenderCopy(app.rdr, app.fog_texture, NULL, &fog_rect);
        }
        else if (temp >= 500)
        {
            fog_rect.x = FOG_X;
            SDL_RenderCopy(app.rdr, app.fog_texture, NULL, &fog_rect);
        }
        else if (fog_rect.x <= FOG_X)
        {
            fog_rect.x = FOG_X;
            SDL_RenderCopy(app.rdr, app.fog_texture, NULL, &fog_rect);
        }
        else
        {
            fog_rect.x = FOG_X + (500 - temp) * (WIN_W - FOG_X) / 500;
            SDL_RenderCopy(app.rdr, app.fog_texture, NULL, &fog_rect);
        }
    }
    else
    {
        fog_rect.x = WIN_W;
    }
}

void Obstacle_Generate()
{
    int generate_coefficient = 0, lane_coefficient, type_coefficient;
    generate_coefficient = rand() % 4;
    if (generate_coefficient <= 2)
    {
        lane_coefficient = rand() % 3;
        type_coefficient = rand() % 5;
        if (type_coefficient == app.runway.prev_type)
        {
            type_coefficient = (type_coefficient + 2) % 5;
        }
        if (type_coefficient == OBST_SHIELD)
        {
            type_coefficient = rand() % 10;
            if (type_coefficient == 9)
            {
                Create_Obstacle(lane_coefficient, OBST_SHIELD);
            }
            else if (type_coefficient == 0)
            {
                Create_Obstacle(lane_coefficient, OBST_FOG);
            }
            else if (type_coefficient == 3)
            {
                Create_Obstacle(lane_coefficient, OBST_FOOTBALL);
            }
            else if (type_coefficient == 6)
            {
                if (app.player == 1)
                {
                    Create_Obstacle(lane_coefficient, OBST_MAGNET);
                }
                else
                {
                    Create_Obstacle(lane_coefficient, OBST_COIN);
                }
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

void Football_Collition(obstacle_node *football)
{
    obstacle_node *p_ob = football->next;
    while (p_ob)
    {
        if (p_ob->obst.type <= OBST_WALL && SDL_HasIntersection(&p_ob->obst.obstacle, &football->obst.obstacle))
        {
            p_ob->obst.type = NOTHING;
            p_ob->obst.lane = NOTHING;
            p_ob->obst.texture = app.nothing;
        }
        p_ob = p_ob->next;
    }
}