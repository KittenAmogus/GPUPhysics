#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include <SDL2/SDL.h>

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL: Init failed: %s\r\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window =
      SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "SDL: Window creating failed: %s\r\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  int running = 1;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = 0;
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        running = 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
