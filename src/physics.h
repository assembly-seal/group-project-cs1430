#ifndef physics_h
#define physics_h

#include <vector>
#include <cmath>
#include "entity.h"
using namespace std;

struct CircleCollision {
    Circle& c1;
    Circle& c2;
};

double distance(const point&, const point&);

vector<CircleCollision> checkCollisions(vector<Circle>, vector<Circle>);
void handleCollisions(vector<CircleCollision>);

#endif // physics_h
