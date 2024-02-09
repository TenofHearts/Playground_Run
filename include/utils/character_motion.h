#ifndef INCLUDE_CHARACTER_MOTION_H_
#define INCLUDE_CHARACTER_MOTION_H_

#include "common.h"

void Character_Motion(void);
void Character_Move(character *character_temp);
void Switch_Lane_L(character *character_temp);
void Switch_Lane_R(character *character_temp);
void Character_Duck(character *character_temp);
void Character_Jump(character *character_temp);
void Character_Run(character *character_temp);

#endif