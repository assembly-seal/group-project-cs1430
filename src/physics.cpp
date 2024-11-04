#include "physics.h"

double distance(const point& p1, const point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

vector<CircleCollision> checkCollisions(vector<Circle> group1, vector<Circle> group2) {
    
    vector<CircleCollision> collisions;
    
    for (Circle& i : group1)
        for (Circle& j : group2)
            if (i.size + j.size < distance(i.pos, j.pos))
                collisions.push_back((CircleCollision){i, j});

    return collisions;
}
