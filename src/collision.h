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
};

bool areColliding(Circle& i, point& j);
bool areColliding(Circle& i, Circle& j);
void checkCollisions(vector<Collision>&, vector<Circle>&, vector<Circle>&);
void checkCollisions(vector<LineCollision>&, vector<Circle>&, vector<Line>&);
void handleCollisions(vector<Collision>&);
void handleCollisions(vector<LineCollision>&);

#endif // collision_h