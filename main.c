#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    TO DO LIST
-̶-̶>̶ S̶e̶t̶ C̶u̶r̶r̶e̶n̶t̶ U̶s̶e̶r̶ i̶n̶ b̶o̶t̶h̶ s̶i̶g̶n̶ u̶p̶ a̶n̶d̶ L̶o̶g̶ i̶n̶
--> Deal with Change username and Change Password in Customer.c
-̶-̶>̶ C̶t̶r̶l̶+̶C̶ C̶t̶r̶l̶+̶V̶ s̶i̶m̶i̶l̶a̶r̶ c̶o̶d̶e̶ o̶f̶ i̶t̶e̶m̶s̶ and cart
--> F̶i̶n̶d̶ t̶h̶e̶ t̶o̶t̶a̶l̶ o̶f̶f̶ t̶h̶e̶ b̶i̶l̶l̶ a̶c̶c̶o̶r̶d̶i̶n̶g̶ t̶o̶ p̶r̶i̶c̶e̶
--> Implement file handling.
--> MAKE CART STRUCTURE MAIN INDEX USERNAME/ACC NO ADD DETAILS (MAKE ADD ITEMS FUNC OR EDIT)
*/

// #define DEBUG_MAIN 1

struct item_details
{
    int item_no;
    char item_name[50];
    int price;
    int quantity;
    struct item_details *next;
} *item_database, *cart_items;

struct user_details
{
    int acc_no;
    char username[50];
    char password[50];
    struct user_details *next;
} *user_database;

typedef struct item_details item_t;
typedef struct user_details user_t;

user_t error_details = {-1,"-1","-1"};
item_t error_items = {-1,"-1",-1,-1};

#include "print_statements.c"
#include "admin.c"
#include "customer.c"

void list_existing_user(user_t *a);
void add_user(user_t **users, char *name, char *pas, int to_add_to_file);
struct user_details * find_user(user_t *users, char *to_find);
void add_csv_to_struct();

int main(){
    static char username[100], c_password[100], check_username[100], check_password[100], new_username[100], new_password[100];
    int main_option, log_in_option, pass_check=0;
    user_t current_user, *sample;
    
    add_csv_to_struct();

    printf("=====================================================================\n\n");
    printf("                        Supermarket Main Menu\n\n");
    printf("=====================================================================\n\n\n");

    log_in:
    printf("=====================================================================\n\n");
    printf("                             Login/Sign Up\n\n");
    printf("=====================================================================\n\n");
    printf("                  |         1.)  Sign Up          |\n");
    printf("                  |         2.)  Log In           |\n");
    printf("                  |         3.)  Exit             |\n");
    printf("\n=====================================================================\n\n");
    printf("                       Enter your choice: ");
    scanf("%d", &log_in_option);

    switch (log_in_option)
    {

    //ISSUE ARRAY OF user_database N̶O̶T̶ WOKRING!!!!!!!!!
    case 1:
        printf("=====================================================================\n\n");
        printf("                Enter your new username: ");
        scanf("%s", new_username);

        #ifdef DEBUG_MAIN
        if (!strcmp(new_username, "ani")) break;
        #endif

        if(find_user(user_database, new_username)->acc_no==-1){
        printf("                Enter your new password: ");
        scanf("%s", new_password);
        printf("\n");
        printf("=====================================================================\n\n\n");
        
        add_user(&user_database, new_username, new_password, 0);
        current_user = *user_database;
        }

        else{
            invalid();
            goto log_in;
        }

        break;
    
    case 2:
        printf("=====================================================================\n\n");
        printf("\n                          Enter your username: ");
        scanf("%s", check_username);
        
        sample = find_user(user_database, check_username);

        #ifdef DEBUG_MAIN
        list_existing_user(user_database);
        printf("\nSample:");
        printf("%d %s %s", sample->acc_no, sample->username, sample->password);
        #endif

        if (sample->acc_no!=-1){
            pass_check = 0;
            password_count_check:
            if(pass_check<=3){
                printf("                    Enter your password: ");
                scanf("%s", check_password);
                printf("\n");
                printf("=====================================================================\n\n\n");
                if (!strcmp(sample->password, check_password)) {
                    invalid();
                    goto password_count_check;
                }
                pass_check++;
            }
            else {
                invalid();
                goto log_in;
            }
        }
        else {
            invalid();
            goto log_in;
        }

        current_user = *sample;
        break;

        case 3:
            quit();
            return 0;

        default:
            invalid();
            break;
    }

    main_menu: 
    printf("                    What would you like to access?\n\n");
    printf("=====================================================================\n");
    printf("                  |         1.)  Administrator    |\n");
    printf("                  |         2.)  Customer         |\n");
    printf("                  |         3.)  Log Out          |\n");
    printf("                  |         4.)  Exit             |\n");
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
        customer(current_user);
        goto main_menu;
        break;
    
    case 3:
        goto log_in;
        break;

    case 4:
        quit();
        return 0;

    default:
        invalid();
        goto main_menu;
        break;
    }
    return 0;
}

void add_user(user_t **users, char *name, char *pass, int to_add_to_file){
    FILE *f1 = fopen("Users.csv", "a");
    if (f1 != NULL){
    static int num = 1;
    user_t *new_node = (user_t*) malloc(sizeof(user_t));
    user_t *last = *users;
    new_node->acc_no = num; 
    strcpy(new_node->username, name); 
    strcpy(new_node->password, pass);
    //Checking if its first element
    if (*users == NULL){
        new_node->next = NULL;
        *users = new_node;
    }

    else {
        new_node->next = *users;
        (*users) = new_node;
    }
    num++;
    if (to_add_to_file == 0) {
        fprintf(f1, "%d,%s,%s\n", new_node->acc_no, new_node->username, new_node->password);
    }
    fclose(f1);
    }
    else {
            printf("\n\n----------------------ERROR IN OPENING FILE----------------------\n\n");
        }
}

void list_existing_user(user_t *a){
    while (a!=NULL)
    {
        printf("%d %s %s\n", a->acc_no, a->username, a->password);
        a = a->next;
    }
}

struct user_details * find_user(user_t *users, char *to_find) {
    user_t check;
    int i=0;
    while (users!=NULL)
    {
        if (!strcmp(users->username, to_find)){

            #ifdef DEBUG_MAIN
            printf("\n\n%d %s %s", users->acc_no, users->username, users->password);
            #endif

            return users;
        }
        users = users->next;
    }
    return &error_details;
}

void add_csv_to_struct(){
    //USERS TO STRUCT
    int new_add_count = 0;
    FILE *fuser;
	fuser = fopen("Users.csv", "r");
	if (fuser == NULL) {
		printf("ERROR in opening file");
	}
	else {

		char line[1024], new_username[100], new_password[100];
		    while (fgets(line, 1024, fuser)) {
			char *tmp = strdup(line);
			if (new_add_count > 0) {
					strtok(tmp, ",\n");  
			        strcpy(new_username, strtok(NULL, ","));  
		    	    strcpy(new_password, strtok(NULL, ","));
                    add_user(&user_database, new_username, new_password, 1);
    		}

            #ifdef DEBUG_MAIN
            printf("hi from add to struct\n\nuser: %s\npass:%s\n\n", new_username, new_password);
            #endif

            new_add_count++;      
            free(tmp);
        }
        fclose(fuser);
        #ifdef DEBUG_MAIN
        list_existing_user(user_database);
        #endif
	}

    //ITEMS TO STRUCT
    new_add_count = 0;
    FILE *fitem;
	fitem = fopen("Items.csv", "r");
	if (fitem == NULL) {
		printf("ERROR in opening file");
	}
	else {

		char line[1024];
		    while (fgets(line, 1024, fitem)) {
			char *tmp = strdup(line);
            char new_itemname[100];
            int new_itemno, new_price, new_quantity;
			if (new_add_count > 0) {
					new_itemno = atoi(strtok(tmp, ",\n"));  
			        strcpy(new_itemname, strtok(NULL, ","));  
		    	    new_price = atoi(strtok(NULL, ","));
		    	    new_quantity = atoi(strtok(NULL, ","));
                    add_item(&item_database, new_itemno, new_itemname, new_price, new_quantity, 1);
    		}

            #ifdef DEBUG_MAIN
            printf("hi from add to items\n\nitemno: %d\nitem name: %s\nprice: %d\nquantity: %d\n\n", new_itemno, new_itemname, new_price, new_quantity);
            #endif

            new_add_count++;      
            free(tmp);
        }
        fclose(fitem);

        #ifdef DEBUG_MAIN
        list_existing_items(item_database);
        #endif
	}
}