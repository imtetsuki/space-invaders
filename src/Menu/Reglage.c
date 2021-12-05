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

void printFile(FILE *fp) { //pour print directement le fichier
    char *buffer = NULL;
    size_t size = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    buffer = (char *) malloc((size + 1) * sizeof(*buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    printf("\033[34m %s", buffer);
    fclose(fp);
}

void selectMenu(int i) {// afficher 1e menu ou la page help
    curs_set(0);
    printf("\033[%d;%dH", 0, 0);
    clear();
    if (i == 0 || i == 4) {
        FILE *menu = fopen("Assets/menu.txt", "r");
        printFile(menu);
    } else if (i == 1) {
        FILE *help = fopen("Assets/help.txt", "r");
        printFile(help);
    }
}

int choiceMenu() { //Faire le choix d'affichage au debut
    char key = key_pressed();
    switch (key) {
        case 'p':
            return 2;
        case 'h':
            return 1;
        case 'q':
            return 3;
        case 'm':
            return 4;
    }

    return EXIT_SUCCESS;
}
