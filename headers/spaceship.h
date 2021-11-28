#ifndef SPACE_INVADERS_SPACESHIP_H
#define SPACE_INVADERS_SPACESHIP_H

typedef struct
{
    char Direction ; /*N => Nord, S => Sud, E => EST, O => OUEST*/
    int PosX; /*Position courante coin gauche X du vaisseau*/
    int PosY; /*Position courante coin gauche Y du vaisseau*/
    int Blindage; /*Niveau de blindage en cours du vaisseau (0=>rien, 1=>blindé, 2=>ultra-blindé, etc.)*/
    int Touches; /*Nombre de fois que le vaisseau est touché par un missile*/
    char Carros_ennemi [3][16];/*Carrosserie du vaisseau ennemi, servira pour l’affichage du vaisseau ennemi à tout moment*/
    char Carrosserie [6][40]; /*Carrosserie du vaisseau du joueur, servira pour l’affichage du vaisseau du joueur à tout moment*/
    char Type; /*’M’=> mon vaisseau, ’E’=> vaisseau ennemi*/
    char Couleur[30]; /*Couleur du vaisseau*/
    int Etat; /*État du vaisseau 1=> actif, 2=> en destruction, 3 => inactif*/
    int Mise_a_jour; /*utile pour la suppression du vaisseau en tenant compte d’un certain délai*/
    struct spaceshipen * NXT; /*Pointeur vers un prochain vaisseau, servira pour la liste chaînée*/

//Vous pouvez rajouter d’autres variables si nécessaire
}spaceshipen;

typedef struct {
    int posX; //Position sur l'axe x du vaisseau allié
    int posY; //Position sur l'axe y du vaisseau allié
    int vie; //Nombre de point de vie restante
    char** Carrosserie; //Affichage du vaisseau
    char couleur[30]; //Couleur du vaisseau allié
    //int Etat;
    int Maj; // Va etre utile pour la suppression du vaisseau avec un delai
}spaceship;

typedef struct {
    int posX; //Position sur l'axe x du vaisseau ennemie
    int posY; //Position sur l'axe y du vaisseau ennemie
    int vie; //Nombre de point de vie restante ( le blindage )
    char** Carrosserie; //Affichage du vaisseau
    char couleur[30]; //Couleau du vaiseau ennemie
    //int etat;
    int maj; // Va etre utile pour la suppression du vaisseau avec un delai
    struct alien * nxt; // Un pointeur pour une liste chainée
}alien;

#endif //SPACE_INVADERS_SPACESHIP_H
