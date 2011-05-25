#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include "piece.h"
#include "tetris.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define SCREEN_DEPTH 32

using namespace std;

SDL_Surface * loadbg(string name){
	SDL_Surface * oldimg = IMG_Load(name.c_str());
	if (oldimg == NULL){
		cout << "Error to load background : " << SDL_GetError()<<endl;
		return NULL;
	}
	SDL_Surface * bg = SDL_DisplayFormat(oldimg);
	SDL_FreeSurface(oldimg);
	return bg;
}

void putstring(SDL_Surface * screen, TTF_Font * font, const char * string, uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B)
{
	
	SDL_Color color;
	SDL_Rect * fontRect = new SDL_Rect();

	color.r = R;
	color.g = G;
	color.b = B;

	SDL_Surface * fontSurface = TTF_RenderText_Solid(font, string, color);
        fontRect->x = x;
        fontRect->y = y;
        fontRect->h = 50;
        fontRect->w = 50;

        SDL_BlitSurface(fontSurface, NULL, screen, fontRect);
	SDL_Flip(screen);
	SDL_FreeSurface(fontSurface);
	delete fontRect;
}

int main() {
	stringstream score;
	SDL_Surface * screen = 0;
	bool running = true;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE | SDL_DOUBLEBUF);
	TTF_Font * font = TTF_OpenFont("Bandal.ttf", 28);
	if(font == NULL){
		cout << "Impossibile caricare il font : "<<SDL_GetError()<<endl;
		exit(1);
	}
	
	Tetris * game = new Tetris();
	
	SDL_Surface * bg = loadbg("black_background.bmp");
	
	SDL_Event * event = new SDL_Event();
     	while(!game->getEnd() && running){
     		while(SDL_PollEvent(event)){
     			if(event->type == SDL_QUIT)
     				running = false;
     			if(event->type == SDL_KEYDOWN){
     				if(event->key.keysym.sym == SDLK_SPACE){
     					game->setDirection(4);
     				}
     				if(event->key.keysym.sym == SDLK_RIGHT){
     					game->setDirection(1);
     				}
     				if(event->key.keysym.sym == SDLK_LEFT){
     					game->setDirection(2);
     				}
     				if(event->key.keysym.sym == SDLK_DOWN){
     					game->setDirection(3);
     				}
     			}
     			if(event->type == SDL_KEYUP){
     				if(event->key.keysym.sym == SDLK_DOWN){
     					game->setDirection(3);
     				}
     			}
     		}
     		SDL_BlitSurface(bg, NULL, screen, NULL);
     		game->play();
     		game->draw(screen);
     		score.str("");
     		score << "Score : "<<game->getPoints();
     		putstring(screen, font, score.str().c_str(), 0,0,0xff,0xff,0xff);
     		
     		if(SDL_Flip(screen) == -1)
     			return 1;
     		SDL_Delay(10);
    	}
    	
    	delete game;
    	TTF_CloseFont(font);
    	TTF_Quit();
    	SDL_FreeSurface(screen);
    	SDL_Quit();
    	return 0;
}
