#ifndef collision_h
#define collision_h

#include <vector>
#include <cmath>
#include "SDL_Plotter.h"
#include "circle.h"
using namespace std;

struct Collision {
    Circle& c1;
    Circle& c2;
    int xDist;
    int yDist;
    double distance;
    double overlap;
};

double getDistance(int, int);
double getDistance(const point&, const point&);
bool areColliding(const Circle&, const Circle&);
void checkCollisions(vector<Collision>&, vector<Circle>&, vector<Circle>&);
void handleCollisions(vector<Collision>&);

#endif // collision_h