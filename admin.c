#include <stdio.h>

static int password = 123;

void administrator(){
    int admin_option, trail;
    int check;

    enter_password:
    trail = 0;
    printf("\n\n=====================================================================\n");
    printf("                       Enter your password: ");
    scanf("%d", &check);
    printf("=====================================================================\n\n");

if (password==check){
    admin_menu:
    printf("\n\n=====================================================================\n");
    printf("                       Administrator Settings\n");
    printf("=====================================================================\n");
    printf("                  |         1.)  View Products    |\n");
    printf("                  |         2.)  Add Products     |\n");
    printf("                  |         3.)  Delete Products  |\n");
    printf("                  |         4.)  Change Password  |\n");
    printf("                  |         5.)  Main Menu        |\n");
    printf("=====================================================================\n\n");

    printf("                       Enter your choice: ");
    scanf("%d", &admin_option);

//Select Admin Options using switch case
        switch (admin_option)
        {
        case 1:
            printf("\n\n=====================================================================\n");
            printf("                        Available Items\n");
            printf("=====================================================================\n\n");
            //Set up a back option and return to main menu option
            goto admin_menu;
            break;
        
        case 2:
            //Ask info on how many quires are required and product details. 
            //Also set up a force quit on an accidental value
            //Set up an Invalid Response 
            goto admin_menu;
            break;
        
        case 3:
            //Ask info on how many quires are required and product details. 
            //Also set up a force quit on an accidental value
            //Set up an Invalid Response    
            goto admin_menu;     
            break;

        case 4:
            printf("\n\n=====================================================================\n");
            printf("                         Enter new password: ");
            scanf("%d", &password);
            printf("=====================================================================\n\n");
            goto enter_password;
            break;

        case 5:
            break;

        default:
            printf("\n\n=====================================================================\n");
            printf("                     Invalid Option. Try Again?\n");
            printf("=====================================================================\n\n");
            goto admin_menu;
            break;
        }
    }

else{
    printf("\n\n=====================================================================\n");
    printf("                     Incorrect Password. Try Again?\n");
    printf("=====================================================================\n\n");
    trail++;
    if (trail<2) goto enter_password;
}

    //Use Files to Add view and delete products
}