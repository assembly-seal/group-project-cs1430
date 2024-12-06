#ifndef distance_h
#define distance_h

#include <cmath>
#include "SDL_Plotter.h"


/* desc: find distance between x and y
 * return: void
 * pre: xdist and ydist
 * post: distance between
 */
double getDistance(int, int);

/* desc: find dist between 2 points
 * return: void
 * pre: valid points
 * post: distance between
 */
double getDistance(const point&, const point&);

#endif // distance_h