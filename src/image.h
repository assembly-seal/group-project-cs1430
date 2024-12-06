/*
 * Author: Caden Sullivan
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: 12/08/2024
 * Date Created: 11/01/24
 * Date Last Modified: 12/06/2024
 */

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
