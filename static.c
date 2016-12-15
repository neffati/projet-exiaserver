#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "image.h"
#include "constant.h"


int main (int argc, char *argv[]){
    // printf(CLEAR);
    clear();
    char *location = "ex1.pbm";

    ImgStruct image;

    getPicture("ex1.pbm", &image);

    struct winsize w;
    int touch;
    ioctl(0, TIOCGWINSZ, &w);
    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);
    double sizeX = (double)w.ws_col;
    double sizeY = (double)w.ws_row;
    double middleImageX = sizeX/2;
    double middleImageY = (sizeY-1)/2;
    //printf("%f et %f", sizeX, sizeY);
    int pid = fork();
    switch (pid){
        case -1:  // Si on a une erreur
            perror("fork");
            return EXIT_FAILURE;
            break;
        case 0:  // Si on est dans le fils
            showPicture(&image,middleImageX,middleImageY);
            break;
        default:  // Si on est dans le père
            wait(NULL);
            printf("Veuillez appuyer sur une touche pour éteindre le programme...");
            getchar( ) ;
            break;
    }
return 0;

}
