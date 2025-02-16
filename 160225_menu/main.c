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
    char nom_hero[]= "Th�s�e";
    char nom_princesse[] = "Arianne";
    char choix;



    printf("===Menu principal===\n1. Introduction\n2. Changer les noms\n3. Choix du labyrinthe\n9. Quitter le jeu\n");
    choix = getchar();

    switch (choix)
    {
        case '1' :

            printf("Le Minotaure est dans la mythologie grecque, un monstre fabuleux poss�dant le corps d�un homme et la t�te d�un taureau.");
            printf("\nIl fut enferm� par le roi Minos dans le labyrinthe construit D�dale (au centre de la Cr�te).");
            printf("\nR�guli�rement, des victimes �taient envoy�es dans ce labyrinthe afin d��tre sacrifi�es par le Minotaure.");
            printf("\nTh�s�e, fils d�Eg�e, accompagn� d�autres victimes furent envoy�es en Cr�te pour �tre sacrifi� dans le labyrinthe par le Minotaure.");
            printf("\nAriane, fille de Minos, tomba follement amoureuse de Th�s�e et sachant ce qui l�attendait dans le labyrinthe, lui remit une bobine de fil afin qu�il l�utilise pour retrouver la sortie du labyrinthe s�il ressort victorieux du combat contre le Minotaure.");
            printf("\nTh�s�e parvient � tuer le Minotaure et � sortir indemne du labyrinthe.");
            printf("\nLe principe du jeu est simple, vous �tes le h�ros (repr�sentant Th�s�e) le et vous devez chercher la princesse Ariane maintenue prisonni�re � l�int�rieur du labyrinthe.");
            printf("\nEn tant que joueur (le h�ros Th�s�e) vous d�placer le h�ros en utilisant les touches de d�placement pour essayer de rejoindre Ariane tout en �vitant de se faire attraper par le Minotaure.");
            printf("\nLe monstrueux Minotaure � l�int�rieur du labyrinthe peut se mouvoir ou pas (suivant le jeu choisi).");

        break;

        case '2':
            viderBufferClavier();

            printf("\nVeuillez introduire le nom du H�ro \n");
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
