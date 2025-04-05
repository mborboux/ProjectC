#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Temps.h"
#include "TableauxLabyrinthes.h"
#include "Affichage.h"

void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void viderBufferClavier();
int choixDuLabyrinthe();
void introduction();
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]);
void miseEnPlacePerso(int posH[2], int posM[2], int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void labyrintheUtiliseAffichage(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe], int labyrintheUtilise[HauteurLabyrinthe+1][LargeurLabyrinthe]);
int main()
{
    int choixLabyrinthe=1;
    char nom_hero[15]= "Thésée";
    char nom_princesse[15] = "Arianne";
    char choix;
    int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe];
    int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe];
    char touche;
    int posH[2];
    int posM[2];
    int score = 10000;

    do {
        printf("===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n4. Jeu difficulte 1\n5. Jeu difficulte 2\n6. Jeu difficulte 3\n7. Quitter le jeu\n");
    choix = getch();

    switch (choix)
    {
        case '1' :
            introduction();
            printf("\nAppuyez sur Enter pour revenir au menu\n");
            getc(stdin);

        break;

        case '2':
            printf("\nVeuillez introduire le nom du Héro \n");
            scanf("%s", nom_hero);
            printf("\nVeuillez introduire le nom de la Princesse \n");
            scanf("%s", nom_princesse);
            printf("%s, %s", nom_hero, nom_princesse);
            printf("\nAppuyez sur la touche entrer pour revenir à la page d'accueil");
            getchar();
            getchar();

        break;

        case '3':

            choixLabyrinthe=choixDuLabyrinthe();

        break;

        case '4':
            //possible deplacement du P & M suite à la traduction du labyrinthe en affichage
            EffaceEcran();
            printf("\b"); //backspace effectué suite à l'apparition d'un espace parasite sur l'écran
            selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
            srand(time(NULL));
            miseEnPlacePerso(posH, posM,labyrintheChoisi);
            labyrintheUtiliseAffichage(labyrintheChoisi,labyrintheManifeste);//labyrinthe manifeste est utilisé pour avoir un parallélisme entre l'écran de jeu et l'écran en back-end
            affichageLabyrinthe(labyrintheChoisi);
            printf("SCORE: \n");
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
            posH[0]++;
            FixePosCurseur(posH[1], posH[0]);


                while(1)                 /// Boucle infinie où on attend l'action sur une
                             /// des touches de déplacement
    {
        if(kbhit())          /// Si appuie sur une touche ==> la fonction kbhit
                             /// (KeyBoard HIT) renvoie vraie si une touche est
                             /// enfoncée
        {
            touche=getch();  /// On stocke la touche dans la variable touche
                             /// uniquement si une touche est enfoncée ==> ceci
                             /// permet de ne pas bloquer inutilement
                             /// l'exectution du programme (et donc faire autres
                             /// choses comme gérer le déplacement du minotaure
                             /// ou gérer le score par exemple)
            if(touche == 72||touche ==80||touche ==77||touche ==75)
            {
                if(score>0)
                {
                    score-=100;
                }
                FixePosCurseur(7, 21);
                printf("%d", score);

            }
            /// Touche flèche en haut actionnée
            if(touche == 72)    /// code ASCII de la touche flèche en haut
            {

                if(labyrintheManifeste[posH[0]-1][posH[1]]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)//permet de mettre à 0 la position de base du H, et permet de refranchir celle-ci dans le futur
                        labyrintheManifeste[posH[0]][posH[1]]=0;
                FixePosCurseur(posH[1],posH[0]);
                printf(" ");
                posH[0]--;
                FixePosCurseur(posH[1],posH[0]);
                printf("H");
                }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==2)
                    {
                        EffaceEcran();
                        printf("Game Over");
                    }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==4)
                    {
                        EffaceEcran();
                        printf("YOU WIN !\nYOUR SCORE: %d", score);
                    }

                    /// faire ce qui doit être fait quand on veut monter en haut

            }

            /// Touche flèche en bas actionnée
            if(touche == 80)    /// code ASCII de la touche flèche en bas
            {
                if (labyrintheManifeste[posH[0]+1][posH[1]]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)
                        labyrintheManifeste[posH[0]][posH[1]]=0;
                FixePosCurseur(posH[1],posH[0]);
                printf(" ");
                posH[0]++;
                FixePosCurseur(posH[1],posH[0]);
                printf("H");
                }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==2)
                    {
                        EffaceEcran();
                        printf("Game Over");
                    }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==4)
                    {
                        EffaceEcran();
                        printf("YOU WIN !\nYOUR SCORE: %d", score);
                    }

                    /// faire ce qui doit être fait quand on veut descendre en
                    /// bas
            }

            /// Touche flèche à gauche actionnée
            if(touche == 75)    /// code ASCII de la touche flèche à gauche
            {
                if(labyrintheManifeste[posH[0]][posH[1]-1]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)
                        labyrintheManifeste[posH[0]][posH[1]]=0;
                FixePosCurseur(posH[1],posH[0]);
                printf(" ");
                posH[1]--;
                FixePosCurseur(posH[1],posH[0]);
                printf("H");
                }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==2)
                    {
                        EffaceEcran();
                        printf("Game Over");
                    }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==4)
                    {
                        EffaceEcran();
                        printf("YOU WIN !\nYOUR SCORE: %d", score);
                    }


                    /// faire ce qui doit être fait quand on veut aller à gauche
            }

            /// Touche flèche à droite actionnée

            if(touche == 77)    /// code ASCII de la touche flèche à droite
            {
                if(labyrintheManifeste[posH[0]][posH[1]+1]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)
                        labyrintheManifeste[posH[0]][posH[1]]=0;
                FixePosCurseur(posH[1],posH[0]);
                printf(" ");
                posH[1]++;
                FixePosCurseur(posH[1],posH[0]);
                printf("H");
                }
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==2)
                    {
                        EffaceEcran();
                        printf("Game Over");
                    }
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==4)
                    {
                        EffaceEcran();
                        printf("YOU WIN !\nYOUR SCORE: %d", score);
                    }


                    /// faire ce qui doit être fait quand on veut aller à droite
            }
            if(touche == 13)
            {
                EffaceEcran();
                break;
            }         /// code ASCII de la touche enter

	/// ensuite on répéte le processus pour toutes les touches à gérer
        FixePosCurseur(posH[1],posH[0]);


        }  /// Fin de la condition lorsque l'on appuie sur une touche

        /// Ici vous faites tous les traitements nécessaires : gestion du score,
        ///  du déplacement du minotaure, de la rencontre Thésée et Ariane ou
        /// Thésée et le Minotaure (après déplacement de Thésée ou du minotaure)

    }


        break;

        case '5':


        break;

        case '6':


        break;

        case '7':

        break;
    }
    }while (choix == '1' || choix == '2' || choix == '3' || choix == '4' || choix == '5' || choix == '6');

    return 0;
}
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe])//Procédure faite pour faire le lien entre le nombre "choix de labyrinthe" et le labyrinthe choisi. Fonction non compatible avec le retour du tableau de valeur => Procédure
{
    int i,j;
    switch(choixLabyrinthe){
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
        for(j=0; j<LargeurLabyrinthe;j++)
        {
            labyrintheUtilise[i][j]=labyrinthe[i-1][j];
        }
    }
}
void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    char table[HauteurLabyrinthe][LargeurLabyrinthe];
    int i,j; //definit un entier i ,et un entier utile dans le futur pour le parcours du tableau
    for(i=0; i<HauteurLabyrinthe;i++)
    {
        for(j=0; j<LargeurLabyrinthe;j++)
        {
            if(labyrinthe[i][j]==0) //On cherche les case = 0 pour les remplacer dans un autre tableau par un espace
            {
                table[i][j]=' ';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==2)
            {
                table[i][j]='M';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==3)
            {
                table[i][j]='H';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==4)
            {
                table[i][j]='P';
                printf("%c", table[i][j]);
            }
            else if (labyrinthe[i][j]==1)
            {
                table[i][j]= 219;
                printf("%c", table[i][j]);
            }
        }
        printf("\n");
    }
}
void viderBufferClavier()
{
    int c;
    do
    {
        c=getch();
    }
    while (c!='\n' && c!=EOF);
}
int choixDuLabyrinthe()
{
    int choixLabyrinthe;
    printf("Labyrinthe 1:\n");
    affichageLabyrinthe(Labyrinthe1);
    getc(stdin);
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
    do{
          printf("\nAvec quel labyrinthe souhaitez-vous jouer ?\n");
          scanf("%d", &choixLabyrinthe);
    }while(choixLabyrinthe< 0 || choixLabyrinthe>11);
    return choixLabyrinthe;
}
void introduction()
{
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps dun homme et la tête dun taureau.");
    printf("\nIl fut enfermé par le roi Minos dans le labyrinthe construit Dédale (au centre de la Crète).");
    printf("\nRégulièrement, des victimes étaient envoyées dans ce labyrinthe afin dêtre sacrifiées par le Minotaure.");
    printf("\nThésée, fils dEgée, accompagné dautres victimes furent envoyées en Crête pour être sacrifié dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Thésée et sachant ce qui lattendait dans le labyrinthe, lui remit une bobine de fil afin quil lutilise pour retrouver la sortie du labyrinthe sil ressort victorieux du combat contre le Minotaure.");
    printf("\nThésée parvient à tuer le Minotaure et à sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous êtes le héros (représentant Thésée) le et vous devez chercher la princesse Ariane maintenue prisonnière à lintérieur du labyrinthe.");
    printf("\nEn tant que joueur (le héros Thésée) vous déplacer le héros en utilisant les touches de déplacement pour essayer de rejoindre Ariane tout en évitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure à lintérieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
}


void miseEnPlacePerso(int posH[2], int posM[2], int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    int posX, posY;
    int test = 0;
    do
    {
        posX = rand()%HauteurLabyrinthe;
        posY = rand()%LargeurLabyrinthe;

        if(Labyrinthe[posX][posY]==0)
        {
            Labyrinthe[posX][posY] = 3;
            test = 1;
            posH[0] = posX;
            posH[1] = posY;
        };
    }while(test == 0);
    do
    {
        posX = rand()%HauteurLabyrinthe;
        posY = rand()%LargeurLabyrinthe;
        if(Labyrinthe[posX][posY]==0)
        {
            Labyrinthe[posX][posY] = 4;
            test = 2;
            //printf("Position P : %d %d\n", posX, posY);
        };
    }while(test == 1);
     do
    {
        posX = rand()%HauteurLabyrinthe;
        posY = rand()%LargeurLabyrinthe;
        if(Labyrinthe[posX][posY]==0)
        {
            Labyrinthe[posX][posY] = 2;
            test = 3;
            posM[0] = posX;
            posM[1] = posY;
            //printf("Position M : %d %d\n", posX, posY);
        };
    }while(test == 2);
}
