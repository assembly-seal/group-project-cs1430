/*
 * Author: Caden Sullivan
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: 12/08/2024
 * Date Created: 11/01/24
 * Date Last Modified: 12/06/2024
 */

#ifndef collision_h
#define collision_h

#include <vector>
#include <cmath>
#include <algorithm>
#include "SDL_Plotter.h"
#include "distance.h"
#include "shape.h"
using namespace std;

struct Collision {
    Circle& c1;
    Circle& c2;
    int xDist;
    int yDist;
    double distance;
    double overlap;
};

struct LineCollision {
    Circle& c;
    point p;
    double lineAngle;
    int pid;
};

struct prevCollision {
    int id1;
    int id2;
    bool over = false;
};

struct prevLineCollision {
    int id1;
    int id2;
    bool over = false;
};

/* desc: check if circle and point collide
 * return: bool
 * pre: valid circle and point
 * post: whether they are colliding
 */
bool areColliding(Circle& i, point& j);
/* desc: check if 2 circles are colliding
 * return: bool
 * pre: 2 valid circles
 * post: whether they are colliding
 */
bool areColliding(Circle& i, Circle& j);
/* desc: find collisions between vectors of circles
 * return: bool
 * pre: valid vectors
 * post: vector full of collisions
 */
void checkCollisions(vector<Collision>&, vector<Circle>&, vector<Circle>&);
/* desc: find collisions between vectors of circles and lines
 * return: bool
 * pre: valid vectors
 * post: vector full of collisions
 */
void checkCollisions(vector<LineCollision>&, vector<Circle>&, vector<Line>&);
/* desc: handle collisions in vector
 * return: void
 * pre: valid vector
 * post: objects moved accordingly
 */
void handleCollisions(vector<Collision>&);
/* desc: handle collisions in vector
 * return: void
 * pre: valid vector
 * post: objects moved accordingly
 */
void handleCollisions(vector<LineCollision>&);

#endif // collision_h
