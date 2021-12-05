CC = gcc

LD = gcc

CFLAGS = -g -Wall -Werror
LDFLAGS = 
RM = rm -f
LDLIBS =s

OBJS =  Moteur.o Joueur.o Ennemie.o  launcher.o Reglage.o

PROG = Space_Invaders

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG) -lncurses
	make clean


Moteur.o: src/Game/Moteur.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Moteur.c

Reglage.o: src/Menu/Reglage.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Menu/Reglage.c

launcher.o: src/launcher.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/launcher.c

Joueur.o: src/Game/Joueur.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Joueur.c

Ennemie.o: src/Game/Ennemie.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Ennemie.c

clean:
	$(RM) $(OBJS)