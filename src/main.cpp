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
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "SDL_Plotter.h"
#include "collision.h"

#define TO_DEGREES (180.0/3.141592653589793238463)

enum GameStatus {
	TITLE_SCREEN,
	GAME_RUN,
	END_SCREEN
};

enum RunEvent {
	SHOOTING_PHASE,
	BOUNCE_PHASE,
	MANAGE_ENEMIES
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

point getUniqueRandomPoint(vector <Circle> circles) {
	point p1;
	bool unique;

	do {
		p1.x = rand() % (1080 / 2 - 60) + 61;
		p1.y = 1920 / 2 - 70;
		unique = true;

		//for (int i = 1; i < circles.size(); ++i) {
			//if (fabs(p1.x - circles.at(i).p.x) < 120) {
			//	unique = false;
			//}
		//}
	} while (!unique);

	return p1;
}


int main() {

    // Data Abstraction:
	const int WIDTH = 1080 / 2;
	const int HEIGHT = 1920 / 2;
    SDL_Plotter g(HEIGHT, WIDTH);
    point p1 = {100, 100}, p2 = {200, 200};
    point spawnPoint = {200, 40};
    GameStatus myStatus = TITLE_SCREEN;
    RunEvent myEvent = SHOOTING_PHASE;
    double mouseX;
    double mouseY;
    double angle;
    int points = 0;

    srand(time(0));

    vector<Circle> circles;
    vector<Line> lines;
    vector<Image> enemies;

    Image titleScreen = {g.addImage("./images/titlescreen_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image endScreen = {g.addImage("./images/gameover_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image arm = {g.addImage("./images/arm.png"), {145, -60, 225, 225}, 0.0};
    Image background = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image projectile = {g.addImage("./images/projectile.png"), {WIDTH / 2 - 30, 100, 40, 40}, 0.0};

    circles.push_back({spawnPoint, 15, {0, 255, 255}});
    circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});
    circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});
    circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});

    Circle& c1 = circles[0];
    c1.f = {0, 0};
    vector<Collision> collisions {};
    vector<LineCollision> lineCollisions {};

    //lines.push_back({{100, 100}, {250, 700}});
    //lines.push_back({{400, 100}, {250, 700}});

    lines.push_back({{0, 0}, {0, HEIGHT}});
    lines.push_back({{0, 0}, {WIDTH, 0}});
    lines.push_back({{WIDTH, 0}, {WIDTH, HEIGHT}});

    enemies.push_back({g.addImage("./images/E1C1_unbroken.png"), {0, 0, 120, 120}, 0.0});
    enemies.push_back({g.addImage("./images/E1C2_unbroken.png"), {0, 0, 120, 120}, 0.0});
    enemies.push_back({g.addImage("./images/E2C1_unbroken.png"), {0, 0, 120, 120}, 0.0});

    // Input:

    // Process:

    while (!g.getQuit())
    {
    	g.clear();

        if (myStatus == TITLE_SCREEN) {
        	// Code to display title screen
            
            g.drawImage(titleScreen);
        	
            // Press a key (for now "e") to start

        	if (g.getKey() == 'e')
                myStatus = GAME_RUN;

        }
        else if (myStatus == GAME_RUN) {
            //g.getMouseLocation(c1.p.x, c1.p.y);

            // Add check if enemies colliding with top wall. If so
            // set myStatus = END_SCREEN

        	checkCollisions(collisions, circles, circles);
        	points += collisions.size() * 25;
        	handleCollisions(collisions);

            g.getMouseLocation(mouseX, mouseY);
            angle = atan2(mouseY - arm.rect.y, mouseX - arm.rect.x - arm.rect.w / 2);
			arm.angle = angle * TO_DEGREES - 90;

            c1.f = c1.f + force(0.0005, 3.14 / 2);
            c1.p.x += cos(c1.f.getDirection()) * c1.f.getMagnitude();
            c1.p.y += sin(c1.f.getDirection()) * c1.f.getMagnitude();

            checkCollisions(lineCollisions, circles, lines);
            handleCollisions(lineCollisions);

            g.drawImage(background);

            for (auto& i : circles) {
                g.setColor(i.c);
                g.drawCircle(i.p, i.r);
            }

            for (auto& i : lines)
        		g.drawLine(i.p1, i.p2);

            g.drawImage(projectile);

            for (int i = 0; i < enemies.size(); ++i) {
            	enemies.at(i).rect.x = circles.at(i + 1).p.x - 60;
            	enemies.at(i).rect.y = circles.at(i + 1).p.y - 60;

            	g.drawImage(enemies.at(i));
            }

            projectile.rect.x = c1.p.x - 20;
            projectile.rect.y = c1.p.y - 20;

            g.drawImage(arm, {arm.rect.w / 2, 0});


            if (g.getKey() == 't') {// Testing manage enemies
            	myEvent = MANAGE_ENEMIES;
            }

            if (myEvent == MANAGE_ENEMIES) {
            	for (int i = 1; i < circles.size(); ++i) {
            		circles.at(i).p.y -= 140;
            	}

                circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});
                circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});
                circles.push_back({getUniqueRandomPoint(circles), 60, {0, 0, 0}});

                enemies.push_back({g.addImage("./images/E1C1_unbroken.png"), {0, 0, 120, 120}, 0.0});
                enemies.push_back({g.addImage("./images/E1C2_unbroken.png"), {0, 0, 120, 120}, 0.0});
                enemies.push_back({g.addImage("./images/E2C1_unbroken.png"), {0, 0, 120, 120}, 0.0});

                myEvent = SHOOTING_PHASE;
             }

        }
        else if (myEvent == BOUNCE_PHASE) {

        }
        else if (myStatus == END_SCREEN) {
        	g.drawImage(endScreen);

        	// Display final score

        	if (g.getKey() == 'e')
        		myStatus = GAME_RUN;
        }

        g.update();
    }

    // Output:

    cout << "SCORE: " << points << endl;
    
    // Assumptions:
    // we get the project done
    
    return 0;
}
