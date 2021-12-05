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

int launch() {
    initscr(); //Utilisation de ncurses
    curs_set(0); //set le curseur au debut
    printf("\033[%d;%dH", 0, 0); //reset au cas ou si ca ne marche pas

    //allocation de memoire pour laser et stars
    Laser *lasers = malloc(20 * sizeof *lasers);
    Star *stars = malloc(25 * sizeof *stars);

    //ouverture de fichier pour ajout dans la carrosserie
    FILE *spaceship = fopen("Assets/spaceship.txt", "r");
    Spaceship *spaceship1 = createJoueur(50, 40, spaceship);

    FILE *alien = fopen("Assets/ennemi1_sud.txt", "r");
    Alien *alien1 = initAlien(10, 10, 1, fileToCharArr(alien));

    //pour creer 20 alien lambda
    for (int i = 0; i < 20; i++) {
        addlist(alien1);
    }

    //creation des etoiles et faire le mouvement
    createStar(stars);
    movementStar(stars);

    //variable utile pour gerer la vitesse mouvement et le statut du jeu
    int sec = 0;
    int out = 0;
    int alienDecalage = 0;
    int alienMove = 1;
    int statu = 2;

    //boucle "infini" pour jouer au jeu
    while (out == 0 && statu == 2) {
        out = movement(spaceship1, lasers);
        collide(alien1, lasers);
        printAlien(alien1);
        printSpaceship(spaceship1);
        if (sec == 1000) {
            movementLaser(lasers);
            if (alienDecalage == 6 || alienDecalage == -6) {
                alienMove = -alienMove;
                mouvementAlien(alien1, 0, 2);
                alienDecalage += alienMove;
            } else {
                alienDecalage += alienMove;
                mouvementAlien(alien1, alienMove, 0);
            }
            sec = 0;
        } else if (sec == 500) {
            movementStar(stars);
        }
        statu = status(alien1,spaceship1);
        sec++;
    }

    return statu;

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
            system("clear");
            printf("Vous avez quitter le jeu bye bye!");
            printf("\033[%d;%dH", 0, 1);
            return 0;
        }
    }
    int x = launch();
    if(x==1){
        system("clear");
        printf("\033[%d;%dH", 0, 0);
        printf("Vous avez gagner, le jeu va etre quitter bye!");
        printf("\033[%d;%dH", 0, 0);
    }else{
        system("clear");
        printf("\033[%d;%dH", 0, 0);
        printf("Vous avez perdu, le jeu va etre quitter bye!");
        printf("\033[%d;%dH", 0, 0);
    }

    system("clear");
    printf("\033[%d;%dH", 0, 0);
    printf("Le jeu est quitter bye bye!");
    printf("\033[%d;%dH", 0, 1);
    return 0;

}