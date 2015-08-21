#ifndef HEADER
#define HEADER
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2_image/SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 620;
const int SCREEN_HEIGHT = 876;
const char* STATIC_DIR = "../test/static";

enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gHelloWorld = NULL;

bool init();

bool loadMedia();

SDL_Surface* loadSurface(const char* path);

void close();

const char* getStaticRes(const char* filename);
#endif
