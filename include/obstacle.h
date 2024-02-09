#ifndef INCLUDE_OBSTACLE_H_
#define INCLUDE_OBSTACLE_H_

#include "common.h"
#include "death_menu.h"

void Create_Obstacle(int lane, int type);
void Delete_Obstacle(obstacle_node *obstacle);
void Obstacle_Motion(void);
void Collide(character *character_temp, obstacle_node *obstacle_p);
int Collition_Detect(SDL_Rect hitbox, character *character_temp);
void Collition_Event(int *type, character *character_temp);
void Delete_Runway(void);
void Deal_Stage(void);
void Obstacle_Generate(void);
void Deal_Fogtrap(void);
void Football_Collition(obstacle_node *football);

#endif