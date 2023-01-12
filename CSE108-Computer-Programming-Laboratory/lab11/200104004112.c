#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
    int data;
    float number;
    char* name;
    struct node *next;
};


void insert_end(struct node **head, int val, float num, char* name_)
{
    //create a new node
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = val;
    newNode->number = num;
    newNode->name = name_;
    newNode->next = NULL;

    //if head is NULL, it is an empty list
    if(*head == NULL)
         *head = newNode;
    //Otherwise, find the last node and add the newNode
    else
    {
        struct node *lastNode = *head;

        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
}

void printList_withLoop(struct node *head)
{
    while(head != NULL)
    {
        printf("%d --> %f --> %s\n", head->data, head->number, head->name);
        head = head->next;
    }

}
void printList_withRecursive(struct node *list) {
    if (list == NULL) return;
    else
    {
        printf("%d --> %f --> %s\n", list->data, list->number, list->name);
        printList_withRecursive(list->next);
    }
}
void insert_head(struct node** head_ref, struct node* new_node)
{
    new_node->next = (*head_ref);
    *head_ref = new_node;
}
void sortedInsert(struct node** head_ref, struct node* new_node)
{
    struct node *head = *head_ref;
    struct node *cursor = NULL;

    while (head != NULL)
    {
        if (strcmp(new_node->name, head->name) > 0)
        {
            cursor = head;
        }
        head = head->next;
    }
   if (cursor == NULL)
   {
       new_node->next = (*head_ref);
        *head_ref = new_node;
   }
   else
   {
       new_node->next = cursor->next;
       cursor->next = new_node;
   }
}
 
 
/* A utility function to create a new node */
struct node* newNode(int new_data, float num, char* name_)
{
    /* allocate node */
    struct node *new_node;
    new_node = malloc(sizeof(struct node));
    /* put in the data  */
    new_node->data = new_data;
    new_node->number = num;
    new_node->name = malloc(strlen(name_) + 1);
    strncpy(new_node->name, name_, strlen(name_));
    new_node->name[strlen(name_)] = '\0';
    new_node->next = NULL;
    /* return new node */
    return new_node;
}


bool search(struct node* head, int x)
{
    while (head != NULL)
    {
        if (head->data == x)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

int main()
{
    struct node *head = NULL;

    insert_end(&head,10,5.5,"hello1");
    insert_end(&head,20,5.5,"hello2");
    insert_end(&head,30,5.5,"hello3");

    printf("Print List with Loop: \n");
    printList_withLoop(head);
    
    struct node* new_node = newNode(1,5.5, "a");
    sortedInsert(&head, new_node);
     
     
    new_node = newNode(3,5.5, "c");
    sortedInsert(&head, new_node);

    
    new_node = newNode(2,5.5, "d");
    sortedInsert(&head, new_node);

    new_node = newNode(2,5.5, "b");
    sortedInsert(&head, new_node);
    
    new_node = newNode(2,5.5, "z");
    sortedInsert(&head, new_node);
     
    new_node = newNode(2,5.5, "h");
    sortedInsert(&head, new_node);
    new_node = newNode(2,5.5, "g");
    sortedInsert(&head, new_node);

    new_node = newNode(2,5.5, "i");
    sortedInsert(&head, new_node);

    printf("\n\nPrint List with Recursive: \n");
    printList_withRecursive(head);
	
	printf("\nIs 20 belong this linked list?: " );
    printf(search(head, 20) ? "YES \n" : "NO \n");
    
    printf("\nIs 18 belong this linked list?: " );
    printf(search(head, 18) ? "YES \n" : "NO \n");


    return 0;
}