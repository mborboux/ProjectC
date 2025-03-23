////// Librairie de gestion de l'affichage
////// fichier .h

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "Affichage.c"

// I N F O R M A T I O N S

// l'emplacement x=1,y=1 correspond au coin sup�rieur gauche de la console
// l'axe vertical est orient� vers le bas
// l'axe horizontal est orient� vers la droite

// pour les couleurs voici les correspondances
/*
NOIR (BLACK) = 0
BLEU (BLUE) = = 1
VERT (GREEN) = 2
CYAN = 3
ROUGE (RED) = 4
MAGENTA = 5
BRUN (BROWN) = 6
GRIS CLAIR (LIGHTGRAY) = 7
GRIS FONCE (DARKGRAY) = 8
BLEU CLAIR (LIGHTBLUE)= 9
VERT CLAIR (LIGHTGREEN) = 10
CYAN CLAIR (LIGHTCYAN) = 11
ROUGE CLAIR (LIGHTRED) = 12
MAGENTA CLAIR (LIGHTMAGENTA) = 13
JAUNE (YELLOW) = 14
BLANC (WHITE) = 15
*/

// Pour vous facilitez le travail :
#define NOIR 0
#define BLEU 1
#define VERT 2
#define CYAN 3
#define ROUGE 4
#define MAGENTA 5
#define BRUN 6
#define GRISCLAIR 7
#define GRISFONCE 8
#define BLEUCLAIR 9
#define VERTCLAIR 10
#define CYANCLAIR 11
#define ROUGECLAIR 12
#define MAGENTACLAIR 13
#define JAUNE 14
#define BLANC 15


//=====================================================================//
// Fonction qui positionne le curseur � l'emplacement x,y sur l'�cran  //
//                      construite � partir de conio.c                 //
//=====================================================================//

void FixePosCurseur(int x, int y);

//=====================================================================//


//=================================================================//
// Fonction qui fixe une couleur � l'emplacement du curseur        //
//                     construite � partir de conio.c              //
//=================================================================//

void Couleur(int CouleurCaractere, int CouleurFond);

//=====================================================================//


//=========================================================================//
// Fonction qui vide l'�cran ( on remplit l'�cran avec une couleur noire)  //
//=========================================================================//

void EffaceEcran();

//=========================================================================//
