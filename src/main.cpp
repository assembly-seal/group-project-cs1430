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

    vector<Circle> shots, enemies;
    vector<Line> lines {};
    vector<Collision> collisions {};
    vector<LineCollision> lineCollisions {};

    Image titleScreen = {g.addImage("./images/titlescreen_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image endScreen   = {g.addImage("./images/gameover_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image arm         = {g.addImage("./images/arm.png"), {145, -60, 225, 225}, 0.0};
    Image background  = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image projectile  = {g.addImage("./images/projectile.png"), {WIDTH / 2 - 30, 100, 40, 40}, 0.0};
    Image E1C1        = {g.addImage("./images/E1C1_unbroken.png"), {0, 0, 120, 120}, 0.0};
    Image E1C2        = {g.addImage("./images/E1C2_unbroken.png"), {0, 0, 120, 120}, 0.0};
    Image E2C1        = {g.addImage("./images/E2C1_unbroken.png"), {0, 0, 120, 120}, 0.0};

    shots.push_back({spawnPoint, 15, projectile, {0, 0}});
    enemies.push_back({getUniqueRandomPoint(enemies), 60, E1C1});
    enemies.push_back({getUniqueRandomPoint(enemies), 60, E1C1});
    enemies.push_back({getUniqueRandomPoint(enemies), 60, E1C1});

    lines.push_back({{0, 0}, {0, HEIGHT}});
    lines.push_back({{0, 0}, {WIDTH, 0}});
    lines.push_back({{WIDTH, 0}, {WIDTH, HEIGHT}});

    // Input:
    // Process:

    while (!g.getQuit()) {
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

                        checkCollisions(collisions, shots, enemies);
                        points += collisions.size() * 25;
                        handleCollisions(collisions);

                        if (g.getKey() == 't') myEvent = MANAGE_ENEMIES;

                        break;

                    case MANAGE_ENEMIES:
                        for (Circle& i : enemies)
                            i.p.y -= 140;

                        for (int i = 0; i < 3; i++)
                            enemies.push_back({getUniqueRandomPoint(enemies), 60, E1C1});

                        myEvent = SHOOTING_PHASE;

                        break;
                }

                for (Circle& i : enemies) {
                    i.image.rect.x = i.p.x - 60;
                    i.image.rect.y = i.p.y - 60;

                    g.drawImage(i.image);
                }

                for (Circle& i : shots) {
                    i.image.rect.x = i.p.x - 20;
                    i.image.rect.y = i.p.y - 20;

                    g.drawImage(i.image);
                }

                g.drawImage(arm, {arm.rect.w / 2, 0});

                break;

            case END_SCREEN:
                g.drawImage(endScreen);

                // Display final score
                if (g.getKey() == 'e')
                    myStatus = GAME_RUN;

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
