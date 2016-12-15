#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include "image.h"
#include "constant.h"


int main (int argc, char *argv[]){

    time_t localHourNow = time (NULL);  //On récupère la date et la stocke dans un tableau
    struct tm tm_localHourNow = *localtime (&localHourNow);
    char tabLocalHourNow[sizeof "HH:MM:SS"];
    int i;
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);       //Initialisation des différentes variables
    int screenSizeX = w.ws_col;
    int screenSizeY = w.ws_row;  //Avec les varaibles pour la taille de l'écran

    //tab 11
    ImgStruct number0;
    ImgStruct number1;
    ImgStruct number2;
    ImgStruct number3;
    ImgStruct number4;  //On définit les différentes structures
    ImgStruct number5;
    ImgStruct number6;
    ImgStruct number7;
    ImgStruct number8;
    ImgStruct number9;
    ImgStruct pts;

    getPicture("0.pbm", &number0);
    getPicture("1.pbm", &number1);
    getPicture("2.pbm", &number2);
    getPicture("3.pbm", &number3);
    getPicture("4.pbm", &number4); //On met en mémoire les images
    getPicture("5.pbm", &number5);
    getPicture("6.pbm", &number6);
    getPicture("7.pbm", &number7);
    getPicture("8.pbm", &number8);
    getPicture("9.pbm", &number9);
    getPicture("pts.pbm", &pts);

    ImgStruct* p_np0;
    ImgStruct* p_nb1;
    ImgStruct* p_nb2; //On crée les différents pointeurs pour les adresses
    ImgStruct* p_nb3;
    ImgStruct* p_nb4;
    ImgStruct* p_nb5;
    ImgStruct* p_nb6;

    while(1){

        strftime(tabLocalHourNow,sizeof(tabLocalHourNow),"%H:%M:%S\n",localtime(&localHourNow )); //On recharge l'heure actuel

        if(tabLocalHourNow[0] == '0') {  //Beaucoup trop de switch case mais bon, on a pas réussi ni eu le temps pour rendre cette partie propre
          p_nb1 = &number0;             //Au moins elle fonctionne ;)
        }
        if(tabLocalHourNow[0] == '1') {
          p_nb1 = &number1;
        }
        if(tabLocalHourNow[0] == '2') {
          p_nb1 = &number2;
        }
        if(tabLocalHourNow[0] == '3') {
          p_nb1 = &number3;
        }
        if(tabLocalHourNow[0] == '4') {
          p_nb1 = &number4;
        }
        if(tabLocalHourNow[0] == '5') {
          p_nb1 = &number5;
        }
        if(tabLocalHourNow[0] == '6') {
          p_nb1 = &number6;
        }
        if(tabLocalHourNow[0] == '7') {
          p_nb1 = &number7;
        }
        if(tabLocalHourNow[0] == '8') {
          p_nb1 = &number8;
        }
        if(tabLocalHourNow[0] == '9') {
          p_nb1 = &number9;
        }
        // Array check for the second number
        if(tabLocalHourNow[1] == '0') {
          p_nb2 = &number0;
        }
        if(tabLocalHourNow[1] == '1') {
          p_nb2 = &number1;
        }
        if(tabLocalHourNow[1] == '2') {
          p_nb2 = &number2;
        }
        if(tabLocalHourNow[1] == '3') {
          p_nb2 = &number3;
        }
        if(tabLocalHourNow[1] == '4') {
          p_nb2 = &number4;
        }
        if(tabLocalHourNow[1] == '5') {
          p_nb2 = &number5;
        }
        if(tabLocalHourNow[1] == '6') {
          p_nb2 = &number6;
        }
        if(tabLocalHourNow[1] == '7') {
          p_nb2 = &number7;
        }
        if(tabLocalHourNow[1] == '8') {
          p_nb2 = &number8;
        }
        if(tabLocalHourNow[1] == '9') {
          p_nb2 = &number9;
        }
        // Array check for the third number
        if(tabLocalHourNow[3] == '0') {
          p_nb3 = &number0;
        }
        if(tabLocalHourNow[3] == '1') {
          p_nb3 = &number1;
        }
        if(tabLocalHourNow[3] == '2') {
          p_nb3 = &number2;
        }
        if(tabLocalHourNow[3] == '3') {
          p_nb3 = &number3;
        }
        if(tabLocalHourNow[3] == '4') {
          p_nb3 = &number4;
        }
        if(tabLocalHourNow[3] == '5') {
          p_nb3 = &number5;
        }
        if(tabLocalHourNow[3] == '6') {
          p_nb3 = &number6;
        }
        if(tabLocalHourNow[3] == '7') {
          p_nb3 = &number7;
        }
        if(tabLocalHourNow[3] == '8') {
          p_nb3 = &number8;
        }
        if(tabLocalHourNow[3] == '9') {
          p_nb3 = &number9;
        }
        // Array check for the fourth number
        if(tabLocalHourNow[4] == '0') {
          p_nb4 = &number0;
        }
        if(tabLocalHourNow[4] == '1') {
          p_nb4 = &number1;
        }
        if(tabLocalHourNow[4] == '2') {
          p_nb4 = &number2;
        }
        if(tabLocalHourNow[4] == '3') {
          p_nb4 = &number3;
        }
        if(tabLocalHourNow[4] == '4') {
          p_nb4 = &number4;
        }
        if(tabLocalHourNow[4] == '5') {
          p_nb4 = &number5;
        }
        if(tabLocalHourNow[4] == '6') {
          p_nb4 = &number6;
        }
        if(tabLocalHourNow[4] == '7') {
          p_nb4 = &number7;
        }
        if(tabLocalHourNow[4] == '8') {
          p_nb4 = &number8;
        }
        if(tabLocalHourNow[4] == '9') {
          p_nb4 = &number9;
        }
        // Array check for the fifth number
        if(tabLocalHourNow[6] == '0') {
          p_nb5 = &number0;
        }
        if(tabLocalHourNow[6] == '1') {
          p_nb5 = &number1;
        }
        if(tabLocalHourNow[6] == '2') {
          p_nb5 = &number2;
        }
        if(tabLocalHourNow[6] == '3') {
          p_nb5 = &number3;
        }
        if(tabLocalHourNow[6] == '4') {
          p_nb5 = &number4;
        }
        if(tabLocalHourNow[6] == '5') {
          p_nb5 = &number5;
        }
        if(tabLocalHourNow[6] == '6') {
          p_nb5 = &number6;
        }
        if(tabLocalHourNow[6] == '7') {
          p_nb5 = &number7;
        }
        if(tabLocalHourNow[6] == '8') {
          p_nb5 = &number8;
        }
        if(tabLocalHourNow[6] == '9') {
          p_nb5 = &number9;
        }
        // Array check for the sixth number
        if(tabLocalHourNow[7] == '0') {
          p_nb6 = &number0;
        }
        if(tabLocalHourNow[7] == '1') {
          p_nb6 = &number1;
        }
        if(tabLocalHourNow[7] == '2') {
          p_nb6 = &number2;
        }
        if(tabLocalHourNow[7] == '3') {
          p_nb6 = &number3;
        }
        if(tabLocalHourNow[7] == '4') {
          p_nb6 = &number4;
        }
        if(tabLocalHourNow[7] == '5') {
          p_nb6 = &number5;
        }
        if(tabLocalHourNow[7] == '6') {
          p_nb6 = &number6;
        }
        if(tabLocalHourNow[7] == '7') {
          p_nb6 = &number7;
        }
        if(tabLocalHourNow[7] == '8') {
          p_nb6 = &number8;
        }
        if(tabLocalHourNow[7] == '9') {
          p_nb6 = &number9;
        }
        showMultiPicture(p_nb1,p_nb2,p_nb3,p_nb4,p_nb5,p_nb6,&pts , (w.ws_col /2) - 14, (w.ws_row/2) + 1 );  //On fait appelle a la fonction showMultiPicture

        printf("\nCet ecran sera Actualisé dans quelques secondes ");
        fflush(stdout);  //On force l'affichage

        for(i = 0; i < N_TIME; i++){
            printf(".");
            fflush(stdout); //En fonction de la constante N_TIME on attend N_TIME secondes pour changer l'heure avec un ajout d'un point par secondes
            sleep(1); //On attend une seconde
        }
        localHourNow = time (NULL);

    }
return 0;
}
