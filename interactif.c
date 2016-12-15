#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/ioctl.h>
#include "image.h"
#include "constant.h"
#define STR_MAX_LENGHT  255

int main(int argc, char* argv[]){
    system("clear");
    int posX, posY; /** nous définisons la position X et Y;*/

    /** nous définissons la taille de l'écran où l'avion se déplacera */
    char str[20];
    strcpy(str, "40x5");
    char* strTemp;

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int screenSizeX = w.ws_col;
    int screenSizeY = w.ws_row;

    strTemp = strtok(str, "x");
    posX = atoi(strTemp);
    strTemp = strtok(NULL, "x");
    posY = atoi(strTemp);
    printf("\nx=%d et y=%d\n", posX, posY);

    /** nous définissons la structure de l'image de l'avion  */
    ImgStruct plane1;
    ImgStruct plane2;
    ImgStruct plane3;
    ImgStruct plane4;


    /** nous faisons appel a la bonne image de l'avion selon la position choisie  */
    getPicture("avionhaut.pbm", &plane1);
    getPicture("avionbas.pbm", &plane2);
    getPicture("aviongauche.pbm", &plane3);
    getPicture("aviondroite.pbm", &plane4);

    showPicture(&plane1,posX, posY); /** nous affichons l'image  */



    /** Direction clavier de l'avion */
    char direction;
    int lastAction;
    while (1)
    {
        if (posX >=  screenSizeX) posX = 1;
        if (posY >=  screenSizeY) posY = 1;
        if (posX <= 0) posX = screenSizeX - 1;
        if (posY <= 0) posY = screenSizeY - 1;
        scanf("%c", &direction);
        switch (direction) /** nous faisons une boucle switch case pour pouvoir faire bouger l'avion */
        {
            case 104 :  /** Direction vers le haut, touche "h" */
                posY--;  /** nous devons faire une décrémentation pour que l'avion puisse aller vers le haut */
                showPicture(&plane1, posX, posY); /** nous affichons ensuite l'image*/
                break;
            case 98 : /** Direction vers le bas, touche "b" */
                posY++; /** nous devons faire une incrémentation pour que l'avion puisse aller vers le bas */
                showPicture(&plane2, posX, posY);/** nous affichons ensuite l'image*/
                break;
            case 103 : /** Direction vers la gauche, touche "g" */
                posX--;/** nous devons faire une décrémentation pour que l'avion puisse aller vers la gauche */
                showPicture(&plane3, posX, posY);/** nous affichons ensuite l'image*/
                break;
            case 100 : /** Direction vers la droite, touche "d" */
                posX++;/** nous devons faire une incrémentation pour que l'avion puisse aller vers la droite */
                showPicture(&plane4, posX, posY);/** nous affichons ensuite l'image*/
                break;
            case 56 : /** Direction vers le haut, touche "8" */
                posY--;
                showPicture(&plane1, posX, posY);
                break;
            case 50 : /** Direction vers le bas, touche "2" */
                posY++;
                showPicture(&plane2, posX, posY);
                break;
            case 52 : /** Direction vers la gauche, touche "4" */
                posX--;
                showPicture(&plane3, posX, posY);
                break;
            case 54 : /** Direction vers la droite, touche "6" */
                posX++;
                showPicture(&plane4, posX, posY);
                break;
            case 113: /** Quitte avec la touche "q" */
                showPicture(&plane1, posX, posY);
                exit(0);
                break;
            default : /** L'avion répéte la derniere direction */
                break;
        } /** nous faisons la meme chose fait avec les les lettes d,g,h,b mais pour les chiffres 8,2,4,6 */

    }

    return 0;

}
