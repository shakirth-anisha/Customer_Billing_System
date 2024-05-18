#include <stdio.h>
#include <stdlib.h>

void profile(struct user_details *user, int option);
struct item_details * find_add_item(item_t *users, char * username, int to_find, int quan);
int total_cost (item_t * cart);
void csv_cart_to_struct (char * current_user);

void customer(struct user_details user){
    csv_cart_to_struct(user.username);

    int customer_options, profile_options, query_c, item_no, item_quan, cart_choice;
    item_t *temp;
    customer_menu:
    printf("\n\n=====================================================================\n");
    printf("                           Customer Settings\n");
    printf("=====================================================================\n");
    printf("                  |         1.)  View Profile     |\n");
    printf("                  |         2.)  View Products    |\n");
    printf("                  |         3.)  View Cart        |\n");
    printf("                  |         4.)  Buy Items        |\n");
    printf("                  |         5.)  Remove Items     |\n");
    printf("                  |         6.)  Main Menu        |\n");
    printf("=====================================================================\n\n");

    printf("                       Enter your choice: ");
    scanf("%d", &customer_options);

    //Select Customer Options using switch case;
    switch (customer_options)
    {
    case 1:
    your_profile:
        printf("\n\n=====================================================================\n\n");
        printf("                             Your Profile\n\n");
        printf("=====================================================================\n\n");
        printf("                           Username: %s\n", user.username);
        printf("                           Password: %s\n", user.password);
        printf("\n=====================================================================\n\n");
        printf("                  |         1.)  Change Username  |\n");
        printf("                  |         2.)  Change Password  |\n");
        printf("                  |         3.)  Back             |\n");
        printf("\n=====================================================================\n\n");
        printf("                       Enter your choice: ");
        scanf("%d", &profile_options);
        profile(&user, profile_options);

        if(profile_options!=3) goto your_profile;
        else goto customer_menu;

        break;
    
    case 2:
        printf("\n\n=====================================================================\n");
        printf("                           Available Items\n");
        printf("=====================================================================\n\n");
        list_existing_items(item_database);
        //Set up a back option and return to main menu option
        goto customer_menu;
        break;
    
    case 3:
        your_cart:
        printf("\n\n=====================================================================\n");
        printf("                             Your cart\n");
        printf("=====================================================================\n\n");
        list_existing_items(cart_items);
        printf("=====================================================================\n");
        printf("                  |         1.)  Checkout         |\n");
        printf("                  |         2.)  Back             |\n");
        printf("=====================================================================\n\n");
        printf("                       Enter your choice: ");
        scanf("%d", &cart_choice);
        switch (cart_choice)
        {
        case 1:
            printf("\n\n=====================================================================\n");
            printf("                        Your Total is: %d\n", total_cost(cart_items));
            printf("=====================================================================\n\n");
            printf("=====================================================================\n");
            printf("                  |         1.)  Proceed          |\n");
            printf("                  |         2.)  Back             |\n");
            printf("=====================================================================\n\n");
            printf("                       Enter your choice: ");
            scanf("%d", &cart_choice);
            switch (cart_choice)
            {
                case 1:
                    printf("\n\n=====================================================================\n\n");
                    printf("                    Your Transaction is Complete.\n\n");
                    printf("=====================================================================\n\n");
                    while (cart_items!=NULL)
                    {
                        temp = cart_items;
                        cart_items = cart_items->next;
                        free(temp);
                    }
                    quit();
                    break;

                case 2:
                    goto your_cart;
                    break;

                default:
                    invalid();
                    goto your_cart;
            }

            break;
        
        case 2:
            goto customer_menu;
            break;

        default:
            invalid();
            goto your_cart;
            break;
        }
        //Set up a back option and return to main menu option
        //Set up a total value and ask to proceed to checkout
        //If they checkout, display "Purchase Successfull" and ask if they want to quit or go to main menu
        goto customer_menu;
        break;
    
    case 4:
        printf("                  Enter the number of quires: ");
            scanf("%d", &query_c);
            while (query_c>0)
            {            
            printf("          Enter Item Number and Quantity: ");
            scanf("%d %d", &item_no, &item_quan);
            find_add_item(item_database, user.username, item_no, item_quan);
            query_c--;
            }
        goto customer_menu;
        //Ask info on how many quires are required and product details. 
        //Also set up a force quit on an accidental value
        //Set up an Invalid Response         
        break;

    case 5:
        //Ask info on how many quires are required and product details. 
        //Also set up a force quit on an accidental value. 
        //Set up an Invalid Response 
        break;

    case 6:
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

void profile(struct user_details *user, int option){
    switch (option)
    {
    case 1:
        printf("=====================================================================\n\n");
        printf("                Enter your new username: ");
        scanf("%s", user->username);
        printf("\n=====================================================================\n\n");
        break;
    case 2:
        printf("=====================================================================\n\n");
        printf("                Enter your new password: ");
        scanf("%s", user->password);
        printf("\n=====================================================================\n\n");
        break;
    default:
        invalid();
        break;
    }

}

struct item_details * find_add_item(item_t *users, char *username, int to_find, int quan) {
    FILE *fcart = fopen("Cart.csv", "a");
    if (fcart != NULL){
    while (users!=NULL){
        if (users->item_no == to_find){
            printf("%12d|\t\t%12s|\t\t%8d|\t\t%d|\n", users->item_no, users->item_name, users->price, quan);
            add_item(&cart_items, users->item_no, users->item_name, users->price, quan, 1);
            fprintf(fcart,"%s,%d,%s,%d,%d\n", username, users->item_no, users->item_name, users->price, quan);
            return users;
        }
        users = users->next;
        }
        fclose(fcart);
    }
    else {
            printf("\n\n----------------------ERROR IN OPENING FILE----------------------\n\n");
        }
    return &error_items;
}

int total_cost (item_t * cart){
    int sum=0;
    while (cart!=NULL)
    {
        sum+=(cart->price*cart->quantity);
        cart = cart->next;
    }
    return sum;
}

void csv_cart_to_struct (char * current_user){
    //CART TO STRUCT
    free(cart_items);
    new_add_count = 0;
    FILE *fcart;
	fcart = fopen("Cart.csv", "r");
	if (fcart == NULL) {
		printf("ERROR in opening file");
	}
	else {

		char line[1024];
		    while (fgets(line, 1024, fcart)) {
			char *tmp = strdup(line);
            char new_itemname[100], new_username[100];
            int new_itemno, new_price, new_quantity;
			if (new_add_count > 0) {
			        strcpy(new_username, strtok(tmp, ",\n"));  
					new_itemno = atoi(strtok(NULL, ","));  
			        strcpy(new_itemname, strtok(NULL, ","));  
		    	    new_price = atoi(strtok(NULL, ","));
		    	    new_quantity = atoi(strtok(NULL, ","));
                    if (strcpy(new_username, current_user)){
                    add_item(&cart_items, new_itemno, new_itemname, new_price, new_quantity, 1);}
    		}

            #ifdef DEBUG_MAIN
            printf("hi from add to cart\n\nitemno: %d\nitem name: %s\nprice: %d\nquantity: %d\n\n", new_itemno, new_itemname, new_price, new_quantity);
            #endif

            new_add_count++;      
            free(tmp);
        }
        fclose(fcart);

        #ifdef DEBUG_MAIN
        list_existing_items(cart_items);
        #endif
	}
}