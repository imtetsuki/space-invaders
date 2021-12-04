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

    spaceship -> Maj = 1;
    spaceship -> posX = x;
    spaceship -> posY = y;
    spaceship -> vie = 10;
    spaceship -> Carrosserie = fileToCharArr(fp);

    return spaceship;

}

char* fileToCharArr(FILE *fp){
    long lSize;
    char *buffer;

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);



    fclose(fp);
    return buffer;
}

void printSpaceship(Spaceship* ship){
    //system("clear");
    printf("\033[%d;%dH",ship->posY,ship->posX);
    printf("%s",ship->Carrosserie);

}

void removeSpaceship(Spaceship* ship){
    printf("\033[%d;%dH",ship->posY,ship->posX);
    printf("%s","             ");
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
            lasers[i].posX = x+3;
            lasers[i].posY = --y;
            //lasers[i].vitesse = 1;
            lasers[i].maj = 1;
            printLaser(lasers[i].posX, lasers[i].posY);
            break;
        }
    }
}

