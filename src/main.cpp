/*
 * Author: Caden Sullivan, Jace Prince,
 *         Elijah Robledo, Ava Callais
 * Assignment Title: Group Project
 * Assignment Description: Version of Falling Balls
 * Due Date: 12/08/2024
 * Date Created: 11/01/24
 * Date Last Modified: 12/06/2024
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <climits>
#include "SDL_Plotter.h"
#include "collision.h"
using namespace std;

#define PI_2 (PI / 2)
#define TO_DEGREES (180.0 / PI)
#define WIDTH (1080 / 2)
#define HEIGHT (1920 / 2)
#define SHOT_SIZE 40
#define SHOT_SIZE_2 (SHOT_SIZE / 2)
#define SHOT_IMAGE_SIZE (SHOT_SIZE * 1.46285714286)
#define SHOT_IMAGE_SIZE_2 (SHOT_IMAGE_SIZE / 2)
#define ENEMY_SIZE 80
#define ENEMY_SIZE_2 (ENEMY_SIZE / 2)
#define ENEMY_CAP (WIDTH / ENEMY_SIZE / 2)
#define SHOOTING_INTERVAL 500.0

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

/* desc: find an empty space
 * return: point
 * pre: a vector of circles
 * post: a point is found where enemy can reside
 */
point getUniqueRandomPoint(vector<Circle>& circles) {
	point p1;
	bool unique = false;
    Image emptyImage;
    vector<Collision> collisions;
    vector<Circle> tempCircles(1);
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

/* desc: generate random health value
 * return: int
 * pre: total enemies killed
 * post: health value
 */
int generateHealth(int enemiesKilled) {
	int health;
	health = rand() % static_cast<int>(enemiesKilled * 0.2 + 1) + (enemiesKilled + 4);
	return health;
}

/* desc: change enemy appearance based on health
 * return: void
 * pre: valid enemy and images
 * post: enemy image changed
 */
void enemyDamage(Circle& enemy, vector<Image> enemyImages) {
    bool finished = false;
    double healthRatio = static_cast<double>(enemy.currentHealth) / enemy.initialHealth;
	if (healthRatio < (1.0 / 4.0)) {
        for (int i = 8; i < 12 && !finished; i++) {
            if (enemy.image->texture == enemyImages.at(i).texture) {
			    enemy.image = &enemyImages.at(i + 4);
                bool finished = true;
            }
        }
	}
	else if (healthRatio < (2.0 / 4.0)) {
        for (int i = 4; i < 8 && !finished; i++) {
            if (enemy.image->texture == enemyImages.at(i).texture) {
			    enemy.image = &enemyImages.at(i + 4);
                bool finished = true;
            }
        }
	}
	else if (healthRatio < (3.0 / 4.0)){
        for (int i = 0; i < 4 && !finished; i++) {
            if (enemy.image->texture == enemyImages.at(i).texture) {
			    enemy.image = &enemyImages.at(i + 4);
                bool finished = true;
            }
        }
	}
}

int main() {

    // Data Abstraction:
    SDL_Plotter g(HEIGHT, WIDTH);
    GameStatus myStatus = TITLE_SCREEN;
    RunEvent myEvent = MANAGE_ENEMIES;
    double mouseX, mouseY, angle, oldRadianArmAngle, timer;
    int points = 0, enemiesKilled = 0, powerupsCollected = 0, shotsLeft = 1;
    chrono::steady_clock::time_point lastTime;
    float deltaTime;
    string fileName;
    string message;
    int nextId = 0, nextLId = 0;

    vector<Circle> shots, enemies, powerups;
    vector<Collision> collisions {};
    vector<LineCollision> lineCollisions {};

    Image titleScreen = {g.addImage("./images/titlescreen.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image endScreen   = {g.addImage("./images/gameover.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image arm         = {g.addImage("./images/arm.png"), {WIDTH / 2 - 113, -60, 225, 225}, 0.0};
    Image background  = {g.addImage("./images/bg.png"), {0, 0, WIDTH, HEIGHT}, 0.0};
    Image projectile  = {g.addImage("./images/projectile.png"), {WIDTH / 2 - 30, 100, static_cast<int>(SHOT_IMAGE_SIZE), static_cast<int>(SHOT_IMAGE_SIZE)}, 0.0};
    Image powerup 	  = {g.addImage("./images/powerup.png"), {0, 0, 50, 50}, 0.0};

    vector<Image> enemyImages = {
        {g.addImage("./images/E1C1_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C2_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C1_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C2_unbroken.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C1_cracked1.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C2_cracked1.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C1_cracked1.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C2_cracked1.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C1_cracked2.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C2_cracked2.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C1_cracked2.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C2_cracked2.png"), {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C1_broken.png"),   {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E1C2_broken.png"),   {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C1_broken.png"),   {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0},
        {g.addImage("./images/E2C2_broken.png"),   {0, 0, ENEMY_SIZE, ENEMY_SIZE}, 0.0}
    };

    vector<Line> lines = {
        {{0, 0}, {0, HEIGHT}, nextLId++},
        {{0, 0}, {WIDTH, 0}, nextLId++},
        {{WIDTH, 0}, {WIDTH, HEIGHT}, nextLId++}
    };

    // Input/Process/Output:

    srand(time(0));

    lastTime = chrono::steady_clock::now();
    while (!g.getQuit()) {
    	g.clear();

        auto now = chrono::steady_clock::now();
        deltaTime = chrono::duration_cast<chrono::microseconds>(now - lastTime).count() / 1000.0f;
        lastTime = now;

        switch (myStatus) {
            case TITLE_SCREEN:
                // Code to display title screen    
                g.drawImage(&titleScreen);
                
                // Press a "e" to start
                if (g.getKey() == 'e') {
                    myStatus = GAME_RUN;
                }

                break;

            case GAME_RUN: {

            	message = "Score: " + to_string(points);
                for (int i = 0; i < 20 - message.size(); i++) message += " ";
                g.getMouseLocation(mouseX, mouseY);
                g.drawImage(&background);
                g.write(message.c_str(), {20, 25, 190, 25}, {0, 0, 0});
                g.write(message.c_str(), {20, 20, 190, 25}, {255, 255, 255});

                double radianArmAngle = clamp(atan2(mouseY - arm.rect.y, mouseX - arm.rect.x - arm.rect.w / 2), 0.5, PI - 0.5);
                arm.angle = radianArmAngle * TO_DEGREES - 90;

                switch (myEvent) {
                    case SHOOTING_PHASE:
                    
                        shots.at(0).p.x = cos(radianArmAngle) * 200 + WIDTH / 2;
                        shots.at(0).p.y = sin(radianArmAngle) * 200 - 60;

                        if (g.mouseClick()) {
                            oldRadianArmAngle = radianArmAngle;
                            shotsLeft = powerupsCollected + 1;
                            timer = SHOOTING_INTERVAL;
                            myEvent = BOUNCE_PHASE;
                        }

                        break;

                    case BOUNCE_PHASE:
                        timer += deltaTime;
                        
                        if (shotsLeft > 0) {
                            shots.at(shots.size() - 1).p.x = cos(oldRadianArmAngle) * 200 + WIDTH / 2;
                            shots.at(shots.size() - 1).p.y = sin(oldRadianArmAngle) * 200 - 60;
                        }

                        if (timer >= SHOOTING_INTERVAL && shotsLeft-- > 0) {
                            shots.at(shots.size() - 1).f = {0.5, oldRadianArmAngle};
                            if (shotsLeft > 0) shots.push_back(shots.at(shots.size() - 1));
                            timer = 0.0;
                        }
                        // apply force to balls
                        for (Circle& i : shots) {
                            i.f.apply(force(0.005, PI_2));
                            i.p.x += cos(i.f.getDirection()) * i.f.getMagnitude() * deltaTime;
                            i.p.y += sin(i.f.getDirection()) * i.f.getMagnitude() * deltaTime;
                        }

                        // remove balls that have fallen off screen
                        for (int i = 0; i < shots.size(); i++)
                            if (shots.at(i).p.y > HEIGHT + SHOT_SIZE_2)
                                shots.erase(shots.begin() + i);

                        // handle collisions
                        checkCollisions(collisions, shots, shots);
                        checkCollisions(collisions, shots, enemies);
                        checkCollisions(collisions, shots, powerups);
                        handleCollisions(collisions);

                        checkCollisions(lineCollisions, shots, lines);
                        handleCollisions(lineCollisions);
                        
                        for (int i = 0; i < powerups.size(); ++i) {
                            if (powerups.at(i).currentHealth < 0) {
                                powerups.erase(powerups.begin() + i);
                                ++powerupsCollected;
                                // realign i with changed vec
                                i--;
                            }
                        }

                        for (int i = 0; i < enemies.size(); ++i) {
                            enemyDamage(enemies.at(i), enemyImages);

                            if (enemies.at(i).currentHealth <= 0) {
                                enemies.erase(enemies.begin() + i);
                                ++enemiesKilled;
                                // realign i with changed vec
                                i--;
                                points += 25;
                            }
                        }

                        if (!shots.size()) {
                            myEvent = MANAGE_ENEMIES;
                            timer = 0.0;
                        }

                        break;

                    case MANAGE_ENEMIES:
                        for (Circle& i : enemies)
                            i.p.y -= 140;

                        for (Circle& i : powerups)
                            i.p.y -= 140;

                        for (int i = 0; i <= rand() % ENEMY_CAP; i++) {
                            int health = generateHealth(enemiesKilled);
                            enemies.push_back({getUniqueRandomPoint(enemies),
                                               ENEMY_SIZE_2,
                                               &enemyImages.at(rand() % 4),
                                               {},
                                               health,
											   health,
                                               nextId++});
                        }

                        for (Circle& i : enemies) {
                        	if (i.p.y < 150) {
                        		myStatus = END_SCREEN;
                        	}
                        }

                        if ((rand() % 15) == 5) {
                            powerups.push_back({getUniqueRandomPoint(enemies), 25, &powerup, {}, 0, 0, nextId++});
                        }

                        shots.push_back({{}, SHOT_SIZE_2, &projectile, {0, 0}, INT_MAX, INT_MAX, nextId++});

                        myEvent = SHOOTING_PHASE;

                        break;
                }

                for (Circle& i : enemies) {
                    i.image->rect.x = i.p.x - ENEMY_SIZE_2;
                    i.image->rect.y = i.p.y - ENEMY_SIZE_2;
                    g.drawImage(i.image);
                }

                for (Circle& i : shots) {
                    i.image->rect.x = i.p.x - SHOT_IMAGE_SIZE_2;
                    i.image->rect.y = i.p.y - SHOT_IMAGE_SIZE_2;
                    g.drawImage(i.image);
                }

                for (Circle& i : powerups) {
                	i.image->rect.x = i.p.x - 25;
                	i.image->rect.y = i.p.y - 25;
                	g.drawImage(i.image);
                }

                g.drawImage(&arm, {arm.rect.w / 2, 0});

                break;
            }

            case END_SCREEN:
                g.drawImage(&endScreen);

                myEvent = MANAGE_ENEMIES;

                if (points < 1000) {
                	g.write(message.c_str(), {WIDTH / 2 - 140, HEIGHT / 2, 450, 45}, {255, 0, 0});
                }
                else if (points < 5000) {
                	g.write(message.c_str(), {WIDTH / 2 - 140, HEIGHT / 2, 450, 45}, {255, 255, 0});
                }
                else {
                	g.write(message.c_str(), {WIDTH / 2 - 140, HEIGHT / 2, 450, 45}, {0, 255, 0});
                }

                if (g.getKey() == 'e') {
                    myStatus = GAME_RUN;

                    enemies.clear();
                    powerups.clear();
                    shots.clear();

                	enemiesKilled = 0;
                	powerupsCollected = 0;
                	points = 0;
                }
        }

        g.update();
    }

    // Output:
    
    return 0;
}
