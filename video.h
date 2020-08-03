#ifndef VIDEO_H
#define VIDEO_H

#define FONT_HEIGHT     12
#define FONT_WIDTH      8

#define SCREEN_WIDTH    80
#define SCREEN_HEIGHT   25

#define WINDOW_WIDTH    SCREEN_WIDTH*FONT_WIDTH
#define WINDOW_HEIGHT   SCREEN_HEIGHT*FONT_HEIGHT

#define FILE_CHARS      "cp437.bmp"

SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Surface* Screen;
SDL_Texture* Chars;
SDL_Rect CharRect[256];

struct ScreenChar {
    char character;
    int fg;
    int bg;
} ScreenChars[SCREEN_WIDTH][SCREEN_HEIGHT];

SDL_Texture* LoadTexture(char* Filename);
int BlitChar(SDL_Texture* Texture, SDL_Rect TileRect, int x, int y, int Flip);
int DrawScreen(struct ScreenChar* ScreenChars);

#endif
