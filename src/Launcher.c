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

void launch(){

    initscr();
    curs_set(0);

    Laser* lasers = malloc(20* sizeof *lasers);
    Star* stars = malloc(25* sizeof *stars);


    FILE *spaceship = fopen("Assets/spaceship.txt", "r");
    Spaceship *spaceship1 = createJoueur(50,40,spaceship);

    FILE *alien = fopen("Assets/ennemi1_sud.txt", "r");
    Alien *alien1 = initAlien(10,10,1, fileToCharArr(alien));
    addlist(alien1);
    addlist(alien1);
    addlist(alien1);
    addlist(alien1);

    createStar(stars);

    int sec = 0;
    int out = 0;
    while ( out == 0){
        movement(spaceship1, lasers);
        if(sec == 1500) {
            movementLaser(lasers);
            sec = 0;
        }else if (sec == 500){
            movementStar(stars);
        }
        sec++;
        collide(alien1, lasers);
        printSpaceship(spaceship1);
        printAlien(alien1);
    }

}

int main(){
    launch();
    return 0;

}