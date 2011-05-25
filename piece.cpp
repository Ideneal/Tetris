#include "piece.h"

vector< vector< int > > Piece::makePiece(int n){
	vector< vector< int > > lol;
	vector<int> asd(P_DX, 0);
	//init vector
	for(int i=0; i<P_DY; i++)
		lol.push_back(asd);
	//switch n
	switch(n){
		case 1:
			//quadrato
			for(int i = 1; i<3; i++)
				for(int j = 0; j<2; j++)
					lol[i][j] = 1;
			this->width = 2;
			this->height = 2;
			break;
		case 2:
			//L
			for(int i=0; i<3; i++){
				lol[i][0] = 1;
				if(i==2) lol[i][1] = 1;
			}
			this->width = 2;
			this->height = 3;
			break;
		case 3:
			//I
			for(int i=0; i<4; i++)
				lol[i][0] = 1;
			this->width = 1;
			this->height = 4;
			break;
		case 4:
			//Z
			lol[0][0] = 1;
			lol[0][1] = 1;
			lol[1][1] = 1;
			lol[1][2] = 1;
			this->width = 3;
			this->height = 2;
			break;
		case 5:
			//T
			for(int i=0; i<3; i++)
				lol[0][i] = 1;
			lol[1][1] = 1;
			this->width = 3;
			this->height = 2;
			break;
		case 6:
			//L ribaltata
			for(int i=0; i<3; i++)
				lol[i][1] = 1;
			lol[2][0] = 1;
			this->width = 2;
			this->height = 3;
			break;
		case 7:
			//Z ribaltata
			lol[0][2] = 1;
			lol[0][1] = 1;
			lol[1][1] = 1;
			lol[1][0] = 1;
			this->width = 3;
			this->height = 2;
			break;
			
	}
	return lol;
}

Piece::Piece(int n){
	srand(time(NULL));
	if(n<8 && n>0)
		this->piece = this->makePiece(n);
	else
		this->piece = this->makePiece((rand() % 7) + 1);
	this->posx = 13;
	this->posy = 0;
	this->dx = 0;
	this->dy = 1;
}

Piece::~Piece(){
}

vector< vector<int> > Piece::getPiece() const{
	return this->piece;
}

int Piece::getX() const{
	return this->posx;
}

int Piece::getY() const{
	return this->posy;
}

int Piece::getWidth() const{
	return this->width;
}

int Piece::getHeight() const{
	return this->height;
}

int Piece::getValue(int dex, int dey) const {
	if(dex < 5 && dex >= 0 && dey < 5 && dey >=0)
		return this->piece[dex][dey];
	else
		return -1;
}

int Piece::getDX() const{
	return this->dx;
}

int Piece::getDY() const{
	return this->dy;
}

void Piece::setDX(int x){
	this->dx = x;
}

void Piece::setDY(int y){
	this->dy = y;
}

void Piece::setX(int x){
	this->posx = x;
}

void Piece::setY(int y){
	this->posy = y;
}

void Piece::rotate(){
	/*Bisogna effettuare la trasposta della matrice e ribaltarla...
	ovvero scambiare la prima riga con l'ultima (questo implica dei controlli ulteriori)*/
	int n;
	//trasposta
	for(int i=0; i<P_DY; i++){
		for(int j=0; j<i; j++){
			n = this->piece[i][j];
			this->piece[i][j] = this->piece[j][i];
			this->piece[j][i] = n;
		}
	}
	//ribaltamento
	for(int i=0; i<P_DY; i++){
		n = this->piece[0][i];
		this->piece[0][i] = this->piece[2][i];
		this->piece[2][i] = n;
	}
	//riallineamento
	while(this->piece[0][0] == 0 && this->piece[1][0] == 0 && this->piece[2][0] == 0 && this->piece[3][0] == 0){
		for(int i=0; i<P_DY; i++){
			for(int j=1; j<P_DX; j++){
				this->piece[i][j-1] = this->piece[i][j];
			}
		}
		for(int i=0; i<P_DY; i++){
			this->piece[i][3] = 0;
		}
	}
	//width e height vanno invertite
	n = this->width;
	this->width = this->height;
	this->height = n;
}

void Piece::move(){
	this->posy += this->dy;
	this->posx += this->dx;
	if(this->posx < 0  ||  this->posx > 30 - this->width){
		this->dx = -this->dx;
		while(this->posx < 0){
			this->posx += this->dx;
		}
		while(this->posx > 30 - this->width){
			this->posx += this->dx;
		}
	}
	
	//risetta il valore di dx
	this->dx = 0;
}
