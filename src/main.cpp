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

#define TO_DEGREES (180.0 / 3.141592653589793238463)
#define WIDTH (1080 / 2)
#define HEIGHT (1920 / 2)
#define ENEMY_SIZE 80
#define ENEMY_SIZE_2 (ENEMY_SIZE / 2)

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


// TODO: REMOVE
void drawCircle(point loc, int size, color c, SDL_Plotter& g){
	for(double i = -size; i <= size;i+=0.1){
		for(double j = -size; j <= size; j+=0.1){
			if(i*i + j*j <= size*size){
				g.plotPixel(round(loc.x+i),round(loc.y+j),c);
			}
		}
	}
}

point getUniqueRandomPoint(vector<Circle>& circles) {
	point p1;
	bool unique = false;
    Image emptyImage;
    vector<Collision> collisions;
    vector<Circle> tempCircles = {{.image = emptyImage}};
    Circle& dummy = tempCircles.at(0);

	do {
        collisions.clear();
		p1.x = rand() % (WIDTH - ENEMY_SIZE) + ENEMY_SIZE_2;
		p1.y = HEIGHT - ENEMY_SIZE_2 - 10;

        dummy.p = p1;
        dummy.r = ENEMY_SIZE_2;

        checkCollisions(collisions, tempCircles, circles);

        unique = collisions.size() == 0;
	} while (!unique);

	return p1;
}

int generateHealth(int enemiesKilled) {
	int health;

	if (enemiesKilled < 5) {
		health = (rand() % (8 - 5)) + 5;
	}
	else if (enemiesKilled < 15) {
		health = (rand() % (15 - 8)) + 8;
	}
	else if (enemiesKilled < 25) {
		health = (rand() % (25 - 15)) + 15;
	}
	else if (enemiesKilled < 35) {
		health = (rand() % (35 - 25)) + 25;
	}
	else if (enemiesKilled < 45) {
		health = (rand() % (45 - 35)) + 35;
	}
	else if (enemiesKilled < 55) {
		health = (rand() % (65 - 45)) + 45;
	}
	else {
		health = (rand() % (75 - 45)) + 45;
	}

	return health;
}

int main() {

    // Data Abstraction:
    SDL_Plotter g(HEIGHT, WIDTH);
    point p1 = {100, 100}, p2 = {200, 200};
    point spawnPoint = {200, 40};
    GameStatus myStatus = TITLE_SCREEN;
    RunEvent myEvent = SHOOTING_PHASE;
    double mouseX;
    double mouseY;
    double angle;
    int points = 0;
    int enemiesKilled = 0;
    int powerupsCollected = 0;

    srand(time(0));

    vector<Circle> shots, enemies;
    vector<Image> enemyImages;
    vector<Line> lines {};
    vector<Collision> collisions {};
    vector<LineCollision> lineCollisions {};

    Image titleScreen = {g.addImage("./images/titlescreen_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image endScreen   = {g.addImage("./images/gameover_temp.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image arm         = {g.addImage("./images/arm.png"), {145, -60, 225, 225}, 0.0};
    Image background  = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image projectile  = {g.addImage("./images/projectile.png"), {WIDTH / 2 - 30, 100, 40, 40}, 0.0};

    enemyImages.push_back({g.addImage("./images/E1C1_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0});
    enemyImages.push_back({g.addImage("./images/E1C2_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0});
    enemyImages.push_back({g.addImage("./images/E2C1_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0});
    enemyImages.push_back({g.addImage("./images/E2C2_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0});

    shots.push_back({spawnPoint, 15, projectile, {0, 0}});

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
                if (g.getKey() == 'e') {
                    myStatus = GAME_RUN;
                    for (int i = 0; i < 3; ++i) {
                    	int num = rand() % 4;
                    	enemies.push_back({getUniqueRandomPoint(enemies), ENEMY_SIZE_2, enemyImages.at(num)});
                    }
                }

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

                        for (int i = 0; i < 3; i++) {
                        	int num = rand() % 4;
                            enemies.push_back({getUniqueRandomPoint(enemies), ENEMY_SIZE_2, enemyImages.at(num)});
                        }

                        for (Circle& i : enemies) {
                        	if (i.p.y < 150) {
                        		myStatus = END_SCREEN;
                        	}
                        }

                        myEvent = SHOOTING_PHASE;

                        break;
                }

                for (Circle& i : enemies) {
                    i.image.rect.x = i.p.x - ENEMY_SIZE_2;
                    i.image.rect.y = i.p.y - ENEMY_SIZE_2;

                    g.drawImage(i.image);
                }

                for (Circle& i : shots) {
                    i.image.rect.x = i.p.x - 20;
                    i.image.rect.y = i.p.y - 20;

                    g.drawImage(i.image);
                }

	    		arm.angle = atan2(mouseY - arm.rect.y, mouseX - arm.rect.x - arm.rect.w / 2) *
                            TO_DEGREES - 90;
                g.drawImage(arm, {arm.rect.w / 2, 0});

                break;

            case END_SCREEN:
                g.drawImage(endScreen);

                enemies.clear();

                // Display final score
                if (g.getKey() == 'e') {
                    myStatus = GAME_RUN;
                    for (int i = 0; i < 3; ++i) {
                    	int num = rand() % 4;
                    	enemies.push_back({getUniqueRandomPoint(enemies), ENEMY_SIZE_2, enemyImages.at(num)});
                    }
                }

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
