#include "utils/print_text.h"

void Print_Text(SDL_Rect dest_rect, SDL_Color fg, char *content, int size)
{
    TTF_Font *font = TTF_OpenFont("res/fonts/BRLNSDB.TTF", size);
    if (font == NULL)
    {
        HANDLE_ERROR("TTF_OpenFont");
    }
    SDL_Surface *txt_surf = TTF_RenderText_Solid(font, content, fg);
    if (txt_surf == NULL)
    {
        HANDLE_ERROR("TTF_RenderText_solid");
    }
    SDL_Texture *txt_texture = SDL_CreateTextureFromSurface(app.rdr, txt_surf);
    if (txt_texture == NULL)
    {
        HANDLE_ERROR("SDL_CreateTextureFromSurface");
    }
    SDL_RenderCopy(app.rdr, txt_texture, NULL, &dest_rect);
    SDL_RenderPresent(app.rdr);
    SDL_DestroyTexture(txt_texture);
    SDL_FreeSurface(txt_surf);
    TTF_CloseFont(font);
}