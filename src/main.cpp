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

enum GameStatus {
	TITLE_SCREEN,
	SHOOTING_PHASE,
	BOUNCE_PHASE,
	MANAGE_ENEMIES,
	END_SCREEN
};

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
	int width = 1920;
	int height = 1080;
    SDL_Plotter g(width,height);
    point p1 = {100, 100}, p2 = {200, 200};
    point spawnPoint = {width / 2.0, height / 2.0};
    color c;
    int size = 20;
    GameStatus myStatus = TITLE_SCREEN;
    char lastKey;

    vector<Circle> circles;
    //for (int i = 0; i < 3; i++)
        //for (int j = 0; j < 3; j++) {
        //    point tempPoint = {i * 30 + 300, j * 30 + 300};
        //    circles.push_back((Circle){tempPoint, 10, {0, 0, 255}});
    //    }
    //Circle& c1 = circles[0];

    circles.push_back((Circle){spawnPoint, 30, {0, 255, 255}});
    Circle& c1 = circles[0];
    vector<Collision> collisions {};

    int points = 0;

    // Input:

    // Process:

    SDL_Texture* stupidCat = g.addImage("./images/Gakster.png");

    while (!g.getQuit())
    {
    	g.clear();

        if (myStatus == TITLE_SCREEN) {
        	// Code to display title screen
        	// Press a key (for now "e") to start

        	lastKey = g.getKey();

        	if (lastKey == 'e') {
                myStatus = SHOOTING_PHASE;
        	}

        }
        else if (myStatus == SHOOTING_PHASE) {
        	checkCollisions(collisions, circles, circles);
        	points += collisions.size() * 25;
        	handleCollisions(collisions);

        	for (auto& i : circles) {
                g.setColor(i.c);
        		g.drawCircle(i.p, i.r);
            }

            g.drawImage(stupidCat, 100, 100, 200, 200, 0.0);

        }
        else if (myStatus == BOUNCE_PHASE) {

        }
        else if (myStatus == MANAGE_ENEMIES) {

        }
        else if (myStatus == END_SCREEN) {

        }

        g.update();
        //g.getMouseLocation(c1.p.x, c1.p.y);
    }

    // Output:

    cout << "SCORE: " << points << endl;
    
    // Assumptions:
    
    return 0;
}
