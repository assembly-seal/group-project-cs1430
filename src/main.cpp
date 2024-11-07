/*
 * Author: Caden Sullivan, Jace Prince,
 *         Elijah Robledo, Ava Callais
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: ??/??/??
 * Date Created: 11/1/24
 * Date Last Modified: 11/1/24
 */

#include <iostream>
#include <SDL2/SDL.h>
#include "entity.h"
#include "color.h"
#include "physics.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

void setRectangle(SDL_Rect& rect, int x, int y, int w, int h) {
    rect = {x, y, w, h};
};

int main() {

    // Data Abstraction:

    Renderer renderer;
    int quit = 0;

    // Input:

    // Process:

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "init error - SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    Circle c1 = {(Point){100, 100}, 100, (Color){100, 255, 0}};
    Circle c2 = {(Point){300, 300}, 100, (Color){100, 255, 0}};

    SDL_Event eventData;
    while (!quit) {

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&c1.pos.x, &c1.pos.y);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawCircle(renderer, c1.pos.x, c1.pos.y);

        SDL_RenderPresent(renderer);

        for (auto& i : balls) {
            for (auto& j : monsters) {
                if (colliding(i, j)) {
                    
                }
            }
        }

        //Update the surface
        SDL_UpdateWindowSurface(window);

        while (SDL_PollEvent(&eventData)) {
            switch (eventData.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow( window );
	SDL_Quit();
    // Output:
    
    // Assumptions:
    
    return 0;
}
