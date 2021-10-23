#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include <stdlib.h>

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

int main(){

    FILE *pToFile = fopen("../Assets/bg1_nord.txt", "r");
    int line = 0;
    char input[512];
    char output[512];
    int x = -15;
    int y = -14;
    /*printf("\033[%d;%dH",x,y);
    printf("TESTdazdazda");
    printf("\033[%d;%dH",--x,y);
    printf("MOMOMOMOMOMO\n");
    system("clear");
    while ( fgets(input,512,pToFile)){
        printf("\033[%d;%dH",x,y);
        y--;
        printf("%s",input);
    }*/
    printf("%s",input);
    while ( fgets(input,512,pToFile)) {
        printf("%s",output);
        strcat(output,input);
    }
    printf("%s",input);
    while(line==0){
        if(key_pressed() == 'z'){
            ++x;
            printf("\033[%d;%dH", x, y);
            printf("tagrandmere");
            line++;
        }
    }
   /*while(line==0){
        if(key_pressed() =='z'){
            while ( fgets(input,512,pToFile)) {
                ++x;
                printf("\033[%d;%dH", x, y);
                printf("%s", input);
            }
        }
        if(key_pressed() =='q'){
            ++y;
            while ( fgets(input,512,pToFile)) {
                printf("\033[%d;%dH", x, y);
                printf("%s", input);
            }
        }
        if(key_pressed() =='s'){
            --y;
            while ( fgets(input,512,pToFile)) {
                printf("\033[%d;%dH", x, y);;
                printf("%s", input);
            }
        }
        if(key_pressed() =='d'){
            while ( fgets(input,512,pToFile)) {
                --x;
                printf("\033[%d;%dH", x, y);
                printf("%s", input);
            }
        }
        if(key_pressed() =='p'){
            line++;
        }
    }*/
    fclose(pToFile);
    return 0;
}