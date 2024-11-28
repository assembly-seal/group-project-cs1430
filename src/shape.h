#ifndef shape_h
#define shape_h

#include "SDL_Plotter.h"
#include "distance.h"

struct Circle {
    point p;
    int r;
    color c;
};

struct Line {
    point p1, p2;
    double len() {
        return getDistance(p1, p2);
    }
};

#endif // shape_h