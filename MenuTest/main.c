#include <stdio.h>
#include <stdlib.h>

int main()
{
    int entreeMenu;
    do{scanf("%d", &entreeMenu);

            switch(entreeMenu) {
    case 1 :
        printf("bonjour");
        break;
    case 2 :
        printf("Comment va");
        break;
    case 3 :
        printf("Ca va et toi");
        break;
    default :
        printf("Au revoir");
            }
    }while(entreeMenu==1 || entreeMenu == 2 || entreeMenu == 3);
    return 0;
}
