#ifndef TETRIS_H
#define TETRIS_H

#include "piece.h"
#include "timer.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

#define M_DX 	30
#define M_DY	44 //40 + 4 del piece che all'inizio è sopra e non si vede

class Tetris{
	private:
		Piece * pezzo;
		vector< vector< int > > matrix;
		int points;
		SDL_Surface * img;
		bool end;
		Timer timer;
		int attesa;
		
		void init();
	public:
		Tetris();
		~Tetris();
		
		int getPoints() const;
		Piece * getPiece() const;
		bool getCollision();
		bool getEnd() const;
		SDL_Surface * getImg() const;
		
		void setEnd(bool);
		void setPoints(int);
		void addPoints();
		void setImg(string);
		void setDirection(int);
		
		void setControll();
		void onMatrix();
		void play();
		void draw(SDL_Surface *);
};
#endif
