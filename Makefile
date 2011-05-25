CC = g++
LIBRERIE = -lSDL -lSDL_image -lSDL_ttf

ifeq ($(NAME), )
	NAME = tetris
endif

compile: $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@

$(NAME): piece.o timer.o tetris.o main.o
	@echo "inizio compilazione..."
	$(CC) -o $@ $^ $(LIBRERIE)

clear: piece.o timer.o tetris.o main.o
	rm $^
