#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>
#include<assert.h>

#include "../../headers/spaceship.h"
#include "../../headers/Moteur.h"
#include "../../headers/Ennemie.h"
#include "../../headers/Joueur.h"
#include "../../headers/Reglage.h"
#include "../../headers/Launcher.h"

struct Alien *initAlien(int posX, int posY, int vie, char *carrosserie) {
    struct Alien *alien = malloc(sizeof(Alien));
    alien->posX = posX;
    alien->posY = posY;
    alien->vie = vie;
    alien->etat = 1;
    alien->carroserie = carrosserie;
    alien->nxt = NULL;

    return alien;
}

void addlist(struct Alien *head) {
    struct Alien *courant = head;
    int cpt = 0;
    int ligne = 0;
    while (courant->nxt != NULL) {
        courant = courant->nxt;
        cpt++;
        if (cpt == 8 - 2 * ligne) {
            ligne++;
            cpt = 0;
        }
    }

    if (cpt == 0) {
        struct Alien *init = initAlien(head->posX + 10 * ligne, head->posY + 5 * ligne, courant->vie,
                                       courant->carroserie);
        courant->nxt = init;
    } else {
        struct Alien *init = initAlien(courant->posX + 10, courant->posY, courant->vie, courant->carroserie);
        courant->nxt = init;
    }

}

void addlistALien(struct Alien *head, struct Alien *next) {
    struct Alien *courant = head;
    while (courant->nxt != NULL) {
        courant = (Alien *) courant->nxt;
    }
    courant->nxt = next;
}

void printAlien(struct Alien *head) {
    struct Alien *courant = head;
    int y;
    while (courant != NULL) {
        y = courant->posY;
        if (courant->vie > 0) {
            printf("\033[%d;%dH", y, courant->posX);
            for (int i = 0; i < strlen(courant->carroserie); i++) {
                if (courant->carroserie[i] == '\n') {
                    printf("\033[%d;%dH", y, courant->posX);
                    y++;
                }
                printf("%c", courant->carroserie[i]);
            }
        }
        courant = courant->nxt;
    }

}

void retire(struct Alien *head, struct Alien *retire) {
    struct Alien *courant = head;
    while (courant != NULL && courant->nxt != retire) {
        courant = courant->nxt;
    }
    if (courant != NULL) {
        struct Alien *tmp = courant->nxt;
        courant->nxt = courant->nxt->nxt;
        free(tmp);
    }
}

void removeAlien(struct Alien *courant) {
    int y = courant->posY;
    printf("\033[%d;%dH", y, courant->posX);
    for (int i = 0; i < 3; i++) {
        printf("\033[%d;%dH", y, courant->posX);
        y++;
        printf("%s", "        ");
    }
}


void mouvementAlien(struct Alien *head, int x, int y) {
    struct Alien *courant = head;

    while (courant != NULL) {
        removeAlien(courant);
        courant->posY += y;
        courant->posX += x;
        courant = courant->nxt;
        printAlien(courant);
    }


}