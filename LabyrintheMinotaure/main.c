/*

Jeu Fil d'Arianne
Programmation C
ITSCM 2024-2025

Maxime Borboux
Marwane Tahiri

En remerciant Monsieur Jaghou pour le challenge que ce jeu nous a apport�
en nous permettant de nous exercer sur les mati�res apprises en cours, ainsi que les proc�dures fournies.


*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Temps.h"
#include "TableauxLabyrinthes.h" //ici sont inclus les diff�rents codes fournis par Monsieur Jaghou
#include "Affichage.h"
#include <windows.h> //utilis� avec le setconsoleoutputCP pour g�rer les caract�res sp�ciaux

void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); //Proc�dure qui traduis le labyrinthe sous forme d'affichage
void viderBufferClavier();
int choixDuLabyrinthe(); // Fonction qui retourne sous forme d'entier le choix du labyrinthe
void introduction(); // Procedure qui nous donne l'introduction du jeu
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]); //Procedure qui permet de choisir 1 des 10 labyrinthe
void miseEnPlaceThesee(int posH[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); //Procedure qui mets en place, dans le labyrinthe back-end, le personnage
void miseEnPlaceMinotaure(int posM[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void miseEnPlacePrincess(int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void labyrintheUtiliseAffichage(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe], int labyrintheUtilise[HauteurLabyrinthe+1][LargeurLabyrinthe]); //Proc�dure qui permet d'afficher le labyrinthe avec un saut � la ligne
void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe],int clauseDeSortie); //Proc�dure qui permet le premier jeu avec le deplacement unique du h�ro
void jeuTWO(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe], int clauseDeSortie); //Proc�dure qui permet le second jeu avec le deplacement du h�ro et du minotaure

int main()
{
    SetConsoleOutputCP(65001);//utilis� pour g�rer les caract�res type "�", "�",... Cette r�f�rence nous a �t� fourni apr�s une recherche sur le sujet (unique recherche externe pour le code)
    int choixLabyrinthe=1; //valeur init�e � 1 pour selectionner le premier labyrinthe, pourra �tre chang�e dans le futur
    char nom_hero[15]= "Th�s�e";
    char nom_princesse[15] = "Arianne";
    char choix; //caract�re utilis� pour effectu� le choix dans le menu
    int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]; //labyrinthe utilis� pour effectu� le transfert du contenu du labyrinthe selectionn� sur base du nombre choixLabyrinthe
    int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe];//Labyrinthe back-end utilis� pour manifester les d�placement sur la labyrinthe affich�
    int posH[2]; //position en X et Y de Th�s�e
    int posM[2]; //position en X et Y du Minotaure
    int clauseDeSortie = 1; //astuce utilis�e pour signal� si le jeu fini ou non

    do
    {
        printf("\n===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n4. Jeu difficulte 1\n5. Jeu difficulte 2\n6. Quitter le jeu\n");
        choix = getch();//permet d'�tablir un choix sans la commande entr�e

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

            jeuONE(choixLabyrinthe, labyrintheChoisi, posH, posM, labyrintheManifeste, clauseDeSortie);

            break;

        case '5':

            jeuTWO(choixLabyrinthe, labyrintheChoisi, posH, posM, labyrintheManifeste, clauseDeSortie);

            break;


        case '6':

            break;
        }
    }
    while (choix == '1' || choix == '2' || choix == '3' || choix == '4' || choix == '5');

    return 0;
}
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe])//Proc�dure faite pour faire le lien entre le nombre "choix de labyrinthe" et le labyrinthe choisi. Fonction non compatible avec le retour du tableau de valeur => Proc�dure
{
    int i,j;
    switch(choixLabyrinthe)
    {
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
            else if (labyrinthe[i][j]==1) //On remplace les cases = 1 pour les remplacer dans un autre tableau par le caract�re 219
            {
                table[i][j]= 219;
                printf("%c", table[i][j]);
            }
        }
        //Chacun des remplacement est suivi par l'impression de son caract�re � l'�cran
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
    affichageLabyrinthe(Labyrinthe1);//utilisation du code affichageLabyrinthe pour mettre � l'�cran le labyrinthe 1
    getc(stdin);//Utilis� pour appuyer sur la touche ENTER
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
    do
    {
        printf("\nAvec quel labyrinthe souhaitez-vous jouer ?\n");
        scanf("%d", &choixLabyrinthe); //Permet de stocker pour le futur la valeur choixLabyrinthe
    }
    while(choixLabyrinthe< 0 || choixLabyrinthe>11); //empeche la valeur choixLabyrinthe d'�tre inf�rieure ou �gale � 0 ou sup�rieure ou �gale � 11
    return choixLabyrinthe;
}
void introduction()
{
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps d'un homme et la t�te d'un taureau.");
    printf("\nIl fut enferm� par le roi Minos dans le labyrinthe construit D�dale (au centre de la Cr�te).");
    printf("\nR�guli�rement, des victimes �taient envoy�es dans ce labyrinthe afin d'�tre sacrifi�es par le Minotaure.");
    printf("\nTh�s�e, fils d'Eg�e, accompagn� d'autres victimes furent envoy�es en Cr�te pour �tre sacrifi� dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Th�s�e et sachant ce qui l'attendait dans le labyrinthe, lui remit une bobine de fil afin qu'il l'utilise pour retrouver la sortie du labyrinthe s'il ressort victorieux du combat contre le Minotaure.");
    printf("\nTh�s�e parvient � tuer le Minotaure et � sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous �tes le h�ros (repr�sentant Th�s�e) et vous devez chercher la princesse Ariane maintenue prisonni�re � l'int�rieur du labyrinthe.");
    printf("\nEn tant que joueur (le h�ros Th�s�e) vous d�placer le h�ros en utilisant les touches de d�placement pour essayer de rejoindre Ariane tout en �vitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure � l'int�rieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
}


void miseEnPlaceThesee(int posH[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]) //met en place les personnes dans le tableau avec les chiffres 2, 3 et 4
{
    int posX, posY;
    int test = 0; //servira de valeur test dans le futur pour sortir des 3 boucles futures
    do
    {
        posX = rand()%HauteurLabyrinthe; //effectue une randomisation des nombres pour posX et posY
        posY = rand()%LargeurLabyrinthe;

        if(labyrinthe[posX][posY]==0)
        {
            labyrinthe[posX][posY] = 3; //met en place Th�s�e dans le labyrinthe et conserve en m�moire la position de celui-ci
            test = 1;//mets la valeur � 1 pour sortir de la boucle
            posH[0] = posX;
            posH[1] = posY;
        };
    }while(test == 0); //Continue � refaire les m�mes �tapes tant que la valeur est � 0 (tant qu'on est pas pass� dans le if ci-dessus)
}
void miseEnPlaceMinotaure(int posM[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    int posX, posY;
    int test = 0; //servira de valeur test dans le futur pour sortir des 3 boucles futures
    do
    {
        posX = rand()%HauteurLabyrinthe; //effectue une randomisation des nombres pour posX et posY
        posY = rand()%LargeurLabyrinthe;

        if(labyrinthe[posX][posY]==0)
        {
            labyrinthe[posX][posY] = 2; //met en place le Minotaure dans le labyrinthe et conserve en m�moire la position de celui-ci
            test = 1;//mets la valeur � 1 pour sortir de la boucle
            posM[0] = posX;
            posM[1] = posY;
        };
    }while(test == 0);
}
void miseEnPlacePrincess(int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    int test = 0;
    int posX, posY;
    do
    {
        posX = rand()%HauteurLabyrinthe;
        posY = rand()%LargeurLabyrinthe;
        if(Labyrinthe[posX][posY]==0)
        {
            Labyrinthe[posX][posY] = 4; //mets en place la princesse dans le labyrinthe
            test = 1;//mets la valeur � 2 pour sortir de la boucele
        };
    }while(test == 0);
}


void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe], int clauseDeSortie)
{
    //Code utilis� pour le jeu de difficult� simple o� le minotaure est immobile
    int score = 10000;
    char touche;
    EffaceEcran();
    printf("\b"); //backspace effectu� suite � l'apparition d'un espace parasite sur l'�cran d� � la fonction EffaceEcran
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL)); //on remet le random � 0 pour eviter que la ligne suivante donne � chaque fois le m�me r�sultat
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM, labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
    labyrintheUtiliseAffichage(labyrintheChoisi,labyrintheManifeste);//labyrinthe manifeste est utilis� pour avoir un parall�lisme entre l'�cran de jeu et l'�cran en back-end
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
    posH[0]++; //On incr�mente la position de H de 1 pour avoir le parall�lisme entre labyrinthe back-end et affichage
    FixePosCurseur(posH[1], posH[0]);
    clauseDeSortie=1; //la valeur de la clause de sortie est utilis�e � la ligne suivante afin qu'elle continue � tourner jusqu'� ce que celle-ci soit nulle (condition de victoire/d�faite)


    while(clauseDeSortie)
    {
        if(kbhit())
        {
            touche=getch();
            if(touche == 72||touche ==80||touche ==77||touche ==75)
            {
                if(score>0)
                {
                    score-=100;
                }
                FixePosCurseur(7, 21);
                printf("%d", score);

            }
            /// Touche fl�che en haut actionn�e
            if(touche == 72)    /// code ASCII de la touche fl�che en haut
            {

                if(labyrintheManifeste[posH[0]-1][posH[1]]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)//permet de mettre � 0 la position de base du H dans le labyrinthe back-end, et permet de refranchir celle-ci dans le futur
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
                    clauseDeSortie=0;//Est mise � 0 parce que c'est notre condition de boucle et qu'ainsi nous pourrons alors sortir de la boucle
                }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
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
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }
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
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


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
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==2)
                {
                    EffaceEcran();
                    printf("Game Over");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==4)
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


void jeuTWO(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe], int clauseDeSortie)
{
    //possible deplacement du P & M suite � la traduction du labyrinthe en affichage
    int score = 0;
    char touche;
    EffaceEcran();
    printf("\b"); //backspace effectu� suite � l'apparition d'un espace parasite sur l'�cran
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL));
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM,labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
    labyrintheUtiliseAffichage(labyrintheChoisi,labyrintheManifeste);//labyrinthe manifeste est utilis� pour avoir un parall�lisme entre l'�cran de jeu et l'�cran en back-end
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
    posH[0]++;
    posM[0]++;
    FixePosCurseur(posH[1], posH[0]);
    clauseDeSortie=1;

    while(clauseDeSortie)
    {
        if(kbhit())
        {
            touche=getch();
            if(touche == 72||touche ==80||touche ==77||touche ==75)
            {
                score+=100;
                FixePosCurseur(7, 21);
                printf("%d", score);
            }
            /// Touche fl�che en haut actionn�e
            if(touche == 72)    /// code ASCII de la touche fl�che en haut
            {

                if(labyrintheManifeste[posH[0]-1][posH[1]]==0)
                {
                    labyrintheManifeste[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]--;
                    labyrintheManifeste[posH[0]][posH[1]]=3;
                    FixePosCurseur(posH[1],posH[0]);
                    printf("H");
                }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==2)//gestion de la sortie du jeu pour le h�ros
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }

            }

            /// Touche fl�che en bas actionn�e
            if(touche == 80)    /// code ASCII de la touche fl�che en bas
            {
                if (labyrintheManifeste[posH[0]+1][posH[1]]==0)
                {
                    labyrintheManifeste[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[0]++;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheManifeste[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }

            }

            /// Touche fl�che � gauche actionn�e
            if(touche == 75)    /// code ASCII de la touche fl�che � gauche
            {
                if(labyrintheManifeste[posH[0]][posH[1]-1]==0)
                {
                    labyrintheManifeste[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]--;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheManifeste[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


            }

            /// Touche fl�che � droite actionn�e

            if(touche == 77)    /// code ASCII de la touche fl�che � droite
            {
                if(labyrintheManifeste[posH[0]][posH[1]+1]==0)
                {
                    labyrintheManifeste[posH[0]][posH[1]]=0;
                    FixePosCurseur(posH[1],posH[0]);
                    printf(" ");
                    posH[1]++;
                    FixePosCurseur(posH[1],posH[0]);
                    labyrintheManifeste[posH[0]][posH[1]]=3;
                    printf("H");
                }
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==2)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]][posH[1]+1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }



            }

            /// Touche 'z' actionn�e
            if(touche == 'z')    /// Touche 'z' direction vers le haut
            {

                if(labyrintheManifeste[posM[0]-1][posM[1]]==0)
                {
                    labyrintheManifeste[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[0]--;
                    labyrintheManifeste[posM[0]][posM[1]]=2;
                    FixePosCurseur(posM[1],posM[0]);
                    printf("M");
                }
                else if(labyrintheManifeste[posM[0]-1][posM[1]]==3 || labyrintheManifeste[posM[0]-1][posM[1]]==4)//gestion de la fin de partie pour le minotaure
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;

                }


            }

            /// Touche 's' actionn�e
            if(touche == 's')    /// Touche 's' direction vers le bas
            {
                if (labyrintheManifeste[posM[0]+1][posM[1]]==0)
                {
                    labyrintheManifeste[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[0]++;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheManifeste[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheManifeste[posM[0]+1][posM[1]]==3 || labyrintheManifeste[posM[0]+1][posM[1]]==4)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }

            }

            /// Touche 'q' actionn�e
            if(touche == 'q')    /// Touche 'q' direction � gauche
            {
                if(labyrintheManifeste[posM[0]][posM[1]-1]==0)
                {
                    labyrintheManifeste[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[1]--;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheManifeste[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheManifeste[posM[0]][posM[1]-1]==3||labyrintheManifeste[posM[0]][posM[1]-1]==4)
                {
                    EffaceEcran();
                    printf("Game Over - Minotaur wins");
                    clauseDeSortie=0;
                }

            }

            /// Touche 'd' actionn�e

            if(touche == 'd')    /// Touche 'd' direction � droite
            {
                if(labyrintheManifeste[posM[0]][posM[1]+1]==0)
                {

                    labyrintheManifeste[posM[0]][posM[1]]=0;
                    FixePosCurseur(posM[1],posM[0]);
                    printf(" ");
                    posM[1]++;
                    FixePosCurseur(posM[1],posM[0]);
                    labyrintheManifeste[posM[0]][posM[1]]=2;
                    printf("M");
                }
                else if(labyrintheManifeste[posM[0]][posM[1]+1]==3||labyrintheManifeste[posM[0]][posM[1]+1]==4)
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
            FixePosCurseur(posH[1],posH[0]);
        }
    }
}
