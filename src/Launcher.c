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

void launch() {
    initscr();
    curs_set(0);
    printf("\033[%d;%dH", 0, 0);


    Laser *lasers = malloc(20 * sizeof *lasers);
    Star *stars = malloc(25 * sizeof *stars);


    FILE *spaceship = fopen("Assets/spaceship.txt", "r");
    Spaceship *spaceship1 = createJoueur(50, 40, spaceship);

    FILE *alien = fopen("Assets/ennemi1_sud.txt", "r");
    Alien *alien1 = initAlien(10, 10, 1, fileToCharArr(alien));

    for(int i = 0; i<20;i++){
        addlist(alien1);
    }





    createStar(stars);
    movementStar(stars);

    int sec = 0;
    int out = 0;
    int alienDecalage = 0;
    int alienMove = 1;

    while (out == 0) {
        movement(spaceship1, lasers);
        collide(alien1, lasers);
        printAlien(alien1);
        printSpaceship(spaceship1);
        if (sec == 1000) {
            movementLaser(lasers);
            if (alienDecalage == 6 ||alienDecalage == -6) {
                alienMove = -alienMove;
                mouvementAlien(alien1, 0, 2);
                alienDecalage += alienMove;
            }else {
                alienDecalage += alienMove;
                mouvementAlien(alien1, alienMove, 0);
            }
            sec = 0;
        } else if (sec == 500) {
            movementStar(stars);
        }
        sec++;
    }

}

int main() {
    selectMenu(0);
    int i = 0;
    while (i != 2) {
        i = choiceMenu();
        if (1 == i) {
            selectMenu(i);
        } else if (4 == i) {
            selectMenu(i);
        }
        if (i == 3) {
            return 0;
        }
    }
    launch();
    return 0;

}