#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct node_list
{
    int data;
    float number;
    char* name;
    struct node_list *next;
};

/*Do not modify the following function.*/

void insert_end(struct node_list **head, int val, float num, char* name_)
{ 
    struct node_list *newnode = malloc(sizeof(struct node_list));
    newnode->data = val;
    newnode->number = num;
    newnode->name = name_;
    newnode->next = NULL;

    if(*head == NULL)
 		*head = newnode;
    else
    {
        struct node_list *lastnode = *head;

        while(lastnode->next != NULL)
			lastnode = lastnode->next;

        lastnode->next = newnode;
    }
}

/*Do not modify the following function.*/

void print_list(struct node_list *head)
{
	struct node_list *temp = head;

    while(temp != NULL)
    {
		printf("%d->", temp->data);
		printf("%lf->", temp->number);
		printf("%s", temp->name);
		printf("\t");
		temp = temp->next;
    }
    
    printf("NULL\n\n");
}

/*Do not modify the following function.*/

void print_array(struct node_list *array, int sizeof_array)
{
	int i;
	
	for(i=0;i<sizeof_array;i++)
	{
		printf("%d->", (array+i)->data);
    	printf("%lf->", (array+i)->number);
		printf("%s", (array+i)->name);
		printf("\t");
	}
    	printf("NULL\n\n");
}

/*You can modify following functions.*/

struct node_list* merge_list(struct node_list* head_1, struct node_list* head_2)
{
	/* İki liste bir birine eklenecek */
	struct node_list *cursor = head_1;
	
	/* 1. Listenin sonuna git */
	while(cursor->next != NULL)
	{
		cursor = cursor->next;
	}
	/* 2. Listeyi 1. listenin sonuna ekle */
	cursor->next = head_2;
	return head_1;
}

struct node_list* merge_interleaved(struct node_list* head_1, struct node_list* head_2)
{
	/* a0 -> b0 -> a1 -> b1 -> a2 -> b2 .... b5 -> b6 -> b7.... */
	struct node_list *head = head_1;
	
	/* MISSION FAILED */
	return head;
}

struct node_list* merge_array(struct node_list* a, int na, struct node_list* b, int nb)
{
	/* Creating an dynamic array */
	struct node_list *arr = calloc((na + nb), sizeof(struct node_list));
	int counter = 0;
	int i = 0, j = 0;

	/* Counter toplam array boyutuna ulaşana kadar */
	while(counter < (na + nb))
	{
		if (counter % 2 == 0)				/* İlk döngüde 1. arrayi merged_array'e ekle */
		{
			if (i == na)					/* 1. array daha kısa ise geri kalan yerleri 2. array ile doldur */
			{
				while(counter < na + nb)
				{
					arr[counter] = b[j];
					j++;
					counter++;
				}
			}
			arr[counter] = a[i];
			i++;
		}
		else								/* 2. döngüde 2. arrayi merged_array'e ekle */
		{
			if (j == nb)					/* 2. array daha kısa ise geri kalan yerleri 1. array ile doldur */
			{
				while(counter < na + nb)
				{
					arr[counter] = a[i];
					i++;
					counter++;
				}
			}
			arr[counter] = b[j];
			j++;
		}
		counter++;
	}

	return arr;
}


int main()
{
	/*Do not modify anything between 95 and 130 lines.*/
	
	struct node_list *head_1 = NULL;
	struct node_list *head_2 = NULL;
	struct node_list *merged = NULL;
	struct node_list *interleaved = NULL;
	
	insert_end(&head_1,10,1.5,"hello1");
	insert_end(&head_1,30,3.5,"hello3");
	insert_end(&head_1,50,5.5,"hello5");
	 
	insert_end(&head_2,20,2.5,"hello2");
	insert_end(&head_2,40,4.5,"hello4");
	insert_end(&head_2,60,6.5,"hello6");
	
	printf("Print List 1: \n");
	 
	print_list(head_1);
	 
	printf("Print List 2: \n");
	 
	print_list(head_2);
	 
	merged=merge_list(head_1, head_2);
	
	printf("Print List Merged: \n");

    print_list(merged);

	interleaved=merge_interleaved(head_1, head_2);
	
	printf("Print List Interleaved: \n");
	
	print_list(interleaved);
 	
 	/*Do not modify anything between 95 and 130 lines.*/    
 	
	/*YOU CAN MODIFY BELOW THIS LINE FOR ONLY PART 3.*/
	
	/* Statik array oluştur */
	struct node_list a[6] = {{1, 1.2, "a1", NULL}, {3, 3.2, "a3", NULL}, {5, 5.2, "a5", NULL}, {7, 7.2, "a7", NULL}, {9, 9.2, "a9", NULL}, {11, 11.2, "a11", NULL}};
	struct node_list b[5] = {{2, 2.2, "a2", NULL}, {4, 4.2, "a4", NULL}, {6, 6.2, "a6", NULL}, {8, 8.2, "a8", NULL}, {10, 10.2, "a10", NULL}};
	

	/* Array için pointer oluşturup, merger_array fonksiyonuna parametreleri yolla */
	struct node_list *merged_array;
	merged_array = merge_array(a, 6, b, 5);

	/* Dönen array'i yazdır */
	for (int i = 0; i < 6 + 5; i++)
	{
		printf("-->%s\n", merged_array[i].name);
	}
	printf("\n");

	/* Free yap */
	free(merged_array);
	return 0;
}
