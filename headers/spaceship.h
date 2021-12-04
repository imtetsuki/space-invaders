#ifndef SPACE_INVADERS_SPACESHIP_H
#define SPACE_INVADERS_SPACESHIP_H

#include <stdio.h>

typedef struct {
    int posX; //Position sur l'axe x du vaisseau allié
    int posY; //Position sur l'axe y du vaisseau allié
    int vie; //Nombre de point de vie restante
    char *Carrosserie; //Affichage du vaisseau
    char couleur[30]; //Couleur du vaisseau allié
    int etat; //Va etre utile pour la suppression du vaisseau avec un delai
    int Maj;
}Spaceship;

typedef struct {
    int posX; //Position sur l'axe x du vaisseau ennemie
    int posY; //Position sur l'axe y du vaisseau ennemie
    int vie; //Nombre de point de vie restante ( le blindage )
    char carroserie[20]; //Affichage du vaisseau
    char couleur[30]; //Couleau du vaiseau ennemie
    int etat; //Va etre utile pour la suppression du vaisseau avec un delai
    struct Alien *nxt;; // Un pointeur pour une liste chainée
}Alien;

typedef struct {
    int posX;
    int posY;
    int vitesse;
    char carroserie[35];
    char couleur[30];
    int maj; //maj == 1, laser existe, maj == 0 existe plus
}Laser;

typedef struct{
    int posX;
    int posY;
    int maj; //maj == 1, stars existe, maj == 0 existe plus
}Star;

#endif //SPACE_INVADERS_SPACESHIP_H
