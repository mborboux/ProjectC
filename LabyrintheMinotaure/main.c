/*

Jeu Fil d'Arianne
Programmation C
ITSCM 2024-2025

Maxime Borboux
Marwane Tahiri

En remerciant Monsieur Jaghou pour le challenge que ce jeu nous a apporté
en nous permettant de nous exercer sur les matières apprises en cours, ainsi que les procédures fournies.


*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Temps.h"
#include "TableauxLabyrinthes.h" //ici sont inclus les différents codes fournis par Monsieur Jaghou
#include "Affichage.h"
#include <windows.h> //utilisé avec le setconsoleoutputCP pour gérer les caractères spéciaux

void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); //Procédure qui traduis le labyrinthe sous forme d'affichage
void viderBufferClavier();
int choixDuLabyrinthe(); // Fonction qui retourne sous forme d'entier le choix du labyrinthe
void introduction(); // Procedure qui nous donne l'introduction du jeu
void selectLabyrinthe(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]); //Procedure qui permet de choisir 1 des 10 labyrinthe
void miseEnPlaceThesee(int posH[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]); //Procedure qui mets en place, dans le labyrinthe back-end, le personnage
void miseEnPlaceMinotaure(int posM[2], int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void miseEnPlacePrincess(int Labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe]);
void labyrintheUtiliseAffichage(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe], int labyrintheUtilise[HauteurLabyrinthe+1][LargeurLabyrinthe]); //Procédure qui permet d'afficher le labyrinthe avec un saut à la ligne
void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe],int clauseDeSortie); //Procédure qui permet le premier jeu avec le deplacement unique du héro
void jeuTWO(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe], int clauseDeSortie); //Procédure qui permet le second jeu avec le deplacement du héro et du minotaure

int main()
{
    SetConsoleOutputCP(65001);//utilisé pour gérer les caractères type "é", "è",... Cette référence nous a été fourni après une recherche sur le sujet (unique recherche externe pour le code)
    int choixLabyrinthe=1; //valeur initée à 1 pour selectionner le premier labyrinthe, pourra être changée dans le futur
    char nom_hero[15]= "Thésée";
    char nom_princesse[15] = "Arianne";
    char choix; //caractère utilisé pour effectué le choix dans le menu
    int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe]; //labyrinthe utilisé pour effectué le transfert du contenu du labyrinthe selectionné sur base du nombre choixLabyrinthe
    int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe];//Labyrinthe back-end utilisé pour manifester les déplacement sur la labyrinthe affiché
    int posH[2]; //position en X et Y de Thésée
    int posM[2]; //position en X et Y du Minotaure
    int clauseDeSortie = 1; //astuce utilisée pour signalé si le jeu fini ou non

    do
    {
        printf("\n===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n4. Jeu difficulte 1\n5. Jeu difficulte 2\n6. Quitter le jeu\n");
        choix = getch();//permet d'établir un choix sans la commande entrée

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
    do
    {
        printf("\nAvec quel labyrinthe souhaitez-vous jouer ?\n");
        scanf("%d", &choixLabyrinthe); //Permet de stocker pour le futur la valeur choixLabyrinthe
    }
    while(choixLabyrinthe< 0 || choixLabyrinthe>11); //empeche la valeur choixLabyrinthe d'être inférieure ou égale à 0 ou supérieure ou égale à 11
    return choixLabyrinthe;
}
void introduction()
{
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps d'un homme et la tête d'un taureau.");
    printf("\nIl fut enfermé par le roi Minos dans le labyrinthe construit Dédale (au centre de la Crète).");
    printf("\nRégulièrement, des victimes étaient envoyées dans ce labyrinthe afin d'être sacrifiées par le Minotaure.");
    printf("\nThésée, fils d'Egée, accompagné d'autres victimes furent envoyées en Crête pour être sacrifié dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Thésée et sachant ce qui l'attendait dans le labyrinthe, lui remit une bobine de fil afin qu'il l'utilise pour retrouver la sortie du labyrinthe s'il ressort victorieux du combat contre le Minotaure.");
    printf("\nThésée parvient à tuer le Minotaure et à sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous êtes le héros (représentant Thésée) et vous devez chercher la princesse Ariane maintenue prisonnière à l'intérieur du labyrinthe.");
    printf("\nEn tant que joueur (le héros Thésée) vous déplacer le héros en utilisant les touches de déplacement pour essayer de rejoindre Ariane tout en évitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure à l'intérieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
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
            labyrinthe[posX][posY] = 3; //met en place Thésée dans le labyrinthe et conserve en mémoire la position de celui-ci
            test = 1;//mets la valeur à 1 pour sortir de la boucle
            posH[0] = posX;
            posH[1] = posY;
        };
    }while(test == 0); //Continue à refaire les mêmes étapes tant que la valeur est à 0 (tant qu'on est pas passé dans le if ci-dessus)
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
            labyrinthe[posX][posY] = 2; //met en place le Minotaure dans le labyrinthe et conserve en mémoire la position de celui-ci
            test = 1;//mets la valeur à 1 pour sortir de la boucle
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
            test = 1;//mets la valeur à 2 pour sortir de la boucele
        };
    }while(test == 0);
}


void jeuONE(int choixLabyrinthe, int labyrintheChoisi[HauteurLabyrinthe][LargeurLabyrinthe], int posH[2], int posM[2], int labyrintheManifeste[HauteurLabyrinthe+1][LargeurLabyrinthe], int clauseDeSortie)
{
    //Code utilisé pour le jeu de difficulté simple où le minotaure est immobile
    int score = 10000;
    char touche;
    EffaceEcran();
    printf("\b"); //backspace effectué suite à l'apparition d'un espace parasite sur l'écran dû à la fonction EffaceEcran
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL)); //on remet le random à 0 pour eviter que la ligne suivante donne à chaque fois le même résultat
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM, labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
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
    posH[0]++; //On incrémente la position de H de 1 pour avoir le parallélisme entre labyrinthe back-end et affichage
    FixePosCurseur(posH[1], posH[0]);
    clauseDeSortie=1; //la valeur de la clause de sortie est utilisée à la ligne suivante afin qu'elle continue à tourner jusqu'à ce que celle-ci soit nulle (condition de victoire/défaite)


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
            /// Touche flèche en haut actionnée
            if(touche == 72)    /// code ASCII de la touche flèche en haut
            {

                if(labyrintheManifeste[posH[0]-1][posH[1]]==0)
                {
                    if(labyrintheManifeste[posH[0]][posH[1]]==3)//permet de mettre à 0 la position de base du H dans le labyrinthe back-end, et permet de refranchir celle-ci dans le futur
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
                    clauseDeSortie=0;//Est mise à 0 parce que c'est notre condition de boucle et qu'ainsi nous pourrons alors sortir de la boucle
                }
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }
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
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]+1][posH[1]]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }
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
                    clauseDeSortie=0;
                }
                else if(labyrintheManifeste[posH[0]][posH[1]-1]==4)
                {
                    EffaceEcran();
                    printf("YOU WIN !\nYOUR SCORE: %d", score);
                    clauseDeSortie=0;
                }


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
    //possible deplacement du P & M suite à la traduction du labyrinthe en affichage
    int score = 0;
    char touche;
    EffaceEcran();
    printf("\b"); //backspace effectué suite à l'apparition d'un espace parasite sur l'écran
    selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
    srand(time(NULL));
    miseEnPlaceThesee(posH,labyrintheChoisi);
    miseEnPlaceMinotaure(posM,labyrintheChoisi);
    miseEnPlacePrincess(labyrintheChoisi);
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
            /// Touche flèche en haut actionnée
            if(touche == 72)    /// code ASCII de la touche flèche en haut
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
                else if(labyrintheManifeste[posH[0]-1][posH[1]]==2)//gestion de la sortie du jeu pour le héros
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

            /// Touche flèche en bas actionnée
            if(touche == 80)    /// code ASCII de la touche flèche en bas
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

            /// Touche flèche à gauche actionnée
            if(touche == 75)    /// code ASCII de la touche flèche à gauche
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

            /// Touche flèche à droite actionnée

            if(touche == 77)    /// code ASCII de la touche flèche à droite
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

            /// Touche 'z' actionnée
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

            /// Touche 's' actionnée
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

            /// Touche 'q' actionnée
            if(touche == 'q')    /// Touche 'q' direction à gauche
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

            /// Touche 'd' actionnée

            if(touche == 'd')    /// Touche 'd' direction à droite
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
