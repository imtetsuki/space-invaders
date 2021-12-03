#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>

#include "../headers/spaceship.h"
#include "../headers/Moteur.h"
#include "../headers/Ennemie.h"
#include "../headers/Joueur.h"
#include "../headers/Reglage.h"
#include "../headers/Launcher.h"

int main(){
    initscr();
    curs_set(0);
    int out = 0;
    int x = 50;
    int y = 40;

    Laser* lasers = malloc(200* sizeof *lasers);
    Star* stars = malloc(200* sizeof *stars);

    FILE *spaceship = fopen("Assets/spaceship.txt", "r");
    FILE *alien = fopen("Assets/ennemi1_sud.txt", "r");
    createStar(stars);

    int sec = 0;
    while ( out == 0){
        out = movement(&x,&y,spaceship, lasers);
        if(sec == 1500) {
            movementLaser(lasers);
            sec = 0;
        }else if (sec == 500){
            movementStar(stars);
        }
        sec++;
        printSpaceship(50,10,alien);
        //createEnnemie(aliens,alien);
        //sleep(1);
    }

    fclose(spaceship);
    fclose(alien);
    return 0;

}