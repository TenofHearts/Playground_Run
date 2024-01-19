#include "death_menu.h"

void Transition_Animation_4(int score)
{
    for (int i = 0; i <= 100; i++)
    {
        SDL_SetRenderDrawColor(app.rdr, 0, 0, 0, i);
        SDL_SetRenderDrawBlendMode(app.rdr, SDL_BLENDMODE_BLEND);
        SDL_Rect window_area = {0, 0, WIN_W, WIN_H};
        SDL_RenderFillRect(app.rdr, &window_area);
        Score_Update(score);
        SDL_RenderPresent(app.rdr);
        SDL_Delay(3);
    }
}

void Death_Menu(int score)
{
    Transition_Animation_4(score);
    SDL_Rect text = {265, 50, 300, 80}, restart_button = {365, 200, 100, 50}, exit_button = {365, 275, 100, 50};
    SDL_Color fg_w = {255, 255, 255, 255}, fg_g = {100, 100, 100, 255}, fg_lg = {200, 200, 200, 255};
    Print_Text(text, fg_w, "You Failed", 72);
    Print_Text(restart_button, fg_w, "Restart", 50);
    Print_Text(exit_button, fg_w, "Exit", 50);
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
                if (SDL_PointInRect(&pt_m, &restart_button))
                {
                    Print_Text(restart_button, fg_lg, "Restart", 50);
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_lg, "Exit", 50);
                }
                else
                {
                    Print_Text(restart_button, fg_w, "Restart", 50);
                    Print_Text(exit_button, fg_w, "Exit", 50);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                pt.x = event.button.x;
                pt.y = event.button.y;
                if (SDL_PointInRect(&pt, &restart_button))
                {
                    Print_Text(restart_button, fg_g, "Restart", 50);
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_g, "Exit", 50);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_PointInRect(&pt, &restart_button))
                {
                    Print_Text(restart_button, fg_w, "Restart", 50);
                    SDL_RenderClear(app.rdr);
                    SDL_RenderPresent(app.rdr);
                    return;
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_w, "Exit", 50);
                    exit(0);
                }
                break;
            default:
                break;
            }
        }
    }
}