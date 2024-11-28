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
	const int WIDTH = 1080 / 2;
	const int HEIGHT = 1920 / 2;
    SDL_Plotter g(HEIGHT, WIDTH);
    point p1 = {100, 100}, p2 = {200, 200};
    point spawnPoint = {WIDTH / 2.0, HEIGHT / 2.0};
    color c;
    int size = 20;
    GameStatus myStatus = TITLE_SCREEN;
    char lastKey;

    vector<Circle> circles;
    vector<Line> lines;

    circles.push_back({spawnPoint, 30, {0, 255, 255}});
    Circle& c1 = circles[0];
    vector<Collision> collisions {};

    lines.push_back({{100, 100}, {400, 400}});

    int points = 0;

    Image titleScreen = {g.addImage("./images/titlescreen_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image background = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image stupidCat = {g.addImage("./images/Gakster.png"), {100, 100, 200, 200}, 0.0};

    // Input:

    // Process:

    while (!g.getQuit())
    {
    	g.clear();

        if (myStatus == TITLE_SCREEN) {
        	// Code to display title screen
            
            g.drawImage(titleScreen);
        	
            // Press a key (for now "e") to start

        	lastKey = g.getKey();

        	if (lastKey == 'e') {
                myStatus = SHOOTING_PHASE;
        	}

        }
        else if (myStatus == SHOOTING_PHASE) {

            g.getMouseLocation(c1.p.x, c1.p.y);

            g.drawImage(background);

        	checkCollisions(collisions, circles, circles);
        	points += collisions.size() * 25;
        	handleCollisions(collisions);

        	for (auto& i : circles) {
                g.setColor(i.c);
        		g.drawCircle(i.p, i.r);
            }

            stupidCat.angle += 0.25;
            g.drawImage(stupidCat);

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
