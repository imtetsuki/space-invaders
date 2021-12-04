//
// Created by PHAM Hoang-Lân on 03/12/2021.
//

#ifndef SPACE_INVADERS_JOUEUR_H
#define SPACE_INVADERS_JOUEUR_H

Spaceship* createJoueur(int x, int y, FILE *fp);
char* fileToCharArr(FILE *fp);
void printSpaceship(Spaceship* ship);
void removeSpaceship(Spaceship* ship);
void removeLaser(int x,int y);
void printLaser(int x, int y);
void createLaser(int x, int y, Laser *lasers);

#endif //SPACE_INVADERS_JOUEUR_H

