#ifndef SPACE_INVADERS_ENNEMIE_H
#define SPACE_INVADERS_ENNEMIE_H

struct Alien* initAlien(int posX, int posY, int vie, char* carrosserie);
void addlist(struct Alien* head);
void addlistALien(struct Alien* head,struct Alien* next);
void printAlien(Alien* head);
void retire(struct Alien* head, struct Alien* retire);
void removeAlien(struct Alien* courant);
void mouvementAlien(struct Alien *head, int x, int y);

#endif //SPACE_INVADERS_ENNEMIE_H
