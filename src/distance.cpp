#include "distance.h"

double getDistance(int xDist, int yDist) {
    return sqrt(xDist * xDist + yDist * yDist);
}

double getDistance(const point& p1, const point& p2) {
    return getDistance(p1.x - p2.x, p1.y - p2.y);
}