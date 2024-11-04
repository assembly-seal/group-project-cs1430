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

int main() {

    // Data Abstraction:

    int quit = 0;

    // Input:
    
    // Process:

    SDL_Window*   window   = NULL;
	SDL_Renderer* renderer = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf( "init error - SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	//Create window
	window = SDL_CreateWindow("ENGINE",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH, SCREEN_HEIGHT,
	SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
		cout << "window error - SDL_Error: " << SDL_GetError() << endl;
		return 1;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Circle c1 = {(Point){100, 100}, 100, (Color){100, 255, 0}};
    Circle c2 = {(Point){300, 300}, 100, (Color){100, 255, 0}};

    SDL_Event eventData;
    while (!quit) {

        SDL_GetMouseState( &c1.pos.x, &c1.pos.y );

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
