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

Spaceship* createJoueur(int x, int y, FILE *fp){
    Spaceship *spaceship;

    spaceship = (Spaceship*)malloc(sizeof(Spaceship));
    spaceship -> posX = x;
    spaceship -> posY = y;
    spaceship -> vie = 10;
    spaceship -> etat = 1;
    spaceship -> carrosserie = fileToCharArr(fp);

    return spaceship;
}

char* fileToCharArr(FILE *fp){
    char *buffer = NULL;
    size_t size = 0;

/* Get the buffer size */
    fseek(fp, 0, SEEK_END); /* Go to end of file */
    size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
    rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
    buffer = malloc((size + 1) * sizeof(*buffer)); /* size + 1 byte for the \0 */

/* Read the file into the buffer */
    fread(buffer, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
    buffer[size] = '\0';

/* Print it ! */
    return buffer;
}

void printSpaceship(Spaceship* ship){
    //system("clear");
    //printf("\033[%d;%dH",ship->posY,ship->posX);
    //printf("%s",ship->Carrosserie);
    int y = ship->posY;
    printf("\033[%d;%dH",y,ship->posX);
    for(int i = 0; i< strlen(ship->carrosserie);i++){
        if(ship->carrosserie[i] == '\n'){
            printf("\033[%d;%dH",y,ship->posX);
            y++;
        }
            printf("%c", ship->carrosserie[i]);
    }

}

void removeSpaceship(Spaceship* ship){
    int y = ship->posY;
    printf("\033[%d;%dH",y,ship->posX);
    for(int i = 0; i< 11;i++){
        printf("\033[%d;%dH",y,ship->posX);
        y++;
        printf("%s", "                       ");
    }
}

void removeLaser(int x,int y){
    printf("\033[%d;%dH",y,x);
    printf("%s","  ");
    printf("\n");
}

void printLaser(int x, int y){
    printf("\033[%d;%dH",y,x);
    printf("||");
    printf("\n");
}

void createLaser(int x, int y, Laser *lasers){
    for(int i = 0; i < 25; i++){
        if(lasers[i].maj == 0){
            //lasers[i] = {x+3, --y, 1, 't', 1};
            lasers[i].posX = x+6;
            lasers[i].posY = --y;
            //lasers[i].vitesse = 1;
            lasers[i].maj = 1;
            printLaser(lasers[i].posX, lasers[i].posY);
            break;
        }
    }
}

