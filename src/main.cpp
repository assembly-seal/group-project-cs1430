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
		p1.x = rand() % (1080 / 2) + 1;
		p1.y = 1920 / 2 - 70;
		unique = true;

		for (int i = 0; i < circles.size(); ++i) {
			if (fabs(p1.x - circles.at(i).p.x) < 100) {
						unique = false;
					}
		}
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

    vector<Circle> shots;
    vector<Circle> enemies;
    vector<Line> lines;

    circles.push_back({spawnPoint, 10, {0, 255, 255}});
    circles.push_back({getUniqueRandomPoint(circles), 50, {255, 0, 0}});
    circles.push_back({getUniqueRandomPoint(circles), 50, {255, 0, 0}});
    circles.push_back({getUniqueRandomPoint(circles), 50, {255, 0, 0}});

    Circle& c1 = circles[0];
    c1.f = {0, 0};
    vector<Collision> collisions {};
    vector<LineCollision> lineCollisions {};

    lines.push_back({{100, 100}, {250, 700}});
    lines.push_back({{400, 100}, {250, 700}});

    Image titleScreen = {g.addImage("./images/titlescreen_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image arm = {g.addImage("./images/arm.png"), {145, -80, 250, 250}, 0.0};
    Image background = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image projectile = {g.addImage("./images/projectile.png"), {WIDTH / 2 - 30, 100, 60, 60}, 0.0};
    // Input:

    // Process:

    while (!g.getQuit())
    {
    	g.clear();

        switch (myStatus) {
            case TITLE_SCREEN:
                // Code to display title screen    
                g.drawImage(titleScreen);
                
                // Press a key (for now "e") to start
                if (g.getKey() == 'e')
                    myStatus = GAME_RUN;
            
                break;

            case GAME_RUN:

                g.getMouseLocation(mouseX, mouseY);
                g.drawImage(background);

                switch (myEvent) {
                    case SHOOTING_PHASE:
                    case BOUNCE_PHASE:

                        checkCollisions(collisions, circles, circles);
                        points += collisions.size() * 25;
                        handleCollisions(collisions);

                        break;

                    case MANAGE_ENEMIES:
                        for (int i = 1; i < circles.size(); ++i)
                            circles.at(i).p.y -= 100;

                        circles.push_back({getUniqueRandomPoint(circles), 50, {255, 0, 0}});
                        circles.push_back({getUniqueRandomPoint(circles), 50, {255, 0, 0}});

                        myEvent = SHOOTING_PHASE;
                }

                arm.angle = atan2(mouseY - arm.rect.y, mouseX - arm.rect.x - arm.rect.w / 2) *
                            TO_DEGREES - 90;

                c1.f = c1.f + force(0.0005, 3.14 / 2);
                c1.p.x += cos(c1.f.getDirection()) * c1.f.getMagnitude();
                c1.p.y += sin(c1.f.getDirection()) * c1.f.getMagnitude();

                checkCollisions(lineCollisions, circles, lines);
                handleCollisions(lineCollisions);

                for (auto& i : circles) {
                    g.setColor(i.c);
                    g.drawCircle(i.p, i.r);
                }

                for (auto& i : lines)
                    g.drawLine(i.p1, i.p2);
                g.drawImage(projectile);
                g.drawImage(arm, {arm.rect.w / 2, 0});

                if (g.getKey() == 't') myEvent = MANAGE_ENEMIES;

                    myEvent = SHOOTING_PHASE;
                }

                break;

            case END_SCREEN:
                break;
        }

        g.update();
    }

    // Output:

    cout << "SCORE: " << points << endl;
    
    // Assumptions:
    // we get the project done
    
    return 0;
}
