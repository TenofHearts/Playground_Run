#include "game.h"
#include "utils/character_motion.h"

void Delay(int ms)
{
    ms /= 10;
    SDL_Event event;
    for (int i = 0; i < ms; i++)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case ESC:
                    exit(0);
                    break;
                case B:
                    app.baby_mode = (app.baby_mode + 1) % 2;
                    break;
                case M:
                    app.mute = (app.mute + 1) % 2;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                exit(0);
            default:
                break;
            }
        }
        SDL_Delay(10);
    }
}
void Transition_Animation_2()
{
    SDL_RenderClear(app.rdr);
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
    for (int i = 0; i < app.player; i++)
    {
        for (; app.character[i].character.x < CHARACTER_START + i * DISTANCE; app.character[i].character.x++)
        {
            SDL_RenderClear(app.rdr);
            SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
            SDL_RenderCopy(app.rdr, app.character[0].texture, NULL, &app.character[0].character);
            SDL_RenderCopy(app.rdr, app.character[1].texture, NULL, &app.character[1].character);
            SDL_RenderPresent(app.rdr);
            SDL_Delay(3);
        }
    }
    SDL_Color fg_w = {255, 255, 255, 255};
    SDL_Rect numbers_rect[3] = {{285, 175, 100, 100}, {385, 175, 100, 100}, {485, 175, 100, 100}};
    Print_Text(numbers_rect[0], fg_w, "3..", 50);
    SDL_RenderPresent(app.rdr);
    Delay(500);
    Print_Text(numbers_rect[1], fg_w, "2..", 50);
    SDL_RenderPresent(app.rdr);
    Delay(500);
    Print_Text(numbers_rect[2], fg_w, "1..", 50);
    SDL_RenderPresent(app.rdr);
    Delay(500);
    SDL_RenderClear(app.rdr);
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
    for (int i = 0; i < app.player; i++)
    {
        SDL_RenderCopy(app.rdr, app.character[i].texture, NULL, &app.character[i].character);
    }
    SDL_Rect text_rect = {305, 175, 220, 100};
    Print_Text(text_rect, fg_w, "GO!!!!", 60);
    SDL_RenderPresent(app.rdr);
    Delay(1000);
    SDL_RenderClear(app.rdr);
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
    for (int i = 0; i < app.player; i++)
    {
        SDL_RenderCopy(app.rdr, app.character[i].texture, NULL, &app.character[i].character);
    }
    SDL_RenderPresent(app.rdr);
}

void Game()
{
    Init_Game();
    Transition_Animation_2();
    Restart_Audio();
    Play_BGM();
    SDL_Event event;
    int steps = 0;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
            case SDL_KEYDOWN:
                // SDL_Log("down: sym = %d, scancode = %d\n", event.key.keysym.sym, event.key.keysym.scancode);
                switch (event.key.keysym.scancode)
                {
                case ESC:
                    exit(0);
                    break;
                case SPACE:
                    Stop_Menu();
                    break;
                case R:
                    Death_Menu();
                    return;
                case A:
                    Switch_Lane_L(&app.character[0]);
                    break;
                case LEFT:
                    Switch_Lane_L(&app.character[1 % app.player]);
                    break;
                case D:
                    Switch_Lane_R(&app.character[0]);
                    break;
                case RIGHT:
                    Switch_Lane_R(&app.character[1 % app.player]);
                    break;
                case W:
                    Character_Jump(&app.character[0]);
                    break;
                case UP:
                    Character_Jump(&app.character[1 % app.player]);
                    break;
                case S:
                    Character_Duck(&app.character[0]);
                    break;
                case DOWN:
                    Character_Duck(&app.character[1 % app.player]);
                    break;
                case B:
                    app.baby_mode = (app.baby_mode + 1) % 2;
                    Score_Handle(1);
                    break;
                case M:
                    app.mute = (app.mute + 1) % 2;
                    break;
                /*For testing purposes only*/
                case T:
                    Character_Run(&app.character[0]);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        Motion();
        steps += app.speed;
        if (steps >= SQR_LEN)
        {
            Obstacle_Generate();
            for (int i = 0; i < app.player; i++)
            {
                app.character[i].score++;
            }
            steps = 0;
        }
        if (app.character[0].death || app.character[1].death)
        {
            Death_Menu();
            return;
        }
        Frame_Control();
        app.time.frame_time = SDL_GetTicks64();
        // app.score++; // For testing purposes only
    }
}