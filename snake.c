#include "snake.h"
#include <SDL.h>

/*  ################      So the snake lies on a grid-- like the one of the left--
    #  □□□         #      and it grows by consuming randomly generated fruit,
    #    □         #      which takes up a cell of the grid. The snake by
    #    □□□□□@ *  #      itself is a segment of connected pixels, growing with each
    #              #      fruit consumed by 1 grid. Perhaps a linked list could
    ################      help manage that, as it offers dynamic addition & more. */

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 700

#define GRID_SIZE 18
#define GRID_DIMENSIONS 400

void renderGrid(SDL_Renderer *renderer, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);

    int cellSize = GRID_DIMENSIONS / GRID_SIZE;

    SDL_Rect cell;
    cell.w = cellSize;
    cell.h = cellSize;

    for (int i = 0; i < GRID_SIZE; i++) {

        for (int j = 0; j < GRID_SIZE; j++) {

            cell.x = x + (i * cellSize);
            cell.y = y + (j * cellSize);

            //  for each cell, the x and y coordinate are calculated as the
            //  start position (x, y) plus the width of all previous cells
            //  in the row.

            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO < 0)) {

        fprintf(stderr, "Error: SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // window creation: centered the frame, width and height definitions above
    SDL_Window *window = SDL_CreateWindow(
            "C-Snake",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
            );

    if (!window) {

        fprintf(stderr, "Error: SDL_Window failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {

        fprintf(stderr, "Error: SDL_Renderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIMENSIONS / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIMENSIONS / 2);

    // below, the while loop continuously runs, checking for key presses using SDL_PollEvent.
    // it handles real-time user input and window events. If the user presses the esc key or
    // closes the window, the quit variable is set to true which exits the loop and stops the program.

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYUP:
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {

                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
            }
        }

        // the rendering process keeps happening whilst the program is running
        SDL_RenderClear(renderer);

        renderGrid(renderer, grid_x, grid_y);

        SDL_SetRenderDrawColor(renderer, 0xdb, 0x7c, 0x4d, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}