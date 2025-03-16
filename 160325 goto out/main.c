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
int main()
{
    int choixLabyrinthe=1;
    char nom_hero[15]= "Thésée";
    char nom_princesse[15] = "Arianne";
    char choix;
    int labyrintheChoisi[LargeurLabyrinthe][HauteurLabyrinthe];



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
            selectLabyrinthe(choixLabyrinthe,labyrintheChoisi);
            affichageLabyrinthe(labyrintheChoisi);
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
        labyrintheChoisi = Labyrinthe2;
        break;
    case 3:
        labyrintheChoisi = Labyrinthe3;
        break;
    case 4 :
        labyrintheChoisi = Labyrinthe4;
        break;
    case 5 :
        labyrintheChoisi = Labyrinthe5;
        break;
    case 6 :
        return Labyrinthe6;
        break;
    case 7:
        return Labyrinthe7;
        break;
    case 8:
        return Labyrinthe8;
        break;
    case 9:
        return Labyrinthe9;
        break;
    case 10 :
        return Labyrinthe10;
        break;
    }
}
void affichageLabyrinthe(int labyrinthe[HauteurLabyrinthe][LargeurLabyrinthe])
{
    srand(time(NULL));
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
            else
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
    printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possedant le corps d’un homme et la tête d’un taureau.");
    printf("\nIl fut enfermé par le roi Minos dans le labyrinthe construit Dédale (au centre de la Crète).");
    printf("\nRégulièrement, des victimes étaient envoyées dans ce labyrinthe afin d’être sacrifiées par le Minotaure.");
    printf("\nThésée, fils d’Egée, accompagné d’autres victimes furent envoyées en Crête pour être sacrifié dans le labyrinthe par le Minotaure.");
    printf("\nAriane, fille de Minos, tomba follement amoureuse de Thésée et sachant ce qui l’attendait dans le labyrinthe, lui remit une bobine de fil afin qu’il l’utilise pour retrouver la sortie du labyrinthe s’il ressort victorieux du combat contre le Minotaure.");
    printf("\nThésée parvient à tuer le Minotaure et à sortir indemne du labyrinthe.");
    printf("\nLe principe du jeu est simple, vous êtes le héros (représentant Thésée) le et vous devez chercher la princesse Ariane maintenue prisonnière à l’intérieur du labyrinthe.");
    printf("\nEn tant que joueur (le héros Thésée) vous déplacer le héros en utilisant les touches de déplacement pour essayer de rejoindre Ariane tout en évitant de se faire attraper par le Minotaure.");
    printf("\nLe monstrueux Minotaure à l’intérieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");
}

