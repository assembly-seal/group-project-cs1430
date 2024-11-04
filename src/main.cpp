/*
 * Author: Caden Sullivan, Jace_Prince1,
 *         Elijah_Robledo, Ava_Callais1
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: ??/??/??
 * Date Created: 11/1/24
 * Date Last Modified: 11/1/24
 */

#include <iostream>
#include <SDL2/SDL.h>
#include "entity.h"
#include "physics.h"

void drawCircle(Circle entity, SDL_Plotter& g) {
    point loc = entity.pos;
    int size = entity.size;
    color c = entity.c;

	for(double i = -size; i <= size; i += 0.1){
		for(double j = -size; j <= size; j += 0.1){
			if(i*i + j*j <= size*size){
				g.plotPixel(round(loc.x + i),round(loc.y + j),c);
			}
		}
	}
}

int main() {

    // Data Abstraction:

    

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

    Circle c1 = {(point){100, 100}, 100, (color){100, 255, 0}};
    Circle c2 = {(point){300, 300}, 100, (color){100, 255, 0}};

    while (!quit) {

        SDL_GetMouseState( &c1.pos.x, &c1.pos.y );

        //drawCircle(c1, g);
        //drawCircle(c2, g);

		if(g.kbhit()){
			switch(toupper(g.getKey())){
				case 'C': g.clear();
				          break;
			}
		}

		if(g.mouseClick()){
			p = g.getMouseClick();
			size = rand()%50;
			c.R  = rand()%256;
			c.G  = rand()%256;
			c.B  = rand()%256;
		}
    }

    SDL_DestroyWindow( window );
	SDL_Quit();
    // Output:
    
    // Assumptions:
    
    return 0;
}
