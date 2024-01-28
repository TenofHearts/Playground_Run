#include "stop_menu.h"

void Transition_Animation_3()
{
    for (int i = 0; i <= 30; i++)
    {
        SDL_SetRenderDrawColor(app.rdr, 255, 255, 255, i);
        SDL_SetRenderDrawBlendMode(app.rdr, SDL_BLENDMODE_BLEND);
        SDL_Rect window_area = {0, 0, WIN_W, WIN_H};
        SDL_RenderFillRect(app.rdr, &window_area);
        SDL_RenderPresent(app.rdr);
        SDL_Delay(12);
    }
}

void Stop_Menu()
{
    Pause_BGM();
    Play_Coin_Soundeffect();
    Transition_Animation_3();
    SDL_Rect pause = {315, 50, 200, 80}, continue_button = {315, 200, 200, 50}, exit_button = {365, 275, 100, 50};
    SDL_Color fg_b = {0, 0, 0, 255}, fg_lg = {100, 100, 100, 255}, fg_g = {200, 200, 200, 255};
    Print_Text(pause, fg_b, "Pause", 72);
    Print_Text(continue_button, fg_b, "Continue", 50);
    Print_Text(exit_button, fg_b, "Exit", 50);
    SDL_RenderPresent(app.rdr);
    SDL_Event event;
    SDL_Point pt = {0, 0};
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
            case SDL_MOUSEMOTION:
                SDL_Point pt_m;
                pt_m.x = event.motion.x;
                pt_m.y = event.motion.y;
                if (SDL_PointInRect(&pt_m, &continue_button))
                {
                    Print_Text(continue_button, fg_lg, "Continue", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_lg, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else
                {
                    Print_Text(continue_button, fg_b, "Continue", 50);
                    Print_Text(exit_button, fg_b, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                pt.x = event.button.x;
                pt.y = event.button.y;
                if (SDL_PointInRect(&pt, &continue_button))
                {
                    Print_Text(continue_button, fg_g, "Continue", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_g, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_PointInRect(&pt, &continue_button))
                {
                    Print_Text(continue_button, fg_b, "Continue", 50);
                    SDL_RenderPresent(app.rdr);
                    Play_Coin_Soundeffect();
                    Play_BGM();
                    return;
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_b, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                    exit(0);
                }
                break;
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
            default:
                break;
            }
        }
    }
}