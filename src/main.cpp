/*
 * Author: Caden Sullivan, Jace Prince,
 *         Elijah Robledo, Ava Callais
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: ??/??/??
 * Date Created: 11/1/24
 * Date Last Modified: 11/1/24
 */

#include <iostream>
#include "SDL_Plotter.h"
#include "circle.h"
#include "collision.h"

void drawCircle(point loc, int size, color c, SDL_Plotter& g){
	for(double i = -size; i <= size;i+=0.1){
		for(double j = -size; j <= size; j+=0.1){
			if(i*i + j*j <= size*size){
				g.plotPixel(round(loc.x+i),round(loc.y+j),c);
			}
		}
	}
}

int main() {

    // Data Abstraction:

    SDL_Plotter g(1000,1000);
    point p1 = {100, 100}, p2 = {200, 200};
    color c;
    int size = 20;

    vector<Circle> circles;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            point tempPoint = {i * 30 + 300, j * 30 + 300};
            circles.push_back((Circle){tempPoint, 10, {0, 0, 255}});
        }
    Circle& c1 = circles[0];
    c1.c = {255, 0, 0};
    vector<Collision> collisions {};

    int points = 0;

    // Input:

    // Process:

    while (!g.getQuit())
    {
        g.clear();

        g.getMouseLocation(c1.p.x, c1.p.y);

        checkCollisions(collisions, circles, circles);
        points += collisions.size() * 25;
        handleCollisions(collisions);

		for (auto& i : circles)
            drawCircle(i.p, i.r, i.c, g);
		g.update();
    }

    // Output:

    cout << "SCORE: " << points << endl;
    
    // Assumptions:
    
    return 0;
}
