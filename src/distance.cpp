/*
 * Author: Caden Sullivan
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: 12/08/2024
 * Date Created: 11/01/24
 * Date Last Modified: 12/06/2024
 */

#include "distance.h"

double getDistance(int xDist, int yDist) {
    return sqrt(xDist * xDist + yDist * yDist);
}

double getDistance(const point& p1, const point& p2) {
    return getDistance(p1.x - p2.x, p1.y - p2.y);
}
