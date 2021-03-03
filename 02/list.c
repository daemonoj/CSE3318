/* 
 * Updated 2/11/2020 - Alexandra Stefan
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
struct node * new_node(int value_in,  struct node * next_in) {
    struct node * result = (struct node *) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = next_in;
    return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list with a dummy node. */
struct node * new_list() {
	struct node * dummy = new_node(-9999,NULL);
    return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(struct node * Ld) {
    struct node * next;
	struct node * current = Ld;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Inserts new_node after the node called "previous". 
void insert_node(struct node * previous, struct node * new_node) {
    if (previous == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");        		
    } else {
        new_node->next = previous->next;
        previous->next = new_node;
    }    
}

// Returns 0 for empty lists (that have just one dummy node) and NULL lists 
int compute_length(struct node * Ld) {
    if (Ld == NULL) {
        return 0;
    }

    int counter = 0;
    struct node * curr;
    for (curr = Ld->next; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}


// does not print the dummy node
void print_list_vert(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");    
        return;
    }
    int i = 0;
    struct node * curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);    
}


// does not print the dummy node
void print_list_horiz(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");    
        return;		
    }
    int i = 0;    
    struct node * curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    
}

// does not print the dummy node
void print_list_pointer(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_pointer> : List is NULL\n");    
        return;
    }

    int i = 0;    
    struct node * curr;	
    printf("\n List items:    ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%9d ", curr->data);
        i++;
    }    
    printf("\n List pointers: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    	
}

// Builds and returns a list with integers read from standard input.
 struct node * build_list_of_ints() {  
   struct node * Ld = new_list();
   struct node * last_node = Ld; // the last (and only) node in the list is the dummy node.
   printf("This program builds a list with integers from the user (stops when a non-integer was entered)\n");
   while(1)
   {
      int number;
      printf("please enter an integer: ");     
      int items_read = scanf("%d", &number);
      if (items_read != 1)  // There are no more integers in the read buffer => STOP 
      {
         break;
      }
     
      // allocate memory for the next node 
      struct node * new_node_ptr = new_node(number, NULL);
      insert_node(last_node, new_node_ptr);
      last_node = new_node_ptr;
   }   
   return Ld;
}


struct node * array_2_list(int arr[], int sz)  {  
	int i; 		
	struct node * last_node, *new_node_ptr;
	struct node * A = new_list();
	
	last_node = A;  // the last (and only) node of A is the dummy node.
	for (i = 0; i < sz; i++) 	{
		new_node_ptr = new_node(arr[i], NULL);
		insert_node(last_node, new_node_ptr);
		last_node = new_node_ptr;
	}	
	return A;
}

//---------Node functions End---------

