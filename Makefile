CC = gcc

LD = gcc

CFLAGS = -g -Wall -Werror
LDFLAGS = 
RM = rm -f
LDLIBS =s

#Les .o faut les lister ici
OBJS = main.o spaceship.o

#le nom de ton executable
PROG = Space_Invaders

all: $(PROG)

#le gcc final faut rajouter les flag de compil ici genre -lm pour le math.h
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG) -lncurses
	make clean

#tu mets le .c + les fichier .h inclu dedans
main.o: src/main.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/main.c

spaceship.o: src/spaceship.c #headers/spaceship.h
	$(CC) $(CFLAGS) -c src/spaceship.c

clean:
	$(RM) $(OBJS)