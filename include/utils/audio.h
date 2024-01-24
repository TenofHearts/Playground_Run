#ifndef INCLUDE_AUDIO_H_
#define INCLUDE_AUDIO_H_

#include "common.h"

void Init_Audio();
void Deinit_Audio();
void Play_BGM();
void Pause_BGM();
void Callback(void *userdata, Uint8 *stream, int len);
void Restart_Audio();

#endif