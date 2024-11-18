/*
 * SDL_Plotter.h
 *
 * Version 3.0
 * 5/20/2022
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

#include "SDL_Plotter.h"

//Threaded Sound Function

static int Sound(void *data){
	param *p = (param*)data;
	p->running = true;
	Mix_Chunk *gScratch = NULL;
	gScratch = Mix_LoadWAV( p->name.c_str() );


	while(p->running){
		SDL_mutexP( p->mut );
		  SDL_CondWait(p->cond, p->mut);
		  Mix_PlayChannel( -1, gScratch, 0 );
		  p->play = false;
		SDL_mutexV(p->mut);
	}

	Mix_FreeChunk( gScratch );
	p->running = false;
	return 0;
}


// SDL Plotter Function Definitions

SDL_Plotter::SDL_Plotter(int r, int c, bool WITH_SOUND){
	row = r;
	col = c;
	//leftMouseButtonDown = false;
	quit = false;
	SOUND = WITH_SOUND;
	currentKeyStates = NULL;

	SDL_Init(SDL_INIT_AUDIO);

    window   = SDL_CreateWindow("SDL2 Pixel Drawing",
    		                     SDL_WINDOWPOS_UNDEFINED,
    		                     SDL_WINDOWPOS_UNDEFINED, col, row, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);

    currentKeyStates = SDL_GetKeyboardState( NULL );

    //SOUND Thread Pool
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    soundCount = 0;
    update();
  }

SDL_Plotter::~SDL_Plotter(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Plotter::update() {
    SDL_RenderPresent(renderer);
}

Uint32 SDL_Plotter::getColor(int x, int y){
    return pixels[y * col + x];
}

bool SDL_Plotter::getQuit(){
	//Handle events on queue
	while( SDL_PollEvent( &event ) != 0 )
	{
		if(event.type == SDL_TEXTINPUT){
			key_queue.push(getKeyPress(event));
		}
		else if(event.type == SDL_KEYDOWN){
			//Make the arrow keys work
			if(currentKeyStates[SDL_SCANCODE_DOWN])  key_queue.push(DOWN_ARROW);
			if(currentKeyStates[SDL_SCANCODE_UP])    key_queue.push(UP_ARROW);
			if(currentKeyStates[SDL_SCANCODE_LEFT])  key_queue.push(LEFT_ARROW);
			if(currentKeyStates[SDL_SCANCODE_RIGHT]) key_queue.push(RIGHT_ARROW);
		}
		else if(event.type == SDL_MOUSEBUTTONUP){
			point p;
			SDL_GetMouseState( &p.x, &p.y );
			click_queue.push(p);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN){
			//SDL_GetMouseState( &mouse_X, &mouse_Y );
			//mouseClick = true;
		}
		else if(event.type == SDL_MOUSEMOTION){
			//SDL_PushEvent(&event);
		}

		if(event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_ESCAPE]){
			quit = true;
		}
	}
	return quit;
}

bool SDL_Plotter::kbhit(){
	return key_queue.size() > 0;
}

bool SDL_Plotter::mouseClick(){
	return click_queue.size() > 0;
}


char SDL_Plotter::getKeyPress(SDL_Event & event){
	return *event.text.text;
}

char SDL_Plotter::getKey(){
    char key = '\0';
    if(key_queue.size() > 0){
    	key = key_queue.front();
    	key_queue.pop();
    }

    return key;
}

point SDL_Plotter::getMouseClick(){
	point p;
    if (click_queue.size() > 0) {
    	p = click_queue.front();
    	click_queue.pop();
    }

	return p;
}


void SDL_Plotter::plotPixel(point p, int r, int g, int b){
	plotPixel(p.x,  p.y,  r,  g,  b);
}

void SDL_Plotter::plotPixel(int x, int y, color c){
	plotPixel(x,  y,  c.R,  c.G,  c.B);
}

void SDL_Plotter::plotPixel(point p, color c){
	plotPixel(p.x,  p.y,  c.R,  c.G,  c.B);
}


void SDL_Plotter::plotPixel(int x, int y, int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

void SDL_Plotter::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

int SDL_Plotter::getRow(){
    return row;
}

int SDL_Plotter::getCol(){
    return col;
}

void SDL_Plotter::initSound(string sound){
	if(!soundMap[sound].running){
			param* p = &soundMap[sound];
			p->name = sound;
			p->cond = SDL_CreateCond();
			p->mut = SDL_CreateMutex();

			p->threadID = SDL_CreateThread( Sound, sound.c_str(), (void*)p );
	}
}

void SDL_Plotter::setQuit(bool flag){
	this->quit = flag;
}

void SDL_Plotter::playSound(string sound){
	if(soundMap[sound].running){
		SDL_CondSignal(soundMap[sound].cond);
	}
}

void SDL_Plotter::quitSound(string sound){
	soundMap[sound].running = false;
	SDL_CondSignal(soundMap[sound].cond);
}

void SDL_Plotter::Sleep(int ms){
	SDL_Delay(ms);
}


bool SDL_Plotter::getMouseDown(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONDOWN){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

bool SDL_Plotter::getMouseUp(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONUP){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

bool SDL_Plotter::getMouseMotion(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEMOTION){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

void SDL_Plotter::getMouseLocation(int& x, int& y){
    SDL_GetMouseState(&x, &y);
}

/* FUNCTIONS ADDED BY CADEN */

void SDL_Plotter::setRectangle(int x, int y, int w, int h) {
    rect = {x, y, w, h};
}

void SDL_Plotter::drawCircle(int x_pos, int y_pos, int radius) {
    double t1 = radius / 16.0;
    int x = radius;
    int y = 0;

    while (x > y) {
        setRectangle(-x + x_pos, y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(-y + x_pos, x + y_pos - 1, y * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(-x + x_pos, -y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(-y + x_pos, -x + y_pos + 1, y * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);

        y++;
        t1 += y;
        double t2 = t1 - x;
        if (t2 >= 0) {
            t1 = t2;
            x--;
        }
    }
}
