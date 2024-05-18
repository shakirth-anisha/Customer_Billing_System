#include <stdio.h>

static int password = 123;
// #define DEBUG_ADMIN 1

int new_add_count = 0;
void add_item(item_t **users, int prod_num, char *name, int price, int quant, int check_csv1);
void list_existing_items(item_t *a);
int check_item_number(item_t *users, int to_find);

// FILE *ffp;
// 	ffp = fopen("Items.csv", "r");
// 	if (ffp == NULL) {
// 		printf("ERROR in opening file");
// 	}
// 	else {

// 		char line[1024];
// 		    while (fgets(line, 1024, ffp)) {
// 			char *tmp = strdup(line);
//             char new_itemname[100];
//             int new_itemno, new_price, new_quantity;
// 			if (new_add_count > 0) {
// 					new_itemno = atoi(strtok(tmp, ",\n"));  
// 			        strcpy(new_itemname, strtok(NULL, ","));  
// 		    	    new_price = atoi(strtok(NULL, ","));
// 		    	    new_quantity = atoi(strtok(NULL, ","));
//                     add_item(&item_database, new_itemno, new_itemname, new_price, new_quantity, 1);
//     		}

//             #ifdef DEBUG_ADMIN
//             printf("hi from add to items\n\nitemno: %d\nitem name: %s\nprice: %d\nquantity: %d\n\n", new_itemno, new_itemname, new_price, new_quantity);
//             #endif

//             new_add_count++;      
//             free(tmp);
//         }
//         fclose(ffp);
// 	}

void administrator(){
    int admin_option, trail=0, check, price, quant, query, num;
    char name[100];
    
    enter_password:
    printf("\n\n=====================================================================\n");
    printf("                       Enter your password: ");
    scanf("%d", &check);
    printf("=====================================================================\n\n");

if (password==check){

    admin_menu:
    admin_option = 0;
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
            list_existing_items(item_database);
            //S̶e̶t̶ u̶p̶ a̶ b̶a̶c̶k̶ o̶p̶t̶i̶o̶n̶ a̶n̶d̶ r̶e̶t̶u̶r̶n̶ t̶o̶ m̶a̶i̶n̶ m̶e̶n̶u̶ o̶p̶t̶i̶o̶n̶
            goto admin_menu;
            break;
        
        case 2:
            printf("\n\n=====================================================================\n");
            printf("                              Add Items\n");
            printf("=====================================================================\n\n");
            printf("         Enter the number of quires: ");
            query = 0;
            scanf("%d", &query);
            while (query>0)
            {            
            printf("Enter Item Number, Item Name, Price and Quantity: ");
            scanf("%d %s %d %d", &num, name, &price, &quant);
            add_item(&item_database, num, name, price, quant, 0);
            query--;
            }
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
            invalid();
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
    else trail=0;
}
    //Use Files to Add view and delete products
}

void add_item(item_t **users, int prod_num, char *name, int price, int quant, int check_csv1){
    if (!check_item_number(*users, prod_num)){
    FILE *f1 = fopen("Items.csv", "a");
    if (f1 != NULL){
    item_t *new_node = (item_t*) malloc(sizeof(item_t));
    item_t *last = *users;
    new_node->item_no = prod_num; strcpy(new_node->item_name, name); new_node->price = price; new_node->quantity = quant;
    //Checking if its first element
    if (*users == NULL){
        new_node->next = NULL;
        *users = new_node;
    }
    //Adding elements (LINKED LIST)
    else {
        new_node->next = *users;
        (*users) = new_node;
    }
    if (check_csv1!=1){
        fprintf(f1,"%d,%s,%d,%d\n",new_node->item_no, new_node->item_name, new_node->price, new_node->quantity);
    }
    fclose(f1);
    }
    else {
            printf("\n\n----------------------ERROR IN OPENING FILE----------------------\n\n");
        }
    }
    else invalid();
}

void list_existing_items(item_t *a){
    printf("|Item Number|\t\t|Item Name|\t\t|Price|\t\t|Quantity|\n\n");
    //|Product Number\t|Product Name\t|Quantity\t|Price\t\n
    while (a!=NULL)
    {
        printf("%12d|\t\t%12s|\t\t%8d|\t\t%d|\n", a->item_no, a->item_name, a->price, a->quantity);
        a = a->next;
    }
    // printf("%d %s %d\n", a->roll, a->name, a->sem);
}

int check_item_number(item_t *users, int to_find) {
    while (users!=NULL)
    {
        if (users->item_no == to_find){
            return 1;
        }
        users = users->next;
    }
    return 0;
}