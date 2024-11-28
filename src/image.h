#ifndef image_h
#define image_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Image {
    SDL_Texture* texture;
    SDL_Rect rect;
    double angle;
};

#endif // image_h