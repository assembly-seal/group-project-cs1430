#ifndef shape_h
#define shape_h

#include "SDL_Plotter.h"
#include "distance.h"
#include "force.h"

struct Circle {
    point p;
    int r;
    Image* image;
    force f;
    int health;

    // Circle& operator=(Circle&& other) {
    //     p = other.p;
    //     r = other.r;
    //     image = &other.i;
    // }
};

struct Line {
    point p1, p2;
    double len() {
        return getDistance(p1, p2);
    }
    double angle() {
        return atan2(p2.y - p1.y, p2.x - p1.x);
    }
};

#endif // shape_h
