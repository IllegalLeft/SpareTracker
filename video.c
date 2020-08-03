#include <SDL.h>
#include <stdio.h>

#include "video.h"

SDL_Texture* LoadTexture(char* Filename) {
    SDL_Texture* NewTexture = NULL;

    SDL_Surface* LoadedSurface = SDL_LoadBMP(Filename);
    if (LoadedSurface == NULL)
        printf("Unable to load image %s! %s\n", Filename, SDL_GetError());
    else {
        NewTexture = SDL_CreateTextureFromSurface(Renderer, LoadedSurface);
        if (NewTexture == NULL)
            printf("Unable to create texture from %s! %s\n", Filename, SDL_GetError());
    }
    SDL_FreeSurface(LoadedSurface);

    return NewTexture;
}

int BlitChar(SDL_Texture* Texture, SDL_Rect TileRect, int x, int y, int Flip) {
    SDL_Rect DestRect;
    DestRect.x = x;
    DestRect.y = y;
    DestRect.w = FONT_WIDTH;
    DestRect.h = FONT_HEIGHT;

    SDL_RenderCopyEx(Renderer, Texture, &TileRect, &DestRect, 0, 0, Flip);

    return 0;
}
// ScreenChars[i][j].character
int DrawScreen(struct ScreenChar* ScreenChars) {
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            BlitChar(Chars, CharRect[176], i*FONT_WIDTH, j*FONT_HEIGHT, 0);
        }
    }
    return 0;
}
