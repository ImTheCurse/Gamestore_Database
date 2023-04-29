#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256
#define DBG printf("Entered Here\n");



typedef struct game_node {
    char* title;
    char* genre;
    int year;
    float rating;
    struct game_node* next;
    struct dlc_node* dlc_head;
}GameNode;

typedef struct dlc_node {
    char* title;
    float price;
    struct dlc_node* next;
}DLCNode;

typedef struct {
    GameNode* head;
}GameLinkedList;



DLCNode *CreateDLC(DLCNode *head){
    head = (DLCNode*)malloc(sizeof(DLCNode));
    char *buffer = (char *)malloc(MAX_LEN*sizeof(char));
    if(buffer == NULL){
        free(buffer);
        return head;
    }
    float price = 0.0;

    //get input from user
    printf("DLC Title - ");
    fgets(buffer,MAX_LEN,stdin);
    head->title = (char*)malloc(strlen(buffer)+1);
    if(head->title == NULL){free(head->title);return head;}
    strcpy(head->title,buffer);


    printf("Price - ");
    scanf("%f", &price);
    getchar();    

    head->price = price;

    free(buffer);
    head->next = NULL;
    return head;
    

}


    GameNode *findTitle(GameNode *head,char *title){
        while(head != NULL){
            if(strcmp(head->title,title)==0){
                return head;
            }
            head = head->next;
        }
        
        return NULL;
    }

DLCNode* insert_dlc_at_end(GameNode *head){

    char *buffer = (char*)malloc(MAX_LEN*sizeof(char));
    if(buffer == NULL){free(buffer);return head->dlc_head;}

    printf("Enter Title Name: ");
    fgets(buffer,MAX_LEN,stdin);
    

    GameNode* titleHead;
    titleHead = findTitle(head,buffer);
    
    
    if(titleHead == NULL){
        printf("Title dosen't exist");
        return NULL;
    }
    

    DLCNode *curr = titleHead->dlc_head;
    DLCNode *prev = titleHead->dlc_head;
    
    
    if(titleHead->dlc_head == NULL){
        prev = CreateDLC(titleHead->dlc_head);
        curr = prev->next;
        titleHead->dlc_head = prev;
        return titleHead->dlc_head;
        
    }
    //moving up curr pointer until it reaches the place to add the DLC(where the NULL is)
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
        
    }
    
    DLCNode *newNode = CreateDLC(curr);
    newNode->next = prev->next;
    prev->next = newNode;

    return titleHead->dlc_head;

    


}


void printDLC(GameNode *head){
    char *titleName = malloc(MAX_LEN*sizeof(char));
    if(titleName == NULL){free(titleName);}

    printf("Enter Title Name: ");
    fgets(titleName,MAX_LEN,stdin);
    GameNode *curr = head;
    
    //iterating over curr to find title name in the linked list,else there isn't a DLC.
    while(curr != NULL){
        if(strcmp(curr->title,titleName) == 0){
            printf("DLC's:\n");
            while(curr->dlc_head != NULL){
                printf("Name: %sPrice: %.1f$\n",curr->dlc_head->title,curr->dlc_head->price);
                curr->dlc_head = curr->dlc_head->next;
            }
            free(titleName);
            return;
        }
        curr = curr->next;
    }
    printf("No DLC's found.");
    free(titleName);
}


GameNode* GameAdd(GameNode *pos){
    
    pos = (GameNode*)malloc(sizeof(GameNode));//TODO FREE
    if(pos == NULL){
        free(pos);
    }
    
    
    char *buffer = malloc(MAX_LEN*sizeof(char));
    if(buffer == NULL){
        free(buffer);
    }
    
    int year;
    float rating;

    //Get Input from user

    printf("Game Title - ");
    fgets(buffer,MAX_LEN,stdin);
    pos->title = (char *)malloc(strlen(buffer) + 1);

    if(pos->title == NULL){
        free(pos->title);
    }
    
    strcpy(pos->title,buffer);
    printf("Game Genre - ");
    fgets(buffer,MAX_LEN,stdin);
    pos->genre = (char *)malloc(strlen(buffer) + 1);

    if(pos->genre == NULL){
        free(pos->genre);
    }

    strcpy(pos->genre,buffer);

    printf("Year - ");
    scanf("%d", &year);
    pos->year = year;
    printf("Rating - ");
    scanf("%f", &rating);
    getchar();
    pos->rating = rating;

    pos->next = NULL;
    free(buffer);
    return pos;

}

GameNode* insert_game_at_end(GameNode *head){
    GameNode *prev = head;
    GameNode *curr = head;
    if(head == NULL) {
        prev = GameAdd(head);
        curr = prev->next;
        head = prev;
        
        head->dlc_head = NULL;//when inserting the game, the DLC is currently NULL and later will be added.
        return head;
    }

    while(curr != NULL){
        prev = curr;
        curr = curr->next;
    }

    GameNode *newNode = GameAdd(curr);

    newNode->next = prev->next;
    prev->next = newNode;

    newNode->dlc_head = NULL;//when inserting the game, the DLC is currently NULL and later will be added.
    
    return head;

}


void printList(GameNode *head){
    GameNode *curr = head;
    int i = 0;
    while(curr != NULL){
        printf("%s\n",curr->title);
        curr = curr->next;
    }
}

int LLSize(GameNode *head){
    int i = 0;
    while(head != NULL){
        i++;
        head = head->next;
    }
    return i;
}



GameNode *delete_game_by_title(GameNode *head){
    char *buffer = (char*)malloc(MAX_LEN*sizeof(char));
    if(buffer == NULL){
        free(buffer);
        return head;
    }

    GameNode *curr = head;
    GameNode *prev = head;
    

    printf("Enter game title to remove: ");
    fgets(buffer,MAX_LEN,stdin);

    //if the game is at the head, jump to the next and free the memory of the game and dlc.
    if(strcmp(head->title,buffer) == 0){
        head = head->next;
        free(curr);
        free(buffer);
        if(curr->dlc_head != NULL){
            free(curr->dlc_head);
        }
        return head;
    }
    //iterate over until you reach NULL(if you reach NULL then the title wasn't found).
    while(curr != NULL){
        if(strcmp(curr->title,buffer) == 0){
            prev->next = curr->next;
            free(curr);
            free(buffer);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("not found %s",buffer);
    free(buffer);
    return head;

}

DLCNode *findDLCTitle(GameNode *head){
    char *buffer = (char*)malloc(MAX_LEN*sizeof(char));
    if(buffer == NULL){
        free(buffer);
        return head->dlc_head;
    }
    printf("Enter DLC's game title: ");
    fgets(buffer,MAX_LEN,stdin);
    GameNode *curr = findTitle(head,buffer);
    if(curr == NULL){
       printf("No title found.\n");
       return head->dlc_head;
    }

    printf("Enter DLC name to remove: ");
    fgets(buffer,MAX_LEN,stdin);
    
    //finding DLC to remove.
    while(curr->dlc_head != NULL){
        if(strcmp(buffer,curr->dlc_head->title) == 0){
            free(buffer);
            return curr->dlc_head;
        }
        curr->dlc_head = curr->dlc_head->next;
    }
   
    printf("No DLC found.\n");
    free(buffer);
    return NULL;
}



DLCNode *delete_dlc_by_title(GameNode *head){
    DLCNode *head1 = head->dlc_head;
    DLCNode *curr = findDLCTitle(head);
    if(curr == NULL){
        return head1;
    }
    DLCNode *prev = head1;
    DLCNode *check = head1->next;
    
    //if the dlc we want to remove at the head then jump to the next one.
    if(strcmp(head1->title,curr->title) == 0){
        head1 = head1->next;
        free(curr);
        return head1;
    }

    // this is getting the prev pointer so we could link the prev->next to the node after current.
    while(check != NULL){
        
        if(strcmp(check->title,curr->title)==0){
            prev->next = curr->next;
            free(curr);
            return head1;
        }
        prev = check;
        check = check->next;
    }
}



void swapNodes(GameNode *a, GameNode *b){
    int yearTemp = 0;
    float floatTemp = 0;
    char *tempPtr;
    DLCNode *DNNodePtr;
    //Swaping the values of rating and year.
    yearTemp = a->year;
    a->year = b->year;
    b->year = yearTemp;

    floatTemp = a->rating;
    a->rating = b->rating;
    b->rating = floatTemp;
    
    //Swaping the pointers of genre and title.
    tempPtr = a->title;
    a->title = b->title;
    b->title = tempPtr;

    tempPtr = a->genre;
    a->genre = b->genre;
    b->genre = tempPtr;
    



    //Swaping the DLC nodes pointers.
    
    DNNodePtr = a->dlc_head;
    a->dlc_head = b->dlc_head;
    b->dlc_head = DNNodePtr;
}


GameNode *sort_games_by_rating(GameNode *head){

    GameNode *curr = head;
    GameNode *prev = head;
    GameNode *flag = head;
    
    while(flag != NULL){
        while(curr != NULL){
            if(curr->rating > prev->rating){
                swapNodes(curr,prev);
            }
            prev = curr;
            curr = curr->next;
        }
        flag = flag->next;
        prev = head;
        curr = head;
    }

    return head;
}



int main(){
GameNode *gn;
GameLinkedList *gll; 
gll = (GameLinkedList*)malloc(sizeof(GameLinkedList));

gn = NULL;
gll->head = gn;


while(1){
    int operation;
    printf("Video Game List Operations\n");
    printf("-----------------------------\n");
    printf("1. Insert game\n");
    printf("2. Delete game\n");
    printf("3. Print all games\n");
    printf("4. Sort games by rating\n");
    printf("5. Insert DLC for a game\n");
    printf("6. Delete DLC for a game\n");
    printf("7. print DLC for a game\n");
    printf("8. Exit\n");
    scanf("%d", &operation);
    getchar();
    switch(operation){
        case 1:

            gll->head = insert_game_at_end(gll->head);
            break;
        case 2:
            gll->head = delete_game_by_title(gll->head);
            break;
        case 3:
            printList(gll->head);
            break;
        case 4:
            sort_games_by_rating(gll->head);
            break;
        case 5:
            insert_dlc_at_end(gll->head);
            break;
        case 6:
            gll->head->dlc_head = delete_dlc_by_title(gll->head);
            break;
        case 7:
            printDLC(gll->head);
            break;
        case 8:
            return 0;
            //free()
            break;
        
        default:
            printf("Error! There is no such operation\n");
            break;
    }
    }








    return 0;
}
