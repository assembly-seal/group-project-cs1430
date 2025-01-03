/*
 * SDL_Plotter.h
 *
 * Version 3.1
 * Add: color and point constructors
 * 12/14/2022
 *
 * Version 3.0
 * 5/31/2022
 *
 * Version 2.4
 * 4/4/2022
 *
 * Version 2.3
 *  6/28/2021
 *
 * Version 2.2
 *  4/26/2019
 *
 *  Dr. Booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

//OSX Library
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Windows Library
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <queue>
#include <vector>
#include "image.h"
using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int  RED_SHIFT    = 65536;
const int  GREEN_SHIFT  = 256;
const int  BLUE_SHIFT   = 1;
const int  ALPHA_SHIFT  = 16777216;
const int  WHITE        = 255;
const int  MAX_THREAD   = 100;


//Point
struct point{
	double x,y;
	point(){
		x = y = 0;
	}

	point(double x, double y){
		this->x = x;
		this->y = y;
	}
};

//Color
struct color{
	unsigned int R,G,B;
	color(){
		R = G = B = 0;
	}

	color(int r, int g, int b){
		R = r;
		G = g;
		B = b;
	}
};

//Threaded Sound Function
struct param{
	bool play;
	bool running;
	bool pause;
	SDL_Thread*  threadID;
	SDL_cond  *cond;
	SDL_mutex *mut;
	string name;

	param(){
		play = false;
		running = false;
		pause = false;
	    cond = nullptr;
	    mut  = nullptr;
	    threadID = nullptr;
	    name="";
	}
};


class SDL_Plotter{
private:
	SDL_Texture  *texture;
    SDL_Renderer *renderer;
	SDL_Window   *window;
    Uint32       *pixels;
    const Uint8  *currentKeyStates;
    SDL_Event    event;
    int          row, col;
    TTF_Font* font;
    bool         quit;

    //Keyboard Stuff
    queue<char> key_queue;

    //Mouse Stuff
    queue<point> click_queue;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

    char getKeyPress(SDL_Event & event);

public:
    SDL_Plotter(int r=480, int c=640, bool WITH_SOUND = true);
    ~SDL_Plotter();
    void update();

    bool getQuit();
    void setQuit(bool flag);

    bool kbhit();
    bool mouseClick();
    char getKey();
    point getMouseClick();

    void plotPixel(int x, int y, int r, int g, int b);
    void plotPixel(point p, int r, int g, int b);
    void plotPixel(int x, int y, color=color{});
    void plotPixel(point p, color=color{});

    void clear();
    int getRow();
    int getCol();

    void initSound(string sound);
    void playSound(string sound);
    void quitSound(string sound);

    void Sleep(int ms);

    bool getMouseDown(int& x, int& y);
    bool getMouseUp(int& x, int& y);
    bool getMouseMotion(int& x, int& y);
    void getMouseLocation(double& x, double& y);

    Uint32 getColor(int x, int y);

    /* FUNCTIONS ADDED BY CADEN */

    
/* desc: set renderer color
* return: void
* pre: valid color
* post: renderer color set
*/
    void setColor(color);

/* desc: draw a circle on screen
 * return: void
 * pre: valid point and radius
 * post: circle is drawn
 */
    void drawCircle(point, int);

/* desc: create an sdl texture from an image
 * return: SDL_Texture*
 * pre: string pointing to a valid image file
 * post: a useable image is added and its address is given
 */
    SDL_Texture* addImage(const char*);

/* desc: draw an image to the screen
 * return: void
 * pre: valid image, valid point
 * post: image is drawn
 */
    void drawImage(Image*, SDL_Point = {0, 0});

/* desc: draw a line between two points on the screen
 * return: void
 * pre: 2 valid points
 * post: line drawn
 */
    void drawLine(point p1, point p2);

/* desc: write text to the screen
 * return: void
 * pre: valid string for message, valid rect, valid color
 * post: text written to screen
 */
    void write(const char* message, SDL_Rect rect, SDL_Color c);
};

#endif // SDL_PLOTTER_H_
