#include "header.hpp"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initializel SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_RESIZABLE);
        if (gWindow == NULL) {
            printf("Window counld not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

SDL_Surface* loadSurface(const char* path) {
    SDL_Surface* optimizedSurface = NULL;
    //SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_Error: %s\n", path, IMG_GetError());
    } else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia() {
    bool success = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface(getStaticRes("MyPic.png"));
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface(getStaticRes("01.png"));
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load default!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface(getStaticRes("02.png"));
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load default!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface(getStaticRes("MyPic.png"));
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load default!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface(getStaticRes("MyPic.png"));
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load default!\n");
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface* scaledSurface(int x, int y, int w, int h) {
    SDL_Surface* gStretchedSurface = NULL;
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = w;
    stretchRect.h = h;
    SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

    return gStretchedSurface;
}

const char* getStaticRes(const char* filename) {
    char* static_dir = (char *)malloc((strlen(STATIC_DIR) + strlen(filename) + 1) * sizeof(char));
    strcpy(static_dir, STATIC_DIR);
    return strcat(strcat(static_dir, "/"), filename);
}
