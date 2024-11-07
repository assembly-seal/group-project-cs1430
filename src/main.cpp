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

void drawCircle(SDL_Renderer* renderer, int x_pos, int y_pos) {
    double r = 20;
    double t1 = r / 16;
    int x = x_pos;
    int y = 0;

    while (x > y) {
        SDL_Rect rect;

        setRectangle(rect, -x + x_pos, y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(renderer, &rect);
        setRectangle(rect, -y + x_pos, x + y_pos - 1, y * 2, 1);
        SDL_RenderDrawRect(renderer, &rect);
        setRectangle(rect, -x + x_pos, -y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(renderer, &rect);
        setRectangle(rect, -y + x_pos, -x + y_pos + 1, y * 2, 1);
        SDL_RenderDrawRect(renderer, &rect);
  
        y++;
        t1 += y;
        double t2 = t1 - x;
        if (t2 >= 0) {
            t1 = t2;
            x--;
        }
    }
}

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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&c1.pos.x, &c1.pos.y);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawCircle(renderer, c1.pos.x, c1.pos.y);

        SDL_RenderPresent(renderer);

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
