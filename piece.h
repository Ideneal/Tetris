#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

#define P_DX	4
#define P_DY	4

class Piece{
	private:
		vector< vector< int > > piece;
		int posx;
		int posy;
		int width;
		int height;
		int dx;
		int dy;
		
		vector< vector< int > > makePiece(int);
	public:
		Piece(int = -1);
		~Piece();
		
		vector< vector<int> > getPiece() const;
		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;
		int getValue(int, int) const;
		int getDX() const;
		int getDY() const;
		
		void setDX(int);
		void setDY(int);
		void setX(int);
		void setY(int);
		
		void rotate();
		void move();
};
#endif
