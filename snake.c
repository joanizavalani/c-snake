#include "snake.h"
#include <SDL.h>

/*  ################      So the snake lies on a grid-- like the one of the left--
    #  □□□         #      and it grows by consuming randomly generated fruit,
    #    □         #      which takes up a pixel of the grid. The snake by
    #    □□□□□@ *  #      itself is a segment of connected pixels, growing with each
    #              #      fruit consumed by 1 grid. Perhaps a linked list could
    ################      help manage that, as it offers us dynamic addition & more. */

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 650

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO < 0)) {

        fprintf(stderr, "Error: SDL_INIT_VIDEO");
    }

    SDL_Window *window = SDL_CreateWindow(
            "C-Snake",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
            );

    if (!window) {

        fprintf(stderr, "Error: couldn't find window");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {

        fprintf(stderr, "Error: couldn't find renderer");
    }

    SDL_SetRenderDrawColor(renderer, 0xdb, 0x7c, 0x4d, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}