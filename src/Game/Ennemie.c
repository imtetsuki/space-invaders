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

struct Alien* initAlien(int posX, int posY, int vie, char* carrosserie){
    struct Alien* alien= malloc(sizeof(Alien));
    alien -> posX = posX;
    alien -> posY = posY;
    alien -> vie = vie;
    alien -> etat = 1;
    alien -> carroserie = carrosserie;
    alien -> nxt = NULL;

    return alien;
}

void addlist(struct Alien* head){
    struct Alien* courant = head;
    while(courant->nxt != NULL){
        courant = (Alien *) courant->nxt;
    }
    struct Alien* init = initAlien(head->posX+10, head->posY,head->vie, head->carroserie);
    courant -> nxt = init;
}

void addlistALien(struct Alien* head,struct Alien* next){
    struct Alien* courant = head;
    while(courant->nxt != NULL){
        courant = (Alien *) courant->nxt;
    }
    courant->nxt = next;
}
