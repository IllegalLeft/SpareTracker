#include <SDL.h>
#include <stdio.h>

#include "video.h"

int initSDL() {
    // init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL faild to initialize: %s\n", SDL_GetError());
        return 1;
    }

    // create window
    Window = SDL_CreateWindow("owotracker", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (Window == NULL) {
        printf("Window failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    Screen = SDL_GetWindowSurface(Window);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

int endSDL() {
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 0;
}

int CheckEvents(SDL_Event Event) {
    if (Event.type == SDL_QUIT)
        return 1;

    if ((Event.type == SDL_KEYDOWN) && (Event.key.repeat == 0)) {
        switch(Event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
        case SDLK_SPACE:
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int Quit = 0;
    SDL_Event Event;
    int TicksLastFrame = 0;

    initSDL();
    printf("Current audio driver: %s\n", SDL_GetCurrentAudioDriver());

    Chars = LoadTexture(FILE_CHARS);

    // setup character rectangles
    int i = 0;
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            CharRect[i].x = x * FONT_WIDTH;
            CharRect[i].y = y * FONT_HEIGHT;
            CharRect[i].w = FONT_WIDTH;
            CharRect[i].h = FONT_HEIGHT;
            i++;
        }
    }
    // blank screen
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            ScreenChars[x][y].character = 0;
            ScreenChars[x][y].fg = 7;
            ScreenChars[x][y].bg = 0;
        }
    }

    ScreenChars[0][0].character = 100;

    // Main loop
    while (Quit == 0) {
        // poll events
        SDL_PollEvent(&Event);
        Quit = CheckEvents(Event);

        // draw screen
        DrawScreen(ScreenChars);

        // limit to 60fps
        while (SDL_GetTicks() < (1000/60 + TicksLastFrame))
            SDL_Delay(1);
        SDL_RenderPresent(Renderer);
        TicksLastFrame = SDL_GetTicks();
    }

    endSDL();
    return 0;
}
