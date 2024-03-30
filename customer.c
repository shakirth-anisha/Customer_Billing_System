#include <stdio.h>

void customer(){
    int customer_options;
    customer_menu:
    printf("\n\n=====================================================================\n");
    printf("                           Customer Settings\n");
    printf("=====================================================================\n");
    printf("                  |         1.)  View Products    |\n");
    printf("                  |         2.)  View Cart        |\n");
    printf("                  |         3.)  Buy Items        |\n");
    printf("                  |         4.)  Remove Items     |\n");
    printf("                  |         5.)  Main Menu        |\n");
    printf("=====================================================================\n\n");

    printf("                       Enter your choice: ");
    scanf("%d", &customer_options);

    //Select Customer Options using switch case;
    switch (customer_options)
    {
    case 1:
        printf("\n\n=====================================================================\n");
        printf("                        Available Items\n");
        printf("=====================================================================\n\n");

        //Set up a back option and return to main menu option
        break;
    
    case 2:
        printf("\n\n=====================================================================\n");
        printf("                             Your cart\n");
        printf("=====================================================================\n\n");

        //Set up a back option and return to main menu option
        //Set up a total value and ask to proceed to checkout
        //If they checkout, display "Purchase Successfull" and ask if they want to quit or go to main menu
        break;
    
    case 3:
        //Ask info on how many quires are required and product details. 
        //Also set up a force quit on an accidental value
        //Set up an Invalid Response         
        break;

    case 4:
        //Ask info on how many quires are required and product details. 
        //Also set up a force quit on an accidental value. 
        //Set up an Invalid Response 
        break;

    case 5:
        break;

    default:
        printf("\n=====================================================================\n");
        printf("                     Invalid Option. Try Again?\n");
        printf("=====================================================================\n");

        goto customer_menu;
        break;
    }

    //Use Files to show items and add items to cart
}