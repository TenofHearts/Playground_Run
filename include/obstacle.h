#ifndef INCLUDE_OBSTACLE_H_
#define INCLUDE_OBSTACLE_H_

#include "common.h"
#include "death_menu.h"

void Create_Obstacle(int lane, int type);
void Delete_Obstacle(obstacle_node *obstacle);
void Obstacle_Motion(void);
int Collition_Detect(SDL_Rect hitbox);
void Collition_Event(int type);
void Delete_Runway(void);
void Deal_Invincible(void);
void Obstacle_Generate(void);
void Deal_Fogtrap(void);

#endif