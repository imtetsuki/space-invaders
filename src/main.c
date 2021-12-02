#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>
#include "../headers/spaceship.h"


void printEnnemie(Alien *alien);

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

void printSpaceship(int x, int y, FILE *fp){
    //system("clear");
    char line[20];
    while(fgets(line,20,fp)){
        printf("\033[%d;%dH",y,x);
        y++;
        printf("%s",line);
    }
    printf("\n");
    rewind(fp);
}

void removeSpaceship(int x, int y, FILE *fp){
    char line[20];
    while(fgets(line,20,fp)){
        printf("\033[%d;%dH",y,x);
        y++;
        printf("%s","             ");
    }
    printf("\n");
    rewind(fp);
}

void removeLaser(int x,int y){
    printf("\033[%d;%dH",y,x);
    printf("%s","  ");
    printf("\n");
}

void printLaser(int x, int y){
    printf("\033[%d;%dH",y,x);
    printf("|");
    printf("\n");
}

void createLaser(int x, int y, Laser *lasers){
    int size = (int) sizeof(lasers);
    for(int i = 0; i < size; i++){
        if(lasers[i].maj == 0){
            //lasers[i] = {x+3, --y, 1, 't', 1};
            lasers[i].posX = x+3;
            lasers[i].posY = --y;
            //lasers[i].vitesse = 1;
            lasers[i].maj = 1;
            printLaser(lasers[i].posX, lasers[i].posY);
            break;
        }
    }
}

void movementLaser(Laser *lasers){
    int size = (int) sizeof(lasers);
    for(int i = 0; i<size; i++){
        if(lasers[i].maj == 1){
            if(lasers[i].posY == -2){
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

int movement(int *x, int *y, FILE *fp, Laser lasers[]){
    char key = key_pressed();
    switch (key) {
        /*case 'z':
            removeSpaceship(*x,*y,fp);
            --(*y);
            break;*/
        case 'q':
            removeSpaceship(*x,*y,fp);
            //movementLaser(lasers);
            --(*x);
            break;
        /*case 's':
            removeSpaceship(*x,*y,fp);
            ++(*y);
            break;*/
        case 'd':
            removeSpaceship(*x,*y,fp);
            //movementLaser(lasers);
            ++(*x);
            break;
        case 'p':
            return EXIT_FAILURE;
        case ' ':
            createLaser(*x, *y, lasers);
            break;
        /*default:
            return EXIT_SUCCESS;*/
    }

    printSpaceship(*x,*y,fp);
    return EXIT_SUCCESS;
}

void collide(Laser lasers[]){

}

void createEnnemie(Alien *alien, FILE *fp){
    int size = (int) sizeof(alien);
    for(int i = 0; i < size; i++){
        if(alien[0].etat == 0){
            //lasers[i] = {x+3, --y, 1, 't', 1};
            alien[0].posX = 1;
            alien[0].posY = -10;
            //lasers[i].vitesse = 1;
            alien[0].vie = 3;
            alien[0].etat = 1;
            alien[0].alien = fp;
            printEnnemie(alien);
        }else{
            alien[i].posX = alien[i-1].posX+7;
            alien[i].posY = alien[i-1].posY+8;
            alien[i].vie = 3;
            alien[i].etat = 1;
            alien[i].alien = fp;
            alien[i-1].nxt = (struct Alien *) malloc(sizeof(alien[i]));
            printEnnemie(alien);
        }
    }
}

void printEnnemie(Alien *alien) {
    int size = (int) sizeof(alien);
    for(int i = 0; i < size; i++){
        if(alien[i].etat == 0){
            char line[20];
            while(fgets(line,20,alien[i].alien)){
                int y = alien[i].posY;
                int x = alien[i].posX;
                printf("\033[%d;%dH",y,x);
                y++;
                printf("%s",line);
            }
            printf("\n");
            rewind(alien[i].alien);
        }
    }
}


int main(){
    initscr();
    curs_set(0);
    int out = 0;
    int x = 6;
    int y = 50;

    Laser* lasers = malloc(1* sizeof *lasers);
    Alien* aliens = malloc(20* sizeof *aliens);
    //Spaceship* spaceship = malloc(1* sizeof *spaceship);

    FILE *spaceship = fopen("Assets/bg1_nord.txt", "r");
    FILE *alien = fopen("../Assets/ennemi1_sud.txt", "r");

    int sec = 0;
    while ( out == 0){
        out = movement(&x,&y,spaceship, lasers);
        if(sec == 2500) {
            movementLaser(lasers);
            sec = 0;
        }
        sec++;
        createEnnemie(aliens,alien);
        //sleep(1);
    }

    fclose(spaceship);
    fclose(alien);
    return 0;

}