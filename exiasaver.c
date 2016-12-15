#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#define STR_MAX_LENGHT  255

void historicalWrite(int type,char* posPlane,int resolution,char* imgLocation){ //Fonctions pour �crire dans l'historique
	FILE* historicalFile = NULL; //On initialise historicalFile de type *FILE
	char *catString = malloc (sizeof (*catString) * STR_MAX_LENGHT); // on cr�e deux tableaux dynamique
	char *buffer = malloc (sizeof (*buffer) * STR_MAX_LENGHT);
	char *imgLocate;
	strcpy(imgLocate, imgLocation); //En raison d'un bug nous copions la localisation de l'image dans une autre variable
	historicalFile = fopen("historique.txt", "a+"); // on ouvre l'historique.txt � la fin
	if(historicalFile != NULL){ // Si historique.txt � bien pu etre ouvert alors
		time_t localHourNow = time (NULL);  //On r�cup�re la date et la stocke dans un tableau
		struct tm tm_localHourNow = *localtime (&localHourNow);
		char tabLocalHourNow[sizeof "JJ/MM/AAAA HH:MM:SS"];
		strftime (tabLocalHourNow, sizeof tabLocalHourNow, "%d/%m/%Y %H:%M:%S", &tm_localHourNow);
		strcpy(catString,tabLocalHourNow);// on copy la date dans un char* temporaire
		switch(type) //en fonction des types on va �crire diff�rentes choses dans l'historique
		{
			case 1:

				strcat(catString, ";1;");
				strcat(catString, imgLocate);
            break;
			case 2:
				strcat(catString, ";2;resolution:");
				sprintf(buffer,"%d", resolution);
				strcat(catString, buffer);
			break;
			case 3:
				strcat(catString, ";3;");
				strcat(catString, posPlane);
			break;
        }
		strcat(catString, "&\n"); //On ajoute un & et un saut � la ligne � la fin de chaque ligne
		fputs(("%s", catString), historicalFile); // On �crit enfin dans le fichier avec un fputs
		fclose(historicalFile); //On ferme le fichier
		free(buffer);
		free(catString); //On lib�re la m�moire
	}
	else{
		printf("Error"); //Si le fichier n'a pas �tait ouvert alors erreur
		exit;
	}
}

void stats(){ //Fonction de stats

    printf("#################\n");
    printf("###    MENU   ###\n");
    printf("#################\n\n\n");
    printf("Tri par date croissante 'c'\n");
    printf("Tri par date decroissante 'd'\n"); //Simple affichage graphique du menu
    printf("Tri par types croissant't'\n");
    printf("Tri par types decroissant'p'\n");
    printf("Statistiques totaux 's'\n");
    printf("Tappez 'x' pour remettre votre historique a zero\n");
    printf("Tappez 'q' pour quitter\n");
    char choiceUser;
    scanf("%c", &choiceUser); //R�cup�ration de ce que veut faire l'utilisateur
    FILE* fichier = NULL;
    fichier = fopen("historique.txt", "r"); //Ouverture du fichier
    if (fichier != NULL){ //Si le fichier est bien ouvert
        if(choiceUser == 'c'){ //le choix de l'utilisateur est c
            system("clear"); //effacage de la console
            char strTemp[STR_MAX_LENGHT]="";//creation tableaux de caract�res
            while (fgets(strTemp, STR_MAX_LENGHT, fichier) != NULL) //tant que on est pas arriver � la fin du fichier
            {
                printf("%s", strTemp);//On affiche la ligne
            }
        }
        if(choiceUser == 'd'){ // si le choix est d
            system("clear"); //effacage de la console
            char strTemp[STR_MAX_LENGHT]=""; //On cr� un tableau de caract�res vide
            int numberLine, valTemp;
            for(numberLine = 0; fgets(strTemp, STR_MAX_LENGHT, fichier) != NULL; numberLine++){} //Compteur de ligne artisanal
            for(; numberLine > 0; numberLine--){ //d�cr�mentation en fonction du nombre de ligne
                rewind(fichier); //On se place en d�but de fichier
                for(valTemp = numberLine; valTemp > 0; valTemp--){ //On incr�mente pour afficher une certaine ligne du fichier
                    fgets(strTemp, STR_MAX_LENGHT, fichier);
                }
                printf("%s", strTemp); //affichage de la fameuse ligne
            }
        }
        if(choiceUser == 't'){ //Si le choix est t
            system("clear"); //effacage de la console
            char strTemp[STR_MAX_LENGHT]; //cr�ation d'un tableau de caract�re
            char currentChar;
            int numberLine, count; //Initialisations de plusieus variables
            for(numberLine = 0; fgets(strTemp, STR_MAX_LENGHT, fichier) != NULL; numberLine++){} //Compteur de ligne artisanal
            int tabHis[numberLine+1][2]; //Cr�ation d'un tableau � deux dimentions
            rewind(fichier); //On se replace en d�but de fichier
            for(count = 0; count < numberLine; count++){ //For en incr�mentation jusqu'au nombre de ligne
                while(currentChar != 59){
                    currentChar = fgetc(fichier); //Tant qu'on ne rencontre pas un ; alors on avance de caract�res en caract�res
                }
                currentChar = fgetc(fichier);
                tabHis[count][0] = currentChar-48;
                tabHis[count][1] = count;  //Zone ou on r�cup�re la valeur ;valeur; du fichier historique qui est en r�alit� le type qui va etre lanc�
                currentChar = fgetc(fichier);
                currentChar = fgetc(fichier); //On avance de deux caract�res, peut etre remplac� par fseek mais manque de temps :)
            }
            int i,j,tempValue1, tempValue2;
            for(j = numberLine; j > 0; j--){
                for(i = 0; i < j - 1; i++){
                    if(tabHis[i][0] > tabHis[i + 1][0]){
                        tempValue1 = tabHis[i][0];
                        tempValue2 = tabHis[i][1];
                        tabHis[i][0] = tabHis[i+1][0];  //Algorithme de tri � bulle, de tableaux bidimentionel
                        tabHis[i][1] = tabHis[i+1][1];
                        tabHis[i+1][0] = tempValue1;
                        tabHis[i+1][1] = tempValue2;
                    }
                }
            }
            for(i = 0; i < numberLine; i++){
                rewind(fichier);
                for(j = 0; j <= tabHis[i][1]; j++){
                    fgets(strTemp, STR_MAX_LENGHT, fichier); //Ici on affiche les ligne de l'historique tri�
                }
                printf("%s", strTemp);
            }
        }
        if(choiceUser == 'p'){
            system("clear");
            char strTemp[STR_MAX_LENGHT];
            char currentChar;
            int numberLine, count; //Initialisation des variables
            for(numberLine = 0; fgets(strTemp, STR_MAX_LENGHT, fichier) != NULL; numberLine++){} //encore et toujours le compteur de ligne fait maison
            int tabHis[numberLine+1][2]; //cr�ation du tab bidimentionnel (pointeurs de pointeur)
            rewind(fichier); //on se place au d�but du fichier
            for(count = 0; count < numberLine; count++){ //Incr�mentation en fonction du nombre de ligne
                while(currentChar != 59){ //Tant qu'on ne rencontre pas un ; on lit caract�re par caract�re
                    currentChar = fgetc(fichier);
                }
                currentChar = fgetc(fichier);
                tabHis[count][0] = currentChar-48;
                tabHis[count][1] = count; //Ici on stocke le type qui a �tait enregistr� dans l'historique ;valeur;
                currentChar = fgetc(fichier);
                currentChar = fgetc(fichier);
            }
            int i,j,tempValue1, tempValue2;
            for(j = numberLine; j > 0; j--){
                for(i = 0; i < j - 1; i++){
                    if(tabHis[i][0] > tabHis[i + 1][0]){
                        tempValue1 = tabHis[i][0];
                        tempValue2 = tabHis[i][1];
                        tabHis[i][0] = tabHis[i+1][0]; //De nouveau l'algorithme de tri bidimentionnel
                        tabHis[i][1] = tabHis[i+1][1];
                        tabHis[i+1][0] = tempValue1;
                        tabHis[i+1][1] = tempValue2;
                    }
                }
            }
            for(i = numberLine; i > 0; i--){
                rewind(fichier);
                for(j = 0; j <= tabHis[i][1]; j++){
                    fgets(strTemp, STR_MAX_LENGHT, fichier); //On affiche encore l'historique en fonction du tri effectu�
                }
                printf("%s", strTemp);

            }
        }
        if(choiceUser == 's'){ //Choix de l'utilisateur s
            system("clear");
            char strTemp[STR_MAX_LENGHT];
            char currentChar;
            int numberLine, count, tempValue; //initialisation des diff�rentes variable
            int statsCount[4] ={0};
            for(numberLine = 0; fgets(strTemp, STR_MAX_LENGHT, fichier) != NULL; numberLine++){};
            statsCount[0] = numberLine;
            rewind(fichier);
            for(count = 0; count < numberLine; count++)
            {
                while(currentChar != 59){
                    currentChar = fgetc(fichier);
                }
                currentChar = fgetc(fichier);
                tempValue = currentChar-48;// On lit le nombre de fois ou on a utilis� l'exiasaver en fonction du type
                switch(tempValue){
                    case 1:
                        statsCount[1]++;
                    break;
                    case 2:
                        statsCount[2]++;
                    break;
                    case 3:
                        statsCount[3]++;
                    break;
                }
                currentChar = fgetc(fichier);
                currentChar = fgetc(fichier);
            } //On affiche les diff�rents statistiques
            printf("Il y a eu %d ecrans de veilles :\ndont %d statiques %d dynamiques et %d interactifs\n", statsCount[0], statsCount[1], statsCount[2], statsCount[3]);
        }
        if(choiceUser == 'x'){
            fclose(fichier);
            fichier = fopen("historique.txt", "w+"); //On r�ouvre le fichier avec w+, ce qui efface le contenu
        }
        if(choiceUser == 'q'){} //On quitte simplement
        }
    fclose(fichier);
} //On a pas r�ussi a faire marcher ce choiceRand � cause des param�tre, ducoup par manque de temps ung ros copier coller dans le main, c'est pas propre mais ca fonctionne
/*void choiceRand(int argc,char *argv[],int *type,char posPlane[],int* resolution,char imgLocation[])
{
    int posX, posY, choiceImg;
    if(argc > 1)
    {
        *type = atoi(argv[1]);
	}
	else
	{
        srand((unsigned int)time((time_t *)NULL));
        *type = rand()%3 + 1 ;

	}
    printf("test");
	if(argc > 2){
        switch(*type)
        {
            case 1:
                sprintf(imgLocation,"%s", argv[2]);
            break;
            case 2:
                *resolution = atoi(argv[2]);
            break;
            case 3:
                sprintf(posPlane,"%s", argv[2]);
            break;
        }
	}else
        {

	    switch(*type)
        {
            case 1:
                srand((unsigned int)time((time_t *)NULL));
                choiceImg = rand()%5;
                char* catString;
                char* buffer;
                sprintf(buffer,"img%d.", choiceImg);
                strcat(catString, buffer);
                    switch(choiceImg){
                        case 1:
                            strcat(catString, "PBM");
                        break;
                        case 2:
                            strcat(catString, "PGM");
                        break;
                        case 3:
                            strcat(catString, "PGM");
                        break;
                        case 4:
                            strcat(catString, "PTM");
                        break;
                        case 5:
                            strcat(catString, "PTM");
                        break;}
                sprintf(imgLocation,"%s", catString);
            break;
            case 2:
                srand((unsigned int)time((time_t *)NULL));
                *resolution = rand()%6;
            break;
            case 3:
                srand((unsigned int)time((time_t *)NULL));
                posX = rand()%80;
                srand((unsigned int)time((time_t *)NULL));
                posY = rand()%22;
                sprintf(posPlane, "%dx%d", posX, posY);
            break;
        }
    }
}*/
int main(int argc, char *argv[]) {                      //Le main
    if(argc == 2 && strcmp(argv[1], "-stats") == 0){//on analyse si l'appel de l'exiasaver est fait avec un param�tre -stats, si oui on va dans stats()
        stats();
    }
    else{
    	int type, resolution;
    	char *imgLocation = malloc (sizeof (*imgLocation) * STR_MAX_LENGHT);
    	char *posPlane = malloc (sizeof (*posPlane) * STR_MAX_LENGHT);
    	char *posPlaneBis = malloc (sizeof (*posPlaneBis) * STR_MAX_LENGHT); //Initialisation des diff�rents tableaux dynamique
        // choiceRand(argc,argv,&type,posPlane,&resolution,imgLocation);
        int posX, posY, choiceImg;
        if(argc > 1)//Si l'utilisateur a choisi quel type il voulait alors on ajuste le type avec l'argv
        {
            type = atoi(argv[1]);
        }
        else
        {
            srand((unsigned int)time((time_t *)NULL)); //Sinon on attribut un type al�atoire
            type = rand()%3 + 1 ;
        }
        if(argc > 2){
            char *testvar = malloc(strlen(argv[2]) + 1);
            switch(type)
            {
                case 1:
                    strcpy(testvar, argv[2]);
                    sprintf(imgLocation,"%s", testvar);  //Si l'utilisateur inclut ses propre param�tre pour les types d'�cran
                break;                                  //Alors on met les diff�rents param�tre en fonction de ces choix
                case 2:
                    strcpy(testvar, argv[2]);
                    resolution = atoi(testvar);
                break;
                case 3:
                    strcpy(testvar, argv[2]);
                    sprintf(posPlane,"%s", testvar);
                break;
            }
        }
        else
        {
            switch(type)
            {
                case 1:
                    srand((unsigned int)time((time_t *)NULL)); //Sinon on les d�finit al�atoirement
                    choiceImg = rand()%3+1;
                    sprintf(imgLocation, "%d.p", choiceImg);
                        switch(choiceImg){
                            case 1:
                                strcat(imgLocation, "bm");
                            break;
                            case 2:
                                strcat(imgLocation, "bm");
                            break;
                            case 3:
                                strcat(imgLocation, "bm");
                            break;
                            case 4:
                                strcat(imgLocation, "bm");
                            break;
                            case 5:
                                strcat(imgLocation, "bm");
                            break;}
                break;
                case 2:
                    /*srand((unsigned int)time((time_t *)NULL));
                    resolution = rand()%6;*/
                break;
                case 3:
                    srand((unsigned int)time((time_t *)NULL));
                    posX = rand()%80;
                    srand((unsigned int)time((time_t *)NULL));
                    posY = rand()%15;
                    printf("%d et %d", posX, posY);
                    sprintf(posPlane, "%dx%d", posX, posY);  //Ici c'est bizzare mais sans le printf et le strcpy, rien ne marche,
                    printf("%s", posPlane);                 //surement une histoire de buffer mais si vous avez la solution je suis prenneur
                    strcpy(posPlaneBis, posPlane);
                break;
            }
        }
        historicalWrite(type,posPlane,resolution, imgLocation);  //On va dans la partie �criture de l'historique
        system("clear");
             if(type == 1)
            {
                    char *arguments[] = {"./static", imgLocation, NULL};
                    //printf("arg = %s\n", arguments[1]);
                    execvp("./static", arguments);
            }
             if(type == 2)
            {
                    /*char strResolution[STR_MAX_LENGHT] = {};  //On aurait bien aim� inclure ces param�tres mais nous n'avons pas r�ussi � faire la r�solution
                    sprintf(strResolution, "%d", resolution);*/   //Ici on �x�cute les diff�rents �crans de veilles en fonctions du choix ou de l'al�atoire
                    char *arguments[] = {"./dynamique", NULL};
                    execvp("./dynamique", arguments);
            }
             if(type == 3)
            {
                    char *arguments[] = {"./interactif", posPlane, NULL};
                    execvp("./interactif", arguments);
            }
        free(posPlane);
        free(posPlaneBis); //On lib�re la m�moire
        free(imgLocation);
    }
    return(0);  //Finit tout c'est bien pass� return 0;
}
