#include "header.cpp"

int main(int argc, char** args) {

  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      bool quit = false;
      SDL_Event e;
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
      while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
              case SDLK_UP:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                break;
              case SDLK_DOWN:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                break;
              case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                break;
              case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                break;
              default:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
          }
          SDL_Rect stretchRect;
          stretchRect.x = (SCREEN_WIDTH - gCurrentSurface->w) / 2;
          stretchRect.y = (SCREEN_HEIGHT - gCurrentSurface->h) / 2;
          stretchRect.w = gCurrentSurface->w;
          stretchRect.h = gCurrentSurface->h;
          //double ratio = gCurrentSurface->w / (double) gCurrentSurface->h;
          //stretchRect.x = 0;
          //stretchRect.y = 0;
          //double window_ratio = SCREEN_WIDTH / (double) SCREEN_HEIGHT;
          //if (ratio > window_ratio) {
          //    stretchRect.w = SCREEN_WIDTH;
          //    stretchRect.h = SCREEN_WIDTH / ratio;
          //} else {
          //    stretchRect.h = SCREEN_HEIGHT;
          //    stretchRect.w = SCREEN_HEIGHT * ratio;
          //}
          SDL_FillRect(gScreenSurface, NULL, 0x000);
          SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
          SDL_UpdateWindowSurface(gWindow);
        }
      }
    }
  }
  close();

  return 0;
}

