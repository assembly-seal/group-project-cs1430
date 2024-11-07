#ifndef renderer_h
#define renderer_h

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

class Renderer {
    SDL_Window*   window;
	SDL_Renderer* renderer;
    SDL_Rect rect;

public:

    void drawCircle(int x_pos, int y_pos, int radius);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clear();
    void draw();
    void shutdown();
    void setRectangle(SDL_Rect& rect, int x, int y, int w, int h);


    Renderer() {
        //Create window
        window = SDL_CreateWindow("ENGINE",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (window == NULL)
            cout << "window error - SDL_Error: " << SDL_GetError() << endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
};

#endif // renderer_h