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

char key_pressed()
{
    struct termios oldterm, newterm;
    int oldfd; char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) {ungetc(c, stdin); result = getchar();}
    return result;
}

int movement(Spaceship *ship, Laser lasers[]){
    char key = key_pressed();
    switch (key) {
        /*case 'z':
            removeSpaceship(*x,*y,fp);
            --(*y);
            break;*/
        case 'q':
            removeSpaceship(ship);
            //movementLaser(lasers);
            --(ship->posX);
            break;
            /*case 's':
                removeSpaceship(*x,*y,fp);
                ++(*y);
                break;*/
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
    }

    printSpaceship(ship);
    return EXIT_SUCCESS;
}


void movementLaser(Laser *lasers){
    for(int i = 0; i<25; i++){
        if(lasers[i].maj == 1){
            if(lasers[i].posY == 0){
                removeLaser(lasers[i].posX, lasers[i].posY );
                lasers[i].maj = 0;
            }else{
                removeLaser(lasers[i].posX, lasers[i].posY );
                lasers[i].posY = lasers[i].posY - 1;
                printLaser(lasers[i].posX,lasers[i].posY);
            }
        }
    }
}

void createStar(Star *stars){
    for(int i = 0; i < 25; i++){
        if(stars[i].maj == 0){
            stars[i].posX = rand()%(50-2+1);
            stars[i].posY = rand()%(50-1);
            stars[i].maj = 1;
            printStar(stars[i].posX, stars[i].posY);
        }
    }
}

void movementStar(Star *stars){
    for(int i = 0; i<25; i++){
        if(stars[i].maj == 1){
            if(stars[i].posX == 120){
                removeStar(stars[i].posX, stars[i].posY );
                stars[i].maj = 0;
                createStar(stars);
            }else{
                removeStar(stars[i].posX, stars[i].posY );
                stars[i].posX = stars[i].posX + 1;
                printStar(stars[i].posX,stars[i].posY);
            }
        }
    }
}

void printStar(int x, int y){
    printf("\033[%d;%dH",y,x);
    printf("*");
    printf("\n");
}

void removeStar(int x,int y){
    printf("\033[%d;%dH",y,x);
    printf("%s","  ");
    printf("\n");
}

void printVoid(){
    for (int i = 0; i < 75; ++i) {
        printf("                                                                                                                                                          ");
    }
}
