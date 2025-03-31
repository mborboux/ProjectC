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
    char nom_hero[15]= "Th�s�e";
    char nom_princesse[15] = "Arianne";
    char choix;
    int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe];
    int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe];
    char touche;
    int posH[2];
    int posM[2];

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
            printf("\nVeuillez introduire le nom du H�ro \n");
            scanf("%s", nom_hero);
            printf("\nVeuillez introduire le nom de la Princesse \n");
            scanf("%s", nom_princesse);
            printf("%s, %s", nom_hero, nom_princesse);
            printf("\nAppuyez sur la touche entrer pour revenir � la page d'accueil");
            getchar();
            getchar();

        break;

        case '3':

            choixLabyrinthe=choixDuLabyrinthe();

        break;

        case '4':
            //possible deplacement du P & M suite � la traduction du labyrinthe en affichage
            EffaceEcran();
            printf("\b"); //backspace effectu� suite � l'apparition d'un espace parasite sur l'�cran
            selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
            srand(time(NULL));
            miseEnPlacePerso(posH, posM,labyrintheChoisi);
            labyrintheUtiliseAffichage(labyrintheChoisi,labyrintheManifeste);//labyrinthe manifeste est utilis� pour avoir un parall�lisme entre l'�cran de jeu et l'�cran en back-end
            affichageLabyrinthe(labyrintheChoisi);
            posH[0]++;
            FixePosCurseur(posH[1], posH[0]);

                while(1)                 /// Boucle infinie o� on attend l'action sur une
                             /// des touches de d�placement
    {
        if(kbhit())          /// Si appuie sur une touche ==> la fonction kbhit
                             /// (KeyBoard HIT) renvoie vraie si une touche est
                             /// enfonc�e
        {
            touche=getch();  /// On stocke la touche dans la variable touche
                             /// uniquement si une touche est enfonc�e ==> ceci
                             /// permet de ne pas bloquer inutilement
                             /// l'exectution du programme (et donc faire autres
                             /// choses comme g�rer le d�placement du minotaure
                             /// ou g�rer le score par exemple)

            /// Touche fl�che en haut actionn�e
            if(touche == 72)    /// code ASCII de la touche fl�che en haut
            {

                if(labyrintheManifeste[posH[0]-1][posH[1]]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)
                        labyrintheManifeste[posH[0]][posH[1]]=0;
                FixePosCurseur(posH[1],posH[0]);
                printf(" ");
                posH[0]--;
                FixePosCurseur(posH[1],posH[0]);
                printf("H");
                    /// faire ce qui doit �tre fait quand on veut monter en haut
                }
            }

            /// Touche fl�che en bas actionn�e
            if(touche == 80)    /// code ASCII de la touche fl�che en bas
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
                    /// faire ce qui doit �tre fait quand on veut descendre en
                    /// bas
            }

            /// Touche fl�che � gauche actionn�e
            if(touche == 75)    /// code ASCII de la touche fl�che � gauche
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


                    /// faire ce qui doit �tre fait quand on veut aller � gauche
            }

            /// Touche fl�che � droite actionn�e

            if(touche == 77)    /// code ASCII de la touche fl�che � droite
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


                    /// faire ce qui doit �tre fait quand on veut aller � droite
            }
            if(touche == 13) break;         /// code ASCII de la touche enter

	/// ensuite on r�p�te le processus pour toutes les touches � g�rer
        FixePosCurseur(posH[1],posH[0]);


        }  /// Fin de la condition lorsque l'on appuie sur une touche

        /// Ici vous faites tous les traitements n�cessaires : gestion du score,
        ///  du d�placement du minotaure, de la rencontre Th�s�e et Ariane ou
        /// Th�s�e et le Minotaure (apr�s d�placement de Th�s�e ou du minotaure)

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
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe])//Proc�dure faite pour faire le lien entre le nombre "choix de labyrinthe" et le labyrinthe choisi. Fonction non compatible avec le retour du tableau de valeur => Proc�dure
{
    int i,j;
    switch(choixLabyrinthe){
    case 1:
        for(i=0; i<HauteurLabyrinthe; i++)
        {
            for(j=0; j< LargeurLabyrinthe; j++)
            {
                labyrintheChoisi[i][j] = Labyrinthe1[i][j]; //On parcourt toutes les cases du labyrinthe d�fini par le choix et on les mets dans le tableau "Labyrinthe Choisi" -> On r�cup�re le labyrinthe choisi � la fin et on peut travailler avec
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
void labyrintheUtiliseAffichage(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe], int labyrintheUtilise[HauteurLabyrinthe + 1][LargeurLabyrinthe])//HauteurLabyrinthe + 1 est effectu� pour tenir compte de la ligne suppl�mentaire dans l'�cran de jeu
{
    int i,j;
    for(j=0; j<LargeurLabyrinthe; j++)//Une ligne de 1 "inutile" pour le jeu, mais utile car nous cr�ons la ligne suppl�mentaire se trouvant "� l'�cran"
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
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps d�un homme et la t�te d�un taureau.");
    printf("\nIl fut enferm� par le roi Minos dans le labyrinthe construit D�dale (au centre de la Cr�te).");
    printf("\nR�guli�rement, des victimes �taient envoy�es dans ce labyrinthe afin d��tre sacrifi�es par le Minotaure.");
    printf("\nTh�s�e, fils d�Eg�e, accompagn� d�autres victimes furent envoy�es en Cr�te pour �tre sacrifi� dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Th�s�e et sachant ce qui l�attendait dans le labyrinthe, lui remit une bobine de fil afin qu�il l�utilise pour retrouver la sortie du labyrinthe s�il ressort victorieux du combat contre le Minotaure.");
    printf("\nTh�s�e parvient � tuer le Minotaure et � sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous �tes le h�ros (repr�sentant Th�s�e) le et vous devez chercher la princesse Ariane maintenue prisonni�re � l�int�rieur du labyrinthe.");
    printf("\nEn tant que joueur (le h�ros Th�s�e) vous d�placer le h�ros en utilisant les touches de d�placement pour essayer de rejoindre Ariane tout en �vitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure � l�int�rieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
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
