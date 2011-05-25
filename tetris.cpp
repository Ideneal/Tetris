#include "tetris.h"

void Tetris::init(){
	//init matrix
	vector<int> riga(M_DX, 0); //riga formata da tutti 0
	for(int i=0; i<M_DY; i++)
		this->matrix.push_back(riga);
	this->pezzo = new Piece();
	this->img = NULL;
}

Tetris::Tetris(){
	this->init();
	this->points = 0;
	this->end = false;
	this->setImg("piece.bmp");
	this->attesa = 300;
	timer.start();
}

Tetris::~Tetris(){
	delete pezzo;
	SDL_FreeSurface(this->img);
}

int Tetris::getPoints() const {
	return this->points;
}

Piece * Tetris::getPiece() const {
	return this->pezzo;
}

bool Tetris::getCollision() {
	bool collision = false;
	int x,y;
	for(int i = P_DY - 1; i>=0 && !collision; i--){
		for(int j=0; j<P_DX && !collision; j++){
			if(this->pezzo->getValue(i,j) == 1){
				x = this->pezzo->getX() + j;
				y = this->pezzo->getY() + i + 1; // la posizione sottostante
				if(y > M_DY - 5)
					collision = true;
				else if(this->matrix[y][x] == 1)
					collision = true;
			}
		}
	}
	//se è avvenuta una collisione controlla che la cordinata y non è sopra il display xD
	if(collision){
		for(int i=0; i<P_DY && !this->end; i++){
			for(int j=0; j<P_DX && !this->end; j++){
				if(this->pezzo->getValue(i,j) == 1){
					y = this->pezzo->getY() + i;
					if(y < 2) this->end =true;
				}
			}
		}
	}
	
	return collision;
}

bool Tetris::getEnd() const{
	return this->end;
}

SDL_Surface * Tetris::getImg() const{
	return this->img;
}

void Tetris::setEnd(bool e){
	this->end = e;
}

void Tetris::setPoints(int p){
	this->points = p;
}

void Tetris::addPoints(){
	this->points += 50;
}

void Tetris::setImg(string name){
	SDL_Surface * oldimg = IMG_Load(name.c_str());
	//SDL_Surface * oldimg = SDL_LoadBMP(name.c_str());
	if(oldimg == NULL){
		cout << "Error to load img : " << SDL_GetError()<<endl;
		return;
	}
	this->img = SDL_DisplayFormat(oldimg);
	if(this->img == NULL){
		cout << "Errot to convert img : " << SDL_GetError() << endl;
		this->img = 0;
		return;
	}
	//Uint32 colorkey = SDL_MapRGB(this->img->format, 0xFF, 0xFF, 0xFF);
	//SDL_SetColorKey(this->img, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
     	
     	SDL_FreeSurface(oldimg);
}

void Tetris::setControll(){
	/*controllo se una delle righe è piena*/
	bool piena, finish=false;
	int riga = 0;
	for(int i=M_DY-1 ; i>=4; i--){
		piena = true;
		for(int j=0; j< M_DX && piena; j++){
			if(this->matrix[i][j] == 0)
				piena = false;
		}
		//se è piena devo sovrascrivere le righe al di sopra e incremento i
		//ovviamente se trovo una riga vuota esco dal ciclo
		if(piena){
			//cancello la riga
			for(int k=0; k<M_DX; k++)
				this->matrix[i][k] = 0;
			//sovrascrivo tutto
			for(int k= i-1 ; k >= 0; k--){
				for(int p=0; p<M_DX; p++){
					this->matrix[k+1][p] = this->matrix[k][p];
				}
			}
			//incremento i
			i++;
			this->addPoints();
		}
	}
}

void Tetris::setDirection(int dir){
	bool collision = false;
	int x,y;
	switch(dir){
		//move right
		case 1:
			for(int i = 0; i<P_DY && !collision; i++){
				for(int j=0; j<P_DX && !collision; j++){
					if(this->pezzo->getValue(i,j) == 1){
						x = this->pezzo->getX() + j +1; //la posizione a destra
						y = this->pezzo->getY() + i; 
						if(this->matrix[y][x] == 1)
							collision = true;
					}
				}
			}
			if(collision)
				this->pezzo->setDX(0);
			else
				this->pezzo->setDX(1);
			break;
		//move left
		case 2:
			for(int i = 0; i<P_DY && !collision; i++){
				for(int j=0; j<P_DX && !collision; j++){
					if(this->pezzo->getValue(i,j) == 1){
						x = this->pezzo->getX() + j -1; //la posizione a sinistra
						y = this->pezzo->getY() + i; 
						if(this->matrix[y][x] == 1)
							collision = true;
					}
				}
			}
			if(collision)
				this->pezzo->setDX(0);
			else
				this->pezzo->setDX(-1);
			break;
		//move down (aumenta velocita)
		case 3:
			if(this->attesa < 300)
				this->attesa = this->attesa * 3;
			else
				this->attesa = this->attesa / 3;
			break;
		//rotate
		case 4:
			//viene prima ruotato e se occupa un pezzo gia occupato ruota ancora
			this->pezzo->rotate();
			int x,y;
			bool ruotare = false;
			for(int i=0; i<P_DY && !ruotare; i++){
				for(int j=0; j<P_DX && !ruotare; j++){
					if(this->pezzo->getValue(i,j) == 1){
						x = this->pezzo->getX() + j;
						y = this->pezzo->getY() + i;
						if(this->matrix[ y ][ x ] == 1 || x >= M_DX)
							ruotare = true;
					}
				}
			}
			if(ruotare)
				this->pezzo->rotate();
			break;
	}
}

void Tetris::onMatrix(){
	int x,y;
	
	for(int i = 0; i<P_DY && !this->end; i++){
		for(int j=0; j<P_DX && !this->end; j++){
			if(this->pezzo->getValue(i,j) == 1){
				x = this->pezzo->getX() + j;
				y = this->pezzo->getY() + i;
				this->matrix[y][x] = 1;
			}
		}
	}
	
	delete this->pezzo;
	this->pezzo = new Piece();
}

void Tetris::play(){
	//se non è finito il gioco
	if(!this->end){
		//muovi il pezzo  e attedi
		this->pezzo->move();
		if(timer.getTicks() > this->attesa){//SDL_Delay(200);
			this->pezzo->setDY(1);
			//se è avvenuta una collisione stampa il pezzo su matrix e creane uno nuovo
			if(this->getCollision())
				this->onMatrix();
			//effettua i controlli
			this->setControll();
			//resetta il timer
			timer.stop();
			timer.start();
		}else{
			this->pezzo->setDY(0);
		}
	}
}

void Tetris::draw(SDL_Surface * screen){
	SDL_Rect * rect = new SDL_Rect();
	//disegno della mappa
	for(int i = 4 ; i < M_DY; i++){
		for(int j=0 ; j < M_DX; j++){
			if(this->matrix[i][j] == 1){
				rect->x = j * 16;
				rect->y = i * 16;
				SDL_BlitSurface(this->img, NULL, screen, rect);
			}
		}
	}
	//disegno del pezzo
	for(int i=0 ; i<P_DY; i++){
		for(int j=0 ; j<P_DX; j++){
			if(this->pezzo->getValue(i,j) == 1){
				rect->x = (this->pezzo->getX() + j) * 16;
				rect->y = (this->pezzo->getY() + i) * 16;
				SDL_BlitSurface(this->img, NULL, screen, rect);
			}
		}
	}
	
	delete rect;
	SDL_Flip(this->img);
}
