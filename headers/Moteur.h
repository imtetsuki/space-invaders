//
// Created by PHAM Hoang-Lân on 03/12/2021.
//

#ifndef SPACE_INVADERS_MOTEUR_H
#define SPACE_INVADERS_MOTEUR_H

char key_pressed();
int movement(int *x, int *y, FILE *fp, Laser lasers[]);
void movementLaser(Laser *lasers);
void createStar(Star *stars);
void movementStar(Star *stars);
void printStar(int x, int y);
void removeStar(int x,int y);

#endif //SPACE_INVADERS_MOTEUR_H
