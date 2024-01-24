#include "utils/audio.h"

static Uint32 audio_pos = 0;

void Init_Audio()
{
    if (SDL_LoadWAV("res/audio/bgm_1.wav", &app.audio.audio_spec, &app.audio.audio_buf, &app.audio.audio_len) == NULL)
    {
        HANDLE_ERROR("SDL_LoadWAV");
    }
    app.audio.audio_spec.callback = Callback;
    app.audio.device_id = SDL_OpenAudioDevice(NULL, 0, &app.audio.audio_spec, NULL, 0);
    if (app.audio.device_id <= 0)
    {
        HANDLE_ERROR("SDL_OpenAudioDevice");
    }
}

void Deinit_Audio()
{
    SDL_FreeWAV(app.audio.audio_buf);
    SDL_CloseAudioDevice(app.audio.device_id);
}

void Play_BGM()
{
    SDL_PauseAudioDevice(app.audio.device_id, 0);
}
void Pause_BGM()
{
    SDL_PauseAudioDevice(app.audio.device_id, 1);
}

void Callback(void *userdata, Uint8 *stream, int len)
{
    int remain = app.audio.audio_len - audio_pos;
    if (remain > len)
    {
        memcpy(stream, app.audio.audio_buf + audio_pos, len);
        audio_pos += len;
    }
    else
    {
        memcpy(stream, app.audio.audio_buf + audio_pos, remain);
        audio_pos = 0;
    }
}

void Restart_Audio()
{
    audio_pos = 0;
}