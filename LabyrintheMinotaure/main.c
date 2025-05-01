/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+       Jeu Fil d'Arianne                                                                                          +
+       Programmation C                                                                                            +
+       ITSCM 2024-2025                                                                                            +
+                                                                                                                  +
+       Maxime Borboux                                                                                             +
+       Marwane Tahiri                                                                                             +
+                                                                                                                  +
+       En remerciant Monsieur Jaghou pour le challenge que ce jeu nous a apporté                                  +
+       en nous permettant de nous exercer sur les matières apprises en cours, ainsi que les procédures fournies.  +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Temps.h"
#include "TableauxLabyrinthes.h" //ici sont inclus les différents codes fournis par Monsieur Jaghou
#include "Affichage.h"
#include <windows.h> //utilisé avec le setconsoleoutputCP pour gérer les caractères spéciaux

void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); ///MAX //Procédure qui traduis le labyrinthe sous forme d'affichage
int choixDuLabyrinthe(int easteregg[1]); /// MARWANE // Fonction qui retourne sous forme d'entier le choix du labyrinthe
void introduction(); /// MARWANE // Procedure qui nous donne l'introduction du jeu
void renameCharacter(char nom_hero[], char nom_princesse[]);
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]); ///MARWANE //Procedure qui permet de choisir 1 des 10 labyrinthe
void miseEnPlaceThesee(int posH[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); /// MAX//Procedure qui mets en place, dans le labyrinthe back-end, le personnage
void miseEnPlaceMinotaure(int posM[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); ///MAX
void miseEnPlacePrincess(int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); ///MAX
void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int clauseDeSortie, int easteregg[1]); ///MARWANE //Procédure qui permet le premier jeu avec le deplacement unique du héro
void jeuTWO(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int clauseDeSortie); ///MAX //Procédure qui permet le second jeu avec le deplacement du héro et du minotaure

int main() ///MAX
{
    srand(time(NULL));
    int choixLabyrinthe=rand()%9 + 1; //valeur initée à une valeur entre 1 et 10 pour permettre la sélection d'un labyrinthe au hasard
    char nom_hero[15]= "Thésée";
    char nom_princesse[15] = "Arianne";
    char choix; //caractère utilisé pour effectué le choix dans le menu
    int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]; //labyrinthe utilisé pour effectué le transfert du contenu du labyrinthe selectionné sur base du nombre choixLabyrinthe
    int posH[2]; //position en X et Y de Thésée
    int posM[2]; //position en X et Y du Minotaure
    int clauseDeSortie = 1; //astuce utilisée pour signalé si le jeu fini ou non
    int easteregg[1] = {0}; //Labyrinthe Bonus. Création d'un tableau pour le passage d'information d'une option du code à l'autre


    do
    {
        printf("\n===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n4. Jeu difficulte 1\n5. Jeu difficulte 2\n");
        choix = getch();//permet d'établir un choix sans la commande entrée

        switch (choix)
        {
        case '1' :
            introduction();
            printf("\nAppuyez sur Enter pour revenir au menu\n");
            getc(stdin); //permet de revenir au menu en appuyant sur la touche "Enter"
            EffaceEcran();
            FixePosCurseur(0,0); //Permet de revenir à la position (0,0) car l'efface écran nous ramene à la position (1,1)
            break;

        case '2':
            renameCharacter(nom_hero, nom_princesse);
            break;

        case '3':

            choixLabyrinthe=choixDuLabyrinthe(easteregg); // Permet de faire un choix du Labyrinthe sur ceux disponible - easteregg affichage supplementaire selon certaines conditions

            break;

        case '4':

            jeuONE(choixLabyrinthe, labyrintheChoisi, posH, posM, clauseDeSortie, easteregg); //Permet de choisir le premier niveau de difficulté avec le labyrinthe associé

            break;

        case '5':

            jeuTWO(choixLabyrinthe, labyrintheChoisi, posH, posM, clauseDeSortie); //Permet de choisir le deuxième niveau de difficulté avec le labyrinthe associé

            break;
        }
        EffaceEcran();
        FixePosCurseur(0,0);
    }
    while (choix < 1 || choix >6); //bloque la sortie tant que les valeurs de 1 à 5 ne sont pas entrées

    return 0;
}
void renameCharacter(char nom_hero[], char nom_princesse[])// Ce code reprend pour argument les 2 chaines de caractères contenant les noms du héros et de la princesse, ceux-ci peuvent être modulé comme on le souhaite
{
    SetConsoleOutputCP(1252);//utilisé pour gérer les caractères type "é", "è",... Cette référence nous a été fourni après une recherche sur le sujet (unique recherche externe pour le code
    printf("\nVeuillez introduire le nom du Héro \n");
    scanf("%s", nom_hero);
    printf("\nVeuillez introduire le nom de la Princesse \n");
    scanf("%s", nom_princesse);
    printf("\nAppuyez sur la touche entrer pour revenir à la page d'accueil\n");
    fflush(stdin);//vide le buffer clavier, sans quoi, l'input de l'entrée au clavier reste bloquée à la valeur du nom de la proncesse
    getc(stdin);
    SetConsoleOutputCP(850); //Permet de revenir au Code ASCII pour éviter problème affichage labyrinthe
    EffaceEcran();
    FixePosCurseur(0,0);
}
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe])//Procédure faite pour faire le lien entre le nombre "choix de labyrinthe" et le labyrinthe choisi. Fonction non compatible avec le retour du tableau de valeur => Procédure
{
    int i,j;
    switch(choixLabyrinthe)
    {
    case 1:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe1[i][j]; //On parcourt toutes les cases du labyrinthe défini par le choix et on les mets dans le tableau "Labyrinthe Choisi" -> On récupère le labyrinthe choisi à la fin et on peut travailler avec
            }
        }
        break;
    case 2:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe2[i][j];
            }
        }

        break;
    case 3:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe3[i][j];
            }
        }

        break;
    case 4 :
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe4[i][j];
            }
        }

        break;
    case 5 :
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe5[i][j];
            }
        }

        break;
    case 6 :
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe6[i][j];
            }
        }

        break;
    case 7:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe7[i][j];
            }
        }

        break;
    case 8:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe8[i][j];
            }
        }

        break;
    case 9:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe9[i][j];
            }
        }

        break;
    case 10 :
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe10[i][j];
            }
        }

        break;
            case 11 :
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe11[i][j];
            }
        }

        break;
    }
}
void labyrintheUtiliseAffichage(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe], int labyrintheUtilise[HauteurLabyrinthe + 1][LargeurLabyrinthe])//HauteurLabyrinthe + 1 est effectué pour tenir compte de la ligne supplémentaire dans l'écran de jeu
{
    int i,j;
    for(j=0; j<LargeurLabyrinthe; j++)//Une ligne de 1 "inutile" pour le jeu, mais utile car nous créons la ligne supplémentaire se trouvant "à l'écran"
    {
        labyrintheUtilise[0][j]=1;
    }
    for(i=1; i<HauteurLabyrinthe+1; i++)
    {
        for(j=0; j<LargeurLabyrinthe; j++)
        {
            labyrintheUtilise[i][j]=labyrinthe[i-1][j];
        }
    }
}
void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    char table[HauteurLabyrinthe][LargeurLabyrinthe];
    int i,j; //definit un entier i ,et un entier utile dans le futur pour le parcours du tableau
    for(i=0; i<HauteurLabyrinthe; i++)
    {
        for(j=0; j<LargeurLabyrinthe; j++)
        {
            if(labyrinthe[i][j]==0) //On cherche les cases = 0 pour les remplacer dans un autre tableau par un espace
            {
                table[i][j]=' ';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==2) //On cherche la case = 2 pour la remplacer dans un autre tableau par le M (Minotaure)
            {
                table[i][j]='M';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==3) //On cherche la case = 3 pour la remplacer dans un autre tableau par le H (Heros)
            {
                table[i][j]='H';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==4) //On cherche la case = 4 pour la remplacer dans un autre tableau par le P (Princesse)
            {
                table[i][j]='P';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==1) //On remplace les cases = 1 pour les remplacer dans un autre tableau par le caractère 219
            {
                table[i][j]= 219;
                printf("%c", table[i][j]);
            }
        }
        //Chacun des remplacement est suivi par l'impression de son caractère à l'écran
        printf("\n");
    }
}

int choixDuLabyrinthe(int easteregg[1]) //permet de choisir ton labyrinthe + exception "easteregg"
{
    int choixLabyrinthe;
    printf("Labyrinthe 1:\n");
    affichageLabyrinthe(Labyrinthe1);//utilisation du code affichageLabyrinthe pour mettre à l'écran le labyrinthe 1
    getc(stdin);//Utilisé pour appuyer sur la touche ENTER
    printf("\nLabyrinthe 2:\n");
    affichageLabyrinthe(Labyrinthe2);
    getc(stdin);
    printf("\nLabyrinthe 3:\n");
    affichageLabyrinthe(Labyrinthe3);
    getc(stdin);
    printf("\nLabyrinthe 4:\n");
    affichageLabyrinthe(Labyrinthe4);
    getc(stdin);
    printf("\nLabyrinthe 5:\n");
    affichageLabyrinthe(Labyrinthe5);
    getc(stdin);
    printf("\nLabyrinthe 6:\n");
    affichageLabyrinthe(Labyrinthe6);
    getc(stdin);
    printf("\nLabyrinthe 7:\n");
    affichageLabyrinthe(Labyrinthe7);
    getc(stdin);
    printf("\nLabyrinthe 8:\n");
    affichageLabyrinthe(Labyrinthe8);
    getc(stdin);
    printf("\nLabyrinthe 9:\n");
    affichageLabyrinthe(Labyrinthe9);
    getc(stdin);
    printf("\nLabyrinthe 10:\n");
    affichageLabyrinthe(Labyrinthe10);
    getc(stdin);
    if(easteregg[0]==1)        //condition easteregg = 1, activation Labyrinthe 11
    {
        printf("\nLabyrinthe 11:\n");
        affichageLabyrinthe(Labyrinthe11);
        getc(stdin);
        do
        {
            printf("\nAvec quel labyrinthe souhaitez-vous jouer ?\n");
            scanf("%d", &choixLabyrinthe); //Permet de stocker pour le futur la valeur choixLabyrinthe
        }
        while(choixLabyrinthe< 1 || choixLabyrinthe>11);
    }
    else
    {
        do
        {
            printf("\nAvec quel labyrinthe souhaitez-vous jouer ?\n");
            scanf("%d", &choixLabyrinthe); //Permet de stocker pour le futur la valeur choixLabyrinthe
        }
        while(choixLabyrinthe< 1 || choixLabyrinthe>10);//empeche la valeur choixLabyrinthe d'être inférieure ou égale à 0 ou supérieure ou égale à 11
    }
    return choixLabyrinthe;
}
void introduction()
{
    SetConsoleOutputCP(1252);//utilisé pour gérer les caractères type "é", "è",... Cette référence nous a été fourni après une recherche sur le sujet (unique recherche externe pour le code
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps d'un homme et la tête d'un taureau.");
    printf("\nIl fut enfermé par le roi Minos dans le labyrinthe construit Dédale (au centre de la Crète).");
    printf("\nRégulièrement, des victimes étaient envoyées dans ce labyrinthe afin d'être sacrifiées par le Minotaure.");
    printf("\nThésée, fils d'Egée, accompagné d'autres victimes furent envoyées en Crête pour être sacrifié dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Thésée et sachant ce qui l'attendait dans le labyrinthe, lui remit une bobine de fil afin qu'il l'utilise pour retrouver la sortie du labyrinthe s'il ressort victorieux du combat contre le Minotaure.");
    printf("\nThésée parvient à tuer le Minotaure et à sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous êtes le héros (représentant Thésée) et vous devez chercher la princesse Ariane maintenue prisonnière à l'intérieur du labyrinthe.");
    printf("\nEn tant que joueur (le héros Thésée) vous déplacer le héros en utilisant les touches de déplacement pour essayer de rejoindre Ariane tout en évitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure à l'intérieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
    SetConsoleOutputCP(850); //utilisé pour revenir au code ASCII
}


void miseEnPlaceThesee(int posH[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]) //met en place les personnes dans le tableau avec les chiffres 2, 3 et 4
{
    int posX, posY;
    int conditionDeSortie = 1; //servira de valeur test dans le futur pour sortir de la boucle
    do
    {
        posX = rand()%HauteurLabyrinthe; //effectue une randomisation des nombres pour posX et posY
        posY = rand()%LargeurLabyrinthe;

        if(labyrinthe[posX][posY]==0)
        {
            labyrinthe[posX][posY] = 3; //met en place Thésée dans le labyrinthe et conserve en mémoire la position de celui-ci
            conditionDeSortie = 0;//mets la valeur à 0 pour sortir de la boucle
            posH[0] = posX;
            posH[1] = posY;
        };
    }
    while(conditionDeSortie);  //Continue à refaire les mêmes étapes tant que la valeur est à 1 (tant qu'on est pas passé dans le if ci-dessus)
}
void miseEnPlaceMinotaure(int posM[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    int posX, posY;
    int conditionDeSortie = 1; //servira de valeur test dans le futur pour sortir des 3 boucles futures
    do
    {
        posX = rand()%HauteurLabyrinthe; //effectue une randomisation des nombres pour posX et posY
        posY = rand()%LargeurLabyrinthe;

        if(labyrinthe[posX][posY]==0)
        {
            labyrinthe[posX][posY] = 2; //met en place le Minotaure dans le labyrinthe et conserve en mémoire la position de celui-ci
            conditionDeSortie = 0;//mets la valeur à 0 pour sortir de la boucle
            posM[0] = posX;
            posM[1] = posY;
        };
    }
    while(conditionDeSortie);
}
void miseEnPlacePrincess(int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    int conditionDeSortie = 1;
    int posX, posY;
    do
    {
        posX = rand()%HauteurLabyrinthe;
        posY = rand()%LargeurLabyrinthe;
        if(Labyrinthe[posX][posY]==0)
        {
            Labyrinthe[posX][posY] = 4; //mets en place la princesse dans le labyrinthe
            conditionDeSortie = 0;//mets la valeur à 0 pour sortir de la boucele
        };
    }
    while(conditionDeSortie);
}


void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int clauseDeSortie, int easteregg[1])
{
    //Code utilisé pour le jeu de difficulté simple où le minotaure est immobile
    int score = 10000;
    char touche;
    EffaceEcran();
    FixePosCurseur(0,0);//utilisé pour remettre le curseur à la position (0,0) car à la suite de l'EffaceEcran, on se retrouve à la position (1,1)
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL)); //on remet le random à 0 pour eviter que la ligne suivante donne à chaque fois le même résultat
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM, labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
    affichageLabyrinthe(labyrintheChoisi);
    printf("SCORE:%d\n", score);
    FixePosCurseur(23, 1);
    printf("Command for the Hero :");
    FixePosCurseur(23,2);
    printf("Up arrow to go up");
    FixePosCurseur(23,3);
    printf("Down arrow to go down");
    FixePosCurseur(23,4);
    printf("Left arrow to go left");
    FixePosCurseur(23,5);
    printf("Right arrow to go right");
    FixePosCurseur(23,6);
    printf("Enter to stop the game");
    FixePosCurseur(posH[1], posH[0]);
    clauseDeSortie=1; //la valeur de la clause de sortie est utilisée à la ligne suivante afin qu'elle continue à tourner jusqu'à ce que celle-ci soit nulle (condition de victoire/défaite)
    /*Dans la suite du code, le FixePosCurseur et le tableau n'ont pas l'air d'avoir de lien, mais celà est dû à l'inversion des axes
    X et Y dans notre compréhension*/

    while(clauseDeSortie)
    {
        if(kbhit())
        {
            touche=getch();
            if(touche == 72||touche ==80||touche ==77||touche ==75)
                /*  Cette partie du code permet un décompte sur la valeur du score de 10.000 par tranche de 100
                    une modification de l'affichage lorsque le score est en dessous de 1000
                    afin de permettre à l'utilisateur dans l'invité de cmd d'avoir un affichage visuel correcte du score
                */

            {
                if(score>0)
                {
                    score-=100;
                }
                FixePosCurseur(6,20);
                if(score<1000)
                {
                    printf(" ");
                }
                printf(" %d", score);
            }
            /// Touche flèche en haut actionnée
            if(touche == 72)    /// code ASCII de la touche flèche en haut
            {

                if(labyrintheChoisi[posH[0]-1][posH[1]]==0)
                {
                    if(labyrintheChoisi[posH[0]][posH[1]]==3)//permet de mettre à 0 la position de base du H dans le labyrinthe back-end, et permet de refranchir celle-ci dans le futur
                        labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]--;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]-1][posH[1]]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;//Est mise à 0 parce que c'est notre condition de boucle et qu'ainsi nous pourrons alors sortir de la boucle
                    if(score==100 && easteregg[0]!=1) //2 conditions sont necessaires pour activer le labyrinthe caché (score final = 100) (valeur initiale dans l'etat prévu pour son activation)
                        easteregg[0]=1; //la valeur dans le tableau est modifié par cette aciton

                }
                else if(labyrintheChoisi[posH[0]-1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }
            }

            /// Touche flèche en bas actionnée
            if(touche == 80)    /// code ASCII de la touche flèche en bas
            {
                if (labyrintheChoisi[posH[0]+1][posH[1]]==0)
                {
                    if(labyrintheChoisi[posH[0]][posH[1]]==3)
                        labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]++;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]+1][posH[1]]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                    if(score==100 && easteregg[0]!=1)
                        easteregg[0]=1;
                }
                else if(labyrintheChoisi[posH[0]+1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }
            }

            /// Touche flèche à gauche actionnée
            if(touche == 75)    /// code ASCII de la touche flèche à gauche
            {
                if(labyrintheChoisi[posH[0]][posH[1]-1]==0)
                {
                    if(labyrintheChoisi[posH[0]][posH[1]]==3)
                        labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]--;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]][posH[1]-1]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                    if(score==100 && easteregg[0]!=1)
                        easteregg[0]=1;
                }
                else if(labyrintheChoisi[posH[0]][posH[1]-1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


            }

            /// Touche flèche à droite actionnée

            if(touche == 77)    /// code ASCII de la touche flèche à droite
            {
                if(labyrintheChoisi[posH[0]][posH[1]+1]==0)
                {
                    if(labyrintheChoisi[posH[0]][posH[1]]==3)
                        labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]++;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]][posH[1]+1]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                    if(score==100 && easteregg[0]!=1)
                        easteregg[0]=1;
                }
                else if(labyrintheChoisi[posH[0]][posH[1]+1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


            }
            if(touche == 13)
            {
                EffaceEcran();
                break;
            }         /// code ASCII de la touche enter

            FixePosCurseur(posH[1],posH[0]);


        }

    }

}


void jeuTWO(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int clauseDeSortie)
{
    int score = 0;
    char touche;
    EffaceEcran();
    FixePosCurseur(0,0);
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL));
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM,labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
    affichageLabyrinthe(labyrintheChoisi);
    printf("SCORE: %d\n", score);
    FixePosCurseur(23, 1);
    printf("Command for the Hero :");
    FixePosCurseur(23,2);
    printf("Up arrow to go up");
    FixePosCurseur(23,3);
    printf("Down arrow to go down");
    FixePosCurseur(23,4);
    printf("Left arrow to go left");
    FixePosCurseur(23,5);
    printf("Right arrow to go right");
    FixePosCurseur(23, 7);
    printf("Command for the Minotaure :");
    FixePosCurseur(23,8);
    printf("Z to go up");
    FixePosCurseur(23,9);
    printf("S to go down");
    FixePosCurseur(23,10);
    printf("Q to go left");
    FixePosCurseur(23,11);
    printf("D to go right");
    FixePosCurseur(23,13);
    printf("Enter to stop the game");
    clauseDeSortie=1;

    while(clauseDeSortie)
    {
        if(kbhit())
        {
            touche=getch();
            if(touche == 72||touche ==80||touche ==77||touche ==75)
            {
                score+=100;
                FixePosCurseur(6, 20);
                printf(" %d", score);
            }
            /// Touche flèche en haut actionnée
            if(touche == 72)    /// code ASCII de la touche flèche en haut
            {

                if(labyrintheChoisi[posH[0]-1][posH[1]]==0)
                {
                    labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]--;
                    labyrintheChoisi[posH[0]][posH[1]]=3;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]-1][posH[1]]==2)//gestion de la sortie du jeu pour le héros
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheChoisi[posH[0]-1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }

            }

            /// Touche flèche en bas actionnée
            if(touche == 80)    /// code ASCII de la touche flèche en bas
            {
                if (labyrintheChoisi[posH[0]+1][posH[1]]==0)
                {
                    labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]++;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheChoisi[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]+1][posH[1]]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheChoisi[posH[0]+1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }

            }

            /// Touche flèche à gauche actionnée
            if(touche == 75)    /// code ASCII de la touche flèche à gauche
            {
                if(labyrintheChoisi[posH[0]][posH[1]-1]==0)
                {
                    labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]--;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheChoisi[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]][posH[1]-1]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheChoisi[posH[0]][posH[1]-1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


            }

            /// Touche flèche à droite actionnée

            if(touche == 77)    /// code ASCII de la touche flèche à droite
            {
                if(labyrintheChoisi[posH[0]][posH[1]+1]==0)
                {
                    labyrintheChoisi[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]++;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheChoisi[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheChoisi[posH[0]][posH[1]+1]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheChoisi[posH[0]][posH[1]+1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }



            }

            /// Touche 'z' actionnée
            if(touche == 'z')    /// Touche 'z' direction vers le haut
            {

                if(labyrintheChoisi[posM[0]-1][posM[1]]==0)
                {
                    labyrintheChoisi[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[0]--;
                    labyrintheChoisi[posM[0]][posM[1]]=2;
                    FixePosCurseur(posM[1],posM[0]);
                    printf("M");
                }
                else if(labyrintheChoisi[posM[0]-1][posM[1]]==3 || labyrintheChoisi[posM[0]-1][posM[1]]==4)//gestion de la fin de partie pour le minotaure
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;

                }


            }

            /// Touche 's' actionnée
            if(touche == 's')    /// Touche 's' direction vers le bas
            {
                if (labyrintheChoisi[posM[0]+1][posM[1]]==0)
                {
                    labyrintheChoisi[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[0]++;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheChoisi[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheChoisi[posM[0]+1][posM[1]]==3 || labyrintheChoisi[posM[0]+1][posM[1]]==4)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }

            }

            /// Touche 'q' actionnée
            if(touche == 'q')    /// Touche 'q' direction à gauche
            {
                if(labyrintheChoisi[posM[0]][posM[1]-1]==0)
                {
                    labyrintheChoisi[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[1]--;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheChoisi[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheChoisi[posM[0]][posM[1]-1]==3||labyrintheChoisi[posM[0]][posM[1]-1]==4)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }

            }

            /// Touche 'd' actionnée

            if(touche == 'd')    /// Touche 'd' direction à droite
            {
                if(labyrintheChoisi[posM[0]][posM[1]+1]==0)
                {

                    labyrintheChoisi[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[1]++;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheChoisi[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheChoisi[posM[0]][posM[1]+1]==3||labyrintheChoisi[posM[0]][posM[1]+1]==4)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
            }
            if(touche == 13)
            {
                EffaceEcran();
                break;
            }         /// code ASCII de la touche enter
        }
    }
}
