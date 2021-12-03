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

void printSpaceship(int x, int y, FILE *fp){
    //system("clear");
    char line[20];
    while(fgets(line,20,fp)){
        printf("\033[%d;%dH",y,x);
        y++;
        printf("%s",line);
    }
    printf("\n");
    rewind(fp);
}

void removeSpaceship(int x, int y, FILE *fp){
    char line[20];
    while(fgets(line,20,fp)){
        printf("\033[%d;%dH",y,x);
        y++;
        printf("%s","             ");
    }
    printf("\n");
    rewind(fp);
}

void removeLaser(int x,int y){
    printf("\033[%d;%dH",y,x);
    printf("%s","  ");
    printf("\n");
}

void printLaser(int x, int y){
    printf("\033[%d;%dH",y,x);
    printf("|");
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

