#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>

#include "../../headers/spaceship.h"
#include "../../headers/Moteur.h"
#include "../../headers/Ennemie.h"
#include "../../headers/Joueur.h"
#include "../../headers/Reglage.h"
#include "../../headers/Launcher.h"

Spaceship *createJoueur(int x, int y, FILE *fp) { //Initialiser et allouer de l'espace pour un joueur
    Spaceship *spaceship;

    spaceship = (Spaceship *) malloc(sizeof(Spaceship));
    spaceship->posX = x;
    spaceship->posY = y;
    spaceship->vie = 10;
    spaceship->etat = 1;
    spaceship->carrosserie = fileToCharArr(fp);

    return spaceship;
}

char *fileToCharArr(FILE *fp) { //Ajout d'un file dans tableau dynamique de char
    char *buffer = NULL;
    size_t size = 0;

/* Avoir la taille du buffer */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

/* Mettre le pointeur au debut */
    rewind(fp);

/* Allocation de memoire */
    buffer = (char *) malloc((size + 1) * sizeof(*buffer)); /* size + 1 byte for the \0 */

/* Lire le fichier ligne par ligne et rajout dans le buffer */
    fread(buffer, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* Si c'est la fin ca fini le buffer*/
    buffer[size] = '\0';

    fclose(fp);

    return buffer;
}

void printSpaceship(Spaceship *ship) { //Affichage du vaisseau alliee
    //system("clear");
    //printf("\033[%d;%dH",ship->posY,ship->posX);
    //printf("%s",ship->Carrosserie);
    int y = ship->posY;
    printf("\033[%d;%dH", y, ship->posX);
    for (int i = 0; i < strlen(ship->carrosserie); i++) {
        if (ship->carrosserie[i] == '\n') {
            printf("\033[%d;%dH", y, ship->posX);
            y++;
        }
        printf("%c", ship->carrosserie[i]);
    }

}

void removeSpaceship(Spaceship *ship) { //Enlever l'affichage du vaisseau alliee en printant par dessus des espaces vides
    int y = ship->posY;
    printf("\033[%d;%dH", y, ship->posX);
    for (int i = 0; i < 11; i++) {
        printf("\033[%d;%dH", y, ship->posX);
        y++;
        printf("%s", "                       ");
    }
}

void removeLaser(int x, int y) { //Enlever l'affichage du laser en printant par dessus des espaces vides
    printf("\033[%d;%dH", y, x);
    printf("%s", "  ");
    printf("\n");
}

void printLaser(int x, int y) { //Affichage du laser
    printf("\033[%d;%dH", y, x);
    printf("||");
    printf("\n");
}

void createLaser(int x, int y, Laser *lasers) { //Pour creer un laser a chaque appuie avec un break pour creer que un laser par appuie
    for (int i = 0; i < 20; i++) {
        if (lasers[i].maj == 0) {
            //lasers[i] = {x+3, --y, 1, 't', 1};
            lasers[i].posX = x + 6;
            lasers[i].posY = --y;
            //lasers[i].vitesse = 1;
            lasers[i].maj = 1;
            printLaser(lasers[i].posX, lasers[i].posY);
            break;
        }
    }
}

