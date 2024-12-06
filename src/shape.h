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
    int initialHealth;
    int currentHealth;
};

struct Line {
    point p1, p2;
    /* desc: find the length of a line
    * return: double
    * pre: two valid points
    * post: the length of the line
    */
    double len() {
        return getDistance(p1, p2);
    }
    /* desc: find angle formed by 2 lines
    * return: double
    * pre: 2 valid lines
    * post: angle
    */
    double angle() {
        return atan2(p2.y - p1.y, p2.x - p1.x);
    }
};

#endif // shape_h
