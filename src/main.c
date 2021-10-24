#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<ncurses.h>

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
    system("clear");
    char line[20];
    while(fgets(line,20,fp)){
        printf("\033[%d;%dH",y,x);
        y++;
        printf("%s",line);
    }
    printf("\n");
    rewind(fp);
}

int movement(int *x, int *y, FILE *fp){
    char key = key_pressed();
    switch (key) {
        case 'z':
            --(*y);
            break;
        case 'q':
            --(*x);
            break;
        case 's':
            ++(*y);
            break;
        case 'd':
            ++(*x);
            break;
        case 'p':
            return EXIT_FAILURE;
        case ' ':
            printf("pioupiou");
            break;
        /*default:
            return EXIT_SUCCESS;*/
    }
    printSpaceship(*x,*y,fp);
    return EXIT_SUCCESS;
}

int main(){

    int out = 0;
    int x = 6;
    int y = 50;
    FILE *spaceship = fopen("../Assets/bg1_nord.txt", "r");

    while ( out == 0){
        out = movement(&x,&y,spaceship);
    }

    fclose(spaceship);
    return 0;

}