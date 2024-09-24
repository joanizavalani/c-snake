#include "snake.h"

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

int getGridPosition(int windowDimension, int gridDimension) {

    return (windowDimension / 2) - (gridDimension / 2);
}

enum {
    snakeUP,
    snakeDOWN,
    snakeLEFT,
    snakeRIGHT
};

struct snake {
    int x;
    int y;
    int direction;
    struct snake *next;

}; typedef struct snake Snake;

Snake *snakeHead;
Snake *snakeTail;

void initializeSnake() {

    Snake *newSnake = malloc(sizeof(Snake));

    newSnake -> x = rand() % ((GRID_SIZE * 3) / 4);
    newSnake -> y = rand() % ((GRID_SIZE * 3) / 4);
    newSnake -> direction = rand() % 4;
    newSnake -> next = NULL;

    snakeHead = newSnake;
    snakeTail = newSnake;
}

void increaseSnake() {

    Snake *newSnakeCell = malloc(sizeof(Snake));

    newSnakeCell -> x = snakeTail -> x;
    newSnakeCell -> y = snakeTail -> y;
    newSnakeCell -> direction = snakeTail -> direction;

    switch (snakeTail -> direction) {

        case snakeUP:
            newSnakeCell -> y -= 1;
            break;

        case snakeDOWN:
            newSnakeCell -> y += 1;
            break;

        case snakeLEFT:
            newSnakeCell -> x -= 1;
            break;

        case snakeRIGHT:
            newSnakeCell -> x += 1;
            break;
    }

    newSnakeCell -> next = NULL;
    snakeTail -> next = newSnakeCell;
}

void renderSnake(SDL_Renderer *renderer, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);

    int snakeCellSize = GRID_DIMENSIONS / GRID_SIZE;

    SDL_Rect snakeCell;
    snakeCell.w = snakeCellSize;
    snakeCell.h = snakeCellSize;

    Snake *track = snakeHead; // starting from the head of the snake

    // looping through the entire snake (linked list), calculating the (x, y) position
    // of the current cell, until we reach the last segment
    while (track != NULL) {

        snakeCell.x = x + track -> x * snakeCellSize;
        snakeCell.y = y + track -> y * snakeCellSize;

        SDL_RenderFillRect(renderer, &snakeCell);

        track = track -> next; // move to the next cell of the snake
    }
}

// Draws a rectangular grid starting from (x, y), iterating through grid cells
void renderGrid(SDL_Renderer *renderer, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);

    int cellSize = GRID_DIMENSIONS / GRID_SIZE;

    SDL_Rect gridCell;
    gridCell.w = cellSize;
    gridCell.h = cellSize;

    for (int i = 0; i < GRID_SIZE; i++) {

        for (int j = 0; j < GRID_SIZE; j++) {

            gridCell.x = x + (i * cellSize);
            gridCell.y = y + (j * cellSize);

            //  for each cell, the x and y coordinate are calculated as the
            //  start position (x, y) plus the width of all previous cells
            //  in the row.

            SDL_RenderDrawRect(renderer, &gridCell);
        }
    }
}

int main(int argc, char *argv[]) {

    initializeSnake();
    increaseSnake();

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

    int gridPosition_x = getGridPosition(WINDOW_WIDTH, GRID_DIMENSIONS);
    int gridPosition_y = getGridPosition(WINDOW_HEIGHT, GRID_DIMENSIONS);

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

        renderGrid(renderer, gridPosition_x, gridPosition_y);
        renderSnake(renderer, gridPosition_x, gridPosition_y);

        SDL_SetRenderDrawColor(renderer, 0xdb, 0x7c, 0x4d, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}