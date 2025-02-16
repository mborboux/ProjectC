#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "tableauxLabyrinthes.h"
#include "Affichage.h"
void viderBufferClavier ()
{
int c;
do
{
c=getchar();
}
while (c!='\n' && c!=EOF);
}
int main()
{
    char nom_hero[]= "Thésée";
    char nom_princesse[] = "Arianne";
    char choix;



    printf("===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n9. Quitter le jeu\n");
    choix = getchar();

    switch (choix)
    {
        case '1' :

            printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux possédant le corps d’un homme et la tête d’un taureau.");
            printf("\nIl fut enfermé par le roi Minos dans le labyrinthe construit Dédale (au centre de la Crète).");
            printf("\nRégulièrement, des victimes étaient envoyées dans ce labyrinthe afin d’être sacrifiées par le Minotaure.");
            printf("\nThésée, fils d’Egée, accompagné d’autres victimes furent envoyées en Crête pour être sacrifié dans le labyrinthe par le Minotaure.");
            printf("\nAriane, fille de Minos, tomba follement amoureuse de Thésée et sachant ce qui l’attendait dans le labyrinthe, lui remit une bobine de fil afin qu’il l’utilise pour retrouver la sortie du labyrinthe s’il ressort victorieux du combat contre le Minotaure.");
            printf("\nThésée parvient à tuer le Minotaure et à sortir indemne du labyrinthe.");
            printf("\nLe principe du jeu est simple, vous êtes le héros (représentant Thésée) le et vous devez chercher la princesse Ariane maintenue prisonnière à l’intérieur du labyrinthe.");
            printf("\nEn tant que joueur (le héros Thésée) vous déplacer le héros en utilisant les touches de déplacement pour essayer de rejoindre Ariane tout en évitant de se faire attraper par le Minotaure.");
            printf("\nLe monstrueux Minotaure à l’intérieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");

        break;

        case '2':
            viderBufferClavier();

            printf("\nVeuillez introduire le nom du Héro \n");
            scanf("%s", nom_hero);
            viderBufferClavier();
            printf("\nVeuillez introduire le nom de la Princesse \n");
            scanf("%s", nom_princesse);
            printf("%s, %s", nom_hero, nom_princesse);

        break;

        case '3':

            viderBufferClavier();

        break;

        case '9':

            EffaceEcran();

        break;

    }

    return 0;
}
