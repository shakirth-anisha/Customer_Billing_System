#include <stdio.h>
#include "admin.c"
#include "customer.c"
#include "exit.c"

int main(){
    int main_option;
    printf("=====================================================================\n\n");
    printf("                        Supermarket Main Menu\n\n");
    printf("=====================================================================\n\n\n");
    main_menu: 
    printf("                    What would you like to access?\n\n");
    printf("=====================================================================\n");
    printf("                  |         1.)  Administrator    |\n");
    printf("                  |         2.)  Customer         |\n");
    printf("                  |         3.)  Exit             |\n");
    printf("=====================================================================\n\n");

    printf("                       Enter your choice: ");
    scanf("%d", &main_option);
    
    //Selecting an option
    switch (main_option)
    {
    case 1:
        administrator();
        goto main_menu;
        break;

    case 2:
        customer();
        goto main_menu;
        break;
    
    case 3:
        quit();
        break;

    default:
        printf("\n=====================================================================\n");
        printf("                     Invalid Option. Try Again?\n");
        printf("=====================================================================\n");
        goto main_menu;
        break;
    }
    return 0;
}