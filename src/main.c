#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>
#include "../headers/spaceship.h"


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

void createLaser(int x, int y, Laser lasers[]){
    for(int i = 0; i < 400; i++){
        if(lasers[i].maj == 0){
            //lasers[i] = {x+3, --y, 1, 't', 1};
            lasers[i].posX = x+3;
            lasers[i].posY = --y;
            lasers[i].vitesse = 1;
            lasers[i].maj = 1;
            printLaser(lasers[i].posX, lasers[i].posY);
            break;
        }
    }
}

void movementLaser(Laser lasers[]){
    for(int i = 0; i<400; i++){
        if(lasers[i].maj == 1){
            if(lasers[i].posY == -1){
                removeLaser(lasers[i].posX, lasers[i].posY );
                lasers[i].maj = 0;
            }else{
                removeLaser(lasers[i].posX, lasers[i].posY );
                lasers[i].posY = lasers[i].posY - lasers[i].vitesse;
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

int main(){
    initscr();
    curs_set(0);
    int out = 0;
    int x = 6;
    int y = 50;


    int numlaser = 300;
    Laser* lasers = malloc(numlaser * sizeof *lasers);
    for(int i = 0; i<300; i++){
        lasers[i].maj = 0;
    }

    FILE *spaceship = fopen("Assets/bg1_nord.txt", "r");
    FILE *alien = fopen("Assets/ennemi1_sud.txt", "r");
    int sec = 0;
    while ( out == 0){
        out = movement(&x,&y,spaceship, lasers);
        if(sec == 2500) {
            movementLaser(lasers);
            sec = 0;
        }
        sec++;
        printSpaceship(6,20,alien);
        //sleep(1);
    }



    fclose(spaceship);
    fclose(alien);
    return 0;

}