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

void printFile(FILE *fp) {
    char *buffer = NULL;
    size_t size = 0;

/* Get the buffer size */
    fseek(fp, 0, SEEK_END); /* Go to end of file */
    size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
    rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
    buffer = (char *) malloc((size + 1) * sizeof(*buffer)); /* size + 1 byte for the \0 */

/* Read the file into the buffer */
    fread(buffer, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
    buffer[size] = '\0';
    printf("\033[34m %s", buffer);
    fclose(fp);

/* Print it ! */
}

void selectMenu(int i) {// afficher 1
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

int choiceMenu() {
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
