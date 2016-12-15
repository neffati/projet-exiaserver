#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "image.h"
#include "constant.h"

void getPicture(char *location, ImgStruct * p_img)
{
    FILE* fichier = NULL;
    char strTemp[STR_MAX_LENGHT];
    char tabTemp[255];  //Différentes variables initialisé
    int  i, j,k, val;
    char currentChar = ' ';

    fichier = fopen(location, "r");

    // Lecture du fichier
    if(fichier == NULL){
        perror("erreur ouverture fichier");
        return ;
    }
    // rewind(fichier);
    currentChar = fgetc(fichier);
    while(currentChar == '#'){
        fgets(strTemp, STR_MAX_LENGHT, fichier); //On évite tout les lignes de commentaires donc elle avec un  #
        currentChar = fgetc(fichier);
    }

    fseek(fichier, -1, SEEK_CUR);
    fgets(strTemp, STR_MAX_LENGHT, fichier);
    //printf("Fichier de type %s", strTemp);
    currentChar = fgetc(fichier);
    while(currentChar == '#'){
        fgets(strTemp, STR_MAX_LENGHT, fichier);
        currentChar = fgetc(fichier);
    }

    fseek(fichier, -1, SEEK_CUR);
    fgets(strTemp, STR_MAX_LENGHT, fichier);

    // LECTURE DE LA TAILLE
    p_img->x = atoi(strtok(strTemp, " "));
    p_img->y = atoi(strtok(NULL, " "));

    // ALLOCATION TABLEAU 2 DIMENSIONS
    // Allocation des pointeurs
    p_img->tab = ( int ** ) malloc( sizeof( int *) * p_img->y ) ;
    // allocation des lignes
    for( i=0; i< p_img->y;i++ )
    {
        p_img->tab[i] = (int*) malloc( sizeof(int) * p_img->x ) ;
    }

    // Lecture de l'image

    for(i = 0; i < p_img->y; i++)
    { // Pour chaque ligne
        for(j = 0; j < p_img->x ; j++)
        { // Lecture d'une ligne
            currentChar = fgetc(fichier); // Le caractere
            p_img->tab[i][j]  = currentChar - '0' ; // Un '0' ou '1'
            // Pour afficher le pbm en chiffre -> printf("%c", charActual);
            // Le suivant : espace ou fin de ligne
            fgetc(fichier);
       }
       // Pour sauter une ligne entre l'affichage pbm en chiffre -> printf("\n");
    }
    fclose(fichier);
}


void showPicture(ImgStruct * p_img, int posMiddleImgX, int posMiddleImgY ){

    char color[10][10]; // Color codex
    int i, j, k ;
    char car ;
    int val ;
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w); //Différentes variables avec variables pour la taille console
    int screenSizeX = w.ws_col;
    int screenSizeY = w.ws_row;

    int marginDown = screenSizeY - (posMiddleImgY + (p_img->y/2));
    // Initialisation des couleurs
    strcpy(color[0],"\x1b[30m"); //Noir
    strcpy(color[1],"\033[01;37m"); //Blanc
    strcpy(color[2],"\x1b[31m"); //Rouge
    strcpy(color[3],"\x1b[32m"); //Vert
    strcpy(color[4],"\x1b[33m"); //Marron
    strcpy(color[5],"\x1b[34m"); //Bleu
    strcpy(color[6],"\x1b[35m"); //Magenta
    strcpy(color[7],"\x1b[36m"); //Cyan
    strcpy(color[8],"\033[22;37m"); //Gris
    strcpy(color[9],"\033[01;33m"); //Jaune

    double posX = floor( posMiddleImgX - p_img->x / 2 ) ;
    double posY = floor( posMiddleImgY - p_img->y / 2 ) ;

    // marge haute
    for(k = 1 ; k <= posY ; k++) printf("\n");

    printf(GR_START);
    for (i = 0; i < p_img->y; i++)
    {   // marge gauche
        for(k = 0; k < posX ; k++) printf(" ") ;

        for (j = 0; j < p_img->x; j++)
        {
            val=p_img->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf("\n");
    }
    printf(GR_STOP);
    // marge basse
    for( k=0; k < marginDown ; k++) printf("\n");
    //fflush(stdout);
}

void showMultiPicture(ImgStruct * p_img1, ImgStruct * p_img2, ImgStruct * p_img3,ImgStruct * p_img4, ImgStruct * p_img5, ImgStruct * p_img6, ImgStruct * p_imgpts, int posMiddleImgX, int posMiddleImgY )
{
    char color[10][10]; // Color codex
    int i, j, k ;
    char car ;
    int val ;
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w); //Différentes variables avec variables pour la taille console
    int screenSizeX = w.ws_col;
    int screenSizeY = w.ws_row;
    int marginDown = screenSizeY - (posMiddleImgY + (p_img1->y/2));
    // Initialisation des couleurs
    strcpy(color[0],"\x1b[30m"); //Noir
    strcpy(color[1],"\033[01;37m"); //Blanc
    strcpy(color[2],"\x1b[31m"); //Rouge
    strcpy(color[3],"\x1b[32m"); //Vert
    strcpy(color[4],"\x1b[33m"); //Marron
    strcpy(color[5],"\x1b[34m"); //Bleu
    strcpy(color[6],"\x1b[35m"); //Magenta
    strcpy(color[7],"\x1b[36m"); //Cyan
    strcpy(color[8],"\033[22;37m"); //Gris
    strcpy(color[9],"\033[01;33m"); //Jaune
    double posX = floor( posMiddleImgX - p_img1->x / 2 ) ;
    double posY = floor( posMiddleImgY - p_img1->y / 2 ) ;
    // marge haute
    for(k = 1 ; k <= posY ; k++) printf("\n");
    printf(GR_START);
    for (i = 0; i < p_img1->y; i++)
    {   // marge gauche
        for(k = 0; k < posX ; k++) printf(" ") ; //On fait la marge haute

        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img1->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset); //Ici on affiche pour chaque image sa ligne avec un espace de 1 caractères
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img2->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_imgpts->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img3->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img4->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_imgpts->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img5->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
        printf(" ");
        for (j = 0; j < p_img1->x; j++)
        {
            val=p_img6->tab[i][j];
            car = ( val == 0 ) ? ' ' : '0' ;
            printf("%s%c%s",color[val],car,reset);
        }
    printf("\n");
    }
    printf(GR_STOP); //On arrete le mode graphique
    // marge basse
    for( k=0; k < marginDown - 1 ; k++) printf("\n"); //On crée la marge basse
    //fflush(stdout);
}


