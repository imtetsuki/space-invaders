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

char key_pressed() { //Pour recuperer l'entree des touches de l'utilisateur
    struct termios oldterm, newterm;
    int oldfd;
    char c, result = 0;
    tcgetattr(STDIN_FILENO, &oldterm);
    newterm = oldterm;
    newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
    fcntl(STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) {
        ungetc(c, stdin);
        result = getchar();
    }
    return result;
}

int movement(Spaceship *ship, Laser lasers[]) { //Faire bouger le vaisseau allie et effectuer des tirs
    char key = key_pressed();
    switch (key) {
        case 'q':
            removeSpaceship(ship);
            //movementLaser(lasers);
            --(ship->posX);
            break;
        case 'd':
            removeSpaceship(ship);
            //movementLaser(lasers);
            ++(ship->posX);
            break;
        case 'p':
            return EXIT_FAILURE;
        case ' ':
            createLaser(ship->posX, ship->posY, lasers);
            break;
            /*default:
                return EXIT_SUCCESS;*/
        case 'l':
            return 1;
    }

    printSpaceship(ship);
    return EXIT_SUCCESS;
}


void movementLaser(Laser *lasers) { //Actualisation des lasers a chaque instant x
    for (int i = 0; i < 20; i++) {
        if (lasers[i].maj == 1) {
            if (lasers[i].posY == 0) {
                removeLaser(lasers[i].posX, lasers[i].posY);
                lasers[i].maj = 0;
            } else {
                removeLaser(lasers[i].posX, lasers[i].posY);
                lasers[i].posY = lasers[i].posY - 1;
                printLaser(lasers[i].posX, lasers[i].posY);
            }
        }
    }
}

void createStar(Star *stars) { //Initialisation des etoiles a des coordoones aleatoire entre un min et max pour x et y
    for (int i = 0; i < 25; i++) {
        if (stars[i].maj == 0) {
            stars[i].posX = rand() % (100 - 2 + 1);
            stars[i].posY = rand() % (50 - 1);
            stars[i].maj = 1;
            printStar(stars[i].posX, stars[i].posY);
        }
    }
}

void movementStar(Star *stars) { //Actualisation des etoiles pour les faires bouger de gauche a droite mais on aurait pu les faire bouger de haut en bas
    for (int i = 0; i < 25; i++) {
        if (stars[i].maj == 1) {
            if (stars[i].posX == 120) {
                removeStar(stars[i].posX, stars[i].posY);
                stars[i].maj = 0;
                createStar(stars);
            } else {
                removeStar(stars[i].posX, stars[i].posY);
                stars[i].posX = stars[i].posX + 1;
                printStar(stars[i].posX, stars[i].posY);
            }
        }
    }
}

void printStar(int x, int y) { //Affichage des etoiles sur le terminal
    printf("\033[%d;%dH", y, x);
    printf("*");
    printf("\n");
}

void removeStar(int x, int y) { //Retirer l'afficahge des etoiles sur le terminal
    printf("\033[%d;%dH", y, x);
    printf("%s", "  ");
    printf("\n");
}

int count(struct Alien *head) { //Pour compter la taille de la linkedlist
    int i = 0;
    while (head != NULL) {
        i++;
        head = head->nxt;
    }
    return i;
}

void collide(struct Alien *head, Laser *lasers) { // fonction pour la collision des lasers sur l'ennemie on regarde la ligne horizontal de devant l'ennemie mais on aurait pu faire une hitbox carree entre du coup 4 conditions
    // et des intervalles x et y pour faire en sorte que ca soit un carre
    struct Alien *courant = head;
    for (int i = 0; i < 25; i++) {
        if (lasers[i].maj == 1) {
            while (courant != NULL) {
                if (lasers[i].posY == courant->posY + 2 && lasers[i].posX > courant->posX &&
                    lasers[i].posX < courant->posX + 8) {
                    courant->vie--;
                    lasers[i].maj = 0;
                    //printf("HITHITHITIHTHITHIHTIHI");
                    if (courant->vie <= 0) {
                        removeAlien(courant);
                        retire(head, courant);
                    }
                    break;
                }
                courant = courant->nxt;
            }
        }

    }
}

int status(struct Alien *head,struct Spaceship *spaceship){ //Verification de l'etat du jeu 1 pour gagner 2 pour continuer le jeu 0 pour lose

    struct Alien * courant = head;

    if (courant == NULL){
        return 1;
    }

    while (courant->nxt != NULL){
        courant = courant->nxt;
    }

    if(courant->posY >= spaceship->posY){
        return 0;
    }

    return 2;

}