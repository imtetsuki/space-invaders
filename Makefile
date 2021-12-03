CC = gcc

LD = gcc

CFLAGS = -g -Wall -Werror
LDFLAGS = 
RM = rm -f
LDLIBS =s

#Les .o faut les lister ici
OBJS =  Moteur.o Joueur.o Ennemie.o  launcher.o

#le nom de ton executable
PROG = Space_Invaders

all: $(PROG)

#le gcc final faut rajouter les flag de compil ici genre -lm pour le math.h
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG) -lncurses
	make clean

#tu mets le .c + les fichier .h inclu dedans

Moteur.o: src/Game/Moteur.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Moteur.c

launcher.o: src/launcher.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/launcher.c

Joueur.o: src/Game/Joueur.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Joueur.c

Ennemie.o: src/Game/Ennemie.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/Game/Ennemie.c

clean:
	$(RM) $(OBJS)