#include "utils/audio.h"

static Uint32 audio_pos = 0;
Uint8 *audio_buf;
Uint32 audio_len;
SDL_AudioDeviceID device_id;
SDL_AudioSpec audio_spec;

Mix_Chunk *coin_soundeffect = NULL;
Mix_Chunk *jump_soundeffect = NULL;

void Init_Audio()
{
    if (SDL_LoadWAV("res/audio/bgm_1.wav", &audio_spec, &audio_buf, &audio_len) == NULL)
    {
        HANDLE_ERROR("SDL_LoadWAV");
    }
    audio_spec.callback = Callback;
    device_id = SDL_OpenAudioDevice(NULL, 0, &audio_spec, NULL, 0);
    if (device_id <= 0)
    {
        HANDLE_ERROR("SDL_OpenAudioDevice");
    }
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    coin_soundeffect = Mix_LoadWAV("res/audio/soundeffect_1.mp3");
    jump_soundeffect = Mix_LoadWAV("res/audio/soundeffect_2.mp3");
}

void Deinit_Audio()
{
    SDL_FreeWAV(audio_buf);
    SDL_CloseAudioDevice(device_id);
}

void Play_BGM()
{
    SDL_PauseAudioDevice(device_id, 0);
}
void Pause_BGM()
{
    SDL_PauseAudioDevice(device_id, 1);
}

void Play_Coin_Soundeffect()
{
    Mix_PlayChannel(-1, coin_soundeffect, 0);
}
void Play_Jump_Soundeffect()
{
    Mix_PlayChannel(-1, jump_soundeffect, 0);
}

void Callback(void *userdata, Uint8 *stream, int len)
{
    int remain = audio_len - audio_pos;
    if (remain > len)
    {
        memcpy(stream, audio_buf + audio_pos, len);
        audio_pos += len;
    }
    else
    {
        memcpy(stream, audio_buf + audio_pos, remain);
        audio_pos = 0;
    }
}

void Restart_Audio()
{
    audio_pos = 0;
}