// libraire de gestion du temps
// Fichier .c


// Pour info :
// clock_t ==> long entier
// clock() : renvoit le nombre de tops d'horloge du microprocesseur depuis le lancement du programme
// Attention il s'agit des tops d'horloge utilis� par votre application, donc globalement vous risquez d'avoir un peu plus que le temps desir�
// Ceci est du aux autres applications qui consomme du temps qui n'est pas comptabilis�
// CLOCKS_PER_SEC indique le nombre de tops d'horloge par seconde du microprocesseur sur lequel vous travaillez
// pour avoir le r�sultat en seconde, il convient d'ajouter au temps actuel, le nombre de seconde * CLOCKS_PER_SEC
// pour avoir le r�sultat en milli seconde, il convient d'ajouter au temps actuel, le nombre de milli seconde * CLOCKS_PER_SEC /1000

void Attendre(clock_t milliseconde)

{
    clock_t temps;    // Stocke le temps (en milliseconde)
    temps=clock();    // Stocke le temps actuel

    // Tant que le temps demand� n'est pas pass� on boucle
    while(temps+milliseconde*(CLOCKS_PER_SEC/1000) >clock());
}
