//
// Created by PHAM Hoang-Lân on 03/12/2021.
//

#ifndef SPACE_INVADERS_ENNEMIE_H
#define SPACE_INVADERS_ENNEMIE_H

struct Alien* initAlien(int posX, int posY, int vie, char* carrosserie);
void addlist(struct Alien* head);
void addlistALien(struct Alien* head,struct Alien* next);


#endif //SPACE_INVADERS_ENNEMIE_H
