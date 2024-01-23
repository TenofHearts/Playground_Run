#include "start_menu.h"

static SDL_Point pt = {0, 0};

void Transition_Animation_1()
{
    SDL_Surface *jpg_surf = IMG_Load("res/image/runway_v3.jpg");
    if (jpg_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    }
    while (app.win_rect.y + WIN_H + 51 <= jpg_surf->h)
    {
        SDL_RenderClear(app.rdr);
        SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
        SDL_RenderPresent(app.rdr);
        app.win_rect.y++;
        SDL_Delay(5);
    }
    SDL_FreeSurface(jpg_surf);
}

void Start()
{
    SDL_RenderCopy(app.rdr, app.background_texture, &app.win_rect, NULL);
    SDL_Surface *png_surf = IMG_Load("res/image/rules_v2.png");
    if (png_surf == NULL)
    {
        HANDLE_ERROR("IMG_Load");
    } // 导入图片，要释放
    SDL_Texture *png_texture = SDL_CreateTextureFromSurface(app.rdr, png_surf);
    if (png_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_Rect rules_rect = {215, 50, 400, 175};
    SDL_RenderCopy(app.rdr, png_texture, NULL, &rules_rect);
    SDL_FreeSurface(png_surf);
    SDL_DestroyTexture(png_texture);
    SDL_Rect start_button = {365, 275, 100, 50};
    SDL_Rect exit_button = {365, 325, 100, 50};
    SDL_Color fg_b = {0, 0, 0, 255}, fg_lg = {100, 100, 100, 255};
    Print_Text(start_button, fg_b, "Start", 50);
    Print_Text(exit_button, fg_b, "Exit", 50);
    SDL_RenderPresent(app.rdr);
    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
            case SDL_MOUSEBUTTONDOWN:
                SDL_Log("Down(%d, %d),button = %d, clicks = %d\n", event.button.x, event.button.y, event.button.button, event.button.clicks);
                pt.x = event.button.x;
                pt.y = event.button.y;
                if (SDL_PointInRect(&pt, &start_button))
                {
                    SDL_Color fg_g = {200, 200, 200, 255};
                    Print_Text(start_button, fg_g, "Start", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else if (SDL_PointInRect(&pt, &exit_button))
                {
                    SDL_Color fg_g = {200, 200, 200, 255};
                    Print_Text(exit_button, fg_g, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                SDL_Log("Up(%d, %d),button = %d, clicks = %d\n", event.button.x, event.button.y, event.button.button, event.button.clicks);
                if (SDL_PointInRect(&pt, &start_button))
                {
                    Print_Text(start_button, fg_b, "Start", 50);
                    Transition_Animation_1();
                    return;
                }
                else if (SDL_PointInRect(&pt, &exit_button))
                {
                    Print_Text(exit_button, fg_b, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                    exit(0);
                }
                break;
            case SDL_MOUSEMOTION:
                // SDL_Log("(%d, %d)\n", event.motion.x, event.motion.y);
                SDL_Point pt_m = {event.motion.x, event.motion.y};
                if (SDL_PointInRect(&pt_m, &start_button))
                {
                    Print_Text(start_button, fg_lg, "Start", 50);
                    Print_Text(exit_button, fg_b, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else if (SDL_PointInRect(&pt_m, &exit_button))
                {
                    Print_Text(exit_button, fg_lg, "Exit", 50);
                    Print_Text(start_button, fg_b, "Start", 50);
                    SDL_RenderPresent(app.rdr);
                }
                else
                {
                    Print_Text(start_button, fg_b, "Start", 50);
                    Print_Text(exit_button, fg_b, "Exit", 50);
                    SDL_RenderPresent(app.rdr);
                }
                break;
            default:
                break;
            }
        }
    }
}