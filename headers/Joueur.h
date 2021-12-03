//
// Created by PHAM Hoang-Lân on 03/12/2021.
//

#ifndef SPACE_INVADERS_JOUEUR_H
#define SPACE_INVADERS_JOUEUR_H

void printSpaceship(int x, int y, FILE *fp);
void removeSpaceship(int x, int y, FILE *fp);
void removeLaser(int x,int y);
void printLaser(int x, int y);
void createLaser(int x, int y, Laser *lasers);

#endif //SPACE_INVADERS_JOUEUR_H

