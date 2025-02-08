#include <stdio.h>
#include <stdlib.h>
#include "TableauxLabyrinthes.h"
#include "Temps.h"
#include "Affichage.h"
#include <conio.h>

int main()
{
    int posX, posY, test=0;//posX position en X, posY position en Y, test, valeur vide pour sortie de boucle
    srand(time(NULL));
    char table[HauteurLabyrinthe][LargeurLabyrinthe];
    int i,j; //definit un entier i ,et un entier utile dans le futur pour le parcours du tableau
    for(i=0; i<HauteurLabyrinthe;i++)
    {
        for(j=0; j<LargeurLabyrinthe;j++)
        {
            if(Labyrinthe10[i][j]==0) //On cherche les case = 0 pour les remplacer dans un autre tableau par un espace
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
    do
    {
        posX = rand()%LargeurLabyrinthe;
        posY = rand()%HauteurLabyrinthe;
        if(Labyrinthe10[posX][posY]==0)
        {
            Labyrinthe10[posX][posY] = 3;
            table[posX][posY] = 'H';
            test = 1;
            //printf("Position H : %d %d\n", posX, posY);
        };
    }while(test == 0);
    do
    {
        posX = rand()%LargeurLabyrinthe;
        posY = rand()%HauteurLabyrinthe;
        if(Labyrinthe10[posX][posY]==0)
        {
            Labyrinthe10[posX][posY] = 4;
            table[posX][posY] = 'P';
            test = 2;
            //printf("Position P : %d %d\n", posX, posY);
        };
    }while(test == 1);
     do
    {
        posX = rand()%LargeurLabyrinthe;
        posY = rand()%HauteurLabyrinthe;
        if(Labyrinthe10[posX][posY]==0)
        {
            Labyrinthe10[posX][posY] = 2;
            table[posX][posY] = 'M';
            test = 3;
            //printf("Position M : %d %d\n", posX, posY);
        };
    }while(test == 2);
    for(i=0; i<HauteurLabyrinthe;i++)
    {
        for(j=0; j<LargeurLabyrinthe;j++)
        {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
