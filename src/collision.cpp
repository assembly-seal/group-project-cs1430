#include "collision.h"

double getDistance(int xDist, int yDist) {
    return sqrt(xDist * xDist + yDist * yDist);
}

double getDistance(const point& p1, const point& p2) {
    return getDistance(p1.x - p2.x, p1.y - p2.y);
}

bool areColliding(const Circle& c1, const Circle& c2) {
    return 1;
}

void checkCollisions(vector<Collision>& collisions, vector<Circle>& group1, vector<Circle>& group2) {
    for (Circle& i : group1)
        for (Circle& j : group2) {
            if (&i != &j) {
                int xDist = j.p.x - i.p.x;
                int yDist = j.p.y - i.p.y;
                double distance = getDistance(xDist, yDist);
                double overlap  = i.r + j.r - distance;
                if (overlap >= 0)
                    collisions.push_back((Collision){i, j, xDist, yDist, distance, overlap});
            }
        }
}

void handleCollisions(vector<Collision>& collisions) {
    while (collisions.size()) {
        Circle& c1      = collisions.back().c1;
        Circle& c2      = collisions.back().c2;
        int xDist       = collisions.back().xDist;
        int yDist       = collisions.back().yDist;
        double distance = collisions.back().distance;
        double overlap  = collisions.back().overlap;

        double xRatio = xDist / distance;
        double yRatio = yDist / distance;

        c1.p.x -= overlap * xRatio / 2;
        c1.p.y -= overlap * yRatio / 2;
        c2.p.x += overlap * xRatio / 2;
        c2.p.y += overlap * yRatio / 2;

        collisions.pop_back();
    }
}