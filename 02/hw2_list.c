/*
 * Author: Ahmad Omar Javed
 * Student Id: 1001877250
 * Assignment: 2
 * Implementing Linked List
 * Merging 2 sorted Linked List
 * Removing duplicates from Linked List
 * Checking if List is sorted
*/

/*
  NULL LIST is where list_pointer is NULL
  EMPTY LIST is where list has only dummy node
  NULL LIST is treated as unoredered
  EMPTY LIST is treated as ordered
  deleting the list gives a NULL LIST and not EMPTY LIST
*/

/*---------Check header file for functions definitions----------*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "hw2_list.h"

typedef struct node * nodePT;

int main(){
  
  /* VARIABLES 
   * choice: to store the choice of user
   * l1_size: to store the size of L1
   * l2_size: to store the size of L2
   * temp_var: temporary variable
   * i: lopp variable
   * L1: List 1
   * L2: list 2
   * f_name: name of the input file
   * f_ptr: pointer to the input file
   */
  int choice, l1_size, l2_size, i, temp_var;
  struct node * L1 = NULL;
  struct node * L2 = NULL;
  char f_name[50];
  FILE * f_ptr;

/*
 * do-while loop to iterate through the choices and wait for user input
 */
  do{
    /*Show what options user has*/
    print_instructions();

    /*Read the users choice*/
    printf("\nEnter your choice (0-6):   ");
    scanf("%d",&choice);
    switch(choice)
    {
      case 0:
        break;
      /*
       * If user chooses 1 ask user for file name
       * open the file
       * read the size of L1 from the file
       * populate L1
       * read the size of L2 from the file
       * populate L2
       * If the file doesnt exist show error
       * continue the loop from beginning
       * close the file
       */
      case 1:
        printf("\nEnter the name of the file with data: ");
        scanf("%s", f_name);
        f_ptr = fopen(f_name, "r");
        if(f_ptr == NULL){
          printf("\nFile doesn't exists!\n");
          break;
        }
        fscanf(f_ptr, "%d", &l1_size);
        L1 = populate_list(L1, f_ptr, l1_size);
        fscanf(f_ptr, "%d", &l2_size);
        L2 = populate_list(L2, f_ptr, l2_size);
        fclose(f_ptr);
        break;
      /*
       * If user chooses 2, check if the List 1 is sorted or not
       * print the message applicable.
       */
      case 2:
        if(is_increasing(L1)){
          printf("\nYes. L1 is sorted.\n");
        }
        else{
          printf("\nNo. L1 is not sorted\n");
        }
        break;
      /*
       * If user chooses 3, print List 1 with dummy node
       * print List 2 with dummy node
       * check if both the list are sorted in ascending order or not
       * merge the two list if they are in sorted order.
       * show error message if they are not in sorted order
       * print List 1 with dummy node at the end
       */
      case 3:
        printf("\nList 1:\n");
        print_dummy_node(L1);
        print_list_pointer(L1);
        printf("\nList 2:\n");
        print_dummy_node(L2);
        print_list_pointer(L2);
        if(is_increasing(L1) && (is_increasing(L2))){
          merge_lists(L1,L2);
          free(L2);
          L2 = NULL;
        }
        else{
          printf("\nCANNOT MERGE. L1 or L2 or BOTH not sorted\n");
        }
        printf("\nList 1:\n");
        print_dummy_node(L1);
        print_list_pointer(L1);
        break;
      /*
       * If user chooses 4, remove the duplicates from List 1
       * print List 1 with dummy nodes
       */
      case 4:
        remove_duplicates(L1);
        printf("\nList 1:\n");
        print_dummy_node(L1);
        print_list_pointer(L1);
        break;
      /*
       * If user chooses 5, print both the lists with dummy nodes
       */
      case 5:
        printf("\nList 1:\n");
        print_dummy_node(L1);
        print_list_pointer(L1);
        printf("\nList 2:\n");
        print_dummy_node(L2);
        print_list_pointer(L2);
        break;
      case 6:
      /*
       * If user chooses 6, check if List 1 and 2 are empty or not.
       * if not empty destroy the lists.
       */
        if(!is_null(L1)){
          printf("\ndestroying L1.....\n");
          destroy_list(L1);
          L1 = NULL;
        }
        if(!is_null(L2)){
          printf("\ndestroying L2.....\n");
          destroy_list(L2);
          L2 = NULL;
        }
        break;
    }
    if (choice > 6)
      printf("\n INVALID CHOICE. RETRY.\n");
  }
  /*The loop ends if uses chooses 0 or lower number*/
  while(choice > 0);

  //destroy both the list before ending the program to free the memory.
  if(!is_null(L1))
    destroy_list(L1);
  if(!is_null(L2))
    destroy_list(L2);
  return 0; 
}


// Prints the instructions to the user
void print_instructions(){
  printf("\n\n");
  printf("1 - load from file. It will read from file and create 2 linked lists");
  printf(", L1 and L2. If L1 and L2 exist, they are first destroyed and then");
  printf(" they are recreated with data from the file.\n"); 
  printf("2 - check that list L1 is sorted in increasing order.\n");
  printf("3 - merge L1 with L2 and print the resulting list, L1. The result"); 
  printf(" list will be referenced from variable L1. It should check that BOTH"); 
  printf(" lists are sorted in increasing order in order for the merge to work.\n");
  printf("4 - remove duplicates from L1. (this method will assumes L1 is"); 
  printf(" sorted in increasing order.\n");
  printf("5 - print lists L1 and L2.\n");
  printf("6 - destroy L1 and L2 (and free the memory). If L1 and L2 are NULL");
  printf(" it should not crash.\n");
  printf("0 - exit.\n\n");
}




/* checks if given list is null or not
   if the header points to NULL its NULL.
   returns true if header is NULL
   else returns false
  */
bool is_null(struct node * my_list){
  if (my_list == NULL){
    return true;
  }
  return false;
}


/* Checks if the list only has dummy node.
   if the header->next points to NULL it only has dummy node.
   this should always be used in conjugation with above function.
   Check if the list is NULL or not before using this function
   Only use it if the list is not NULL.
   returns true if there is only dummy node in the list
   else returns false.
 */
bool has_dummy_node_only(struct node * my_list){
  if (my_list->next == NULL){
    return true;
  }
  return false;
}

/*
  Prints the dummy node of the given list
  Shows the value stored in the dummy node
  as well as the memory location of the dummy node.
  */
void print_dummy_node(struct node * my_list){
  if (my_list == NULL){
    printf("\n<print_dummy_node>: List is NULL\n");
    return;
  }
  printf("\nDummy node: data = %d (adr = %p)\n", my_list->data, my_list);
  return;
}


/*
  Checks if the function is sorted in ascending order or not
*/
bool is_increasing(struct node * my_list){
  /*
    If the list is null
    The list is considered to be not sorted.
  */
  if(is_null(my_list)){
    printf("\nList is NULL: no increasing order\n");
    return false; // is NULL list considered sorted?
  }
  /*
    If the list has only dummy node
    The list is treated as sorted list.
  */
  if (has_dummy_node_only(my_list)){
    printf("\nList is empty: always treated as sorted\n");
    return true;
  }
  /*
    sets a pointer to the first non-dummy node.
    loops from first node to second last node.
    checks if the value stored in the node is greater than
    the value stored in the next node.
    if any such case is encountered, 
    then the list is not sorted in ascending order
    if no such case is encountered, the list is in ascending order.
  */
  struct node * temp_ptr = my_list->next;
  while(temp_ptr->next!=NULL){
    if (temp_ptr->data > temp_ptr->next->data){
      return false;
    }
    temp_ptr = temp_ptr->next;
  }
  return true;
}


/*
  merges 2 given lists into 1 list
  assumes the the given lists are in ascending order
  the merged list is stored in the first list.
*/
void merge_lists(struct node * l1, struct node * l2){
  /*
    create 3 pointers
    pointer 1 to point to nodes in first list
    pointer 2 to point to nodes in second list
    main pointer to store the final order of the nodes.
  */
  struct node * temp_1 = l1;
  struct node * temp_2 = l2;
  struct node * main_ptr = l1;

  /*ignore dummy pointers from the list*/
  temp_1 = temp_1->next;
  temp_2 = temp_2->next;

  /*
    how is it merging?
    the loop runs till both the pointers are null
    4 possible cases:
    1) if the pointer 1 is null, it means
    only nodes from list 2 are remaining hence,
    main pointer->next points to the list 2 pointer
    list 2 pointer is moved to the next node.
    2) if the pointer 2 is null, it means
    only nodes from list 1 are remaining hence,
    main pointer->next points to the list 1 pointer
    list 1 pointer is moved to the next node.
    3) both pointers are not null, but
    value in pointer 1 > value in pointer 2
    main should point to pointer 2 and pointer 2 is moved to next node
    pointer 1 remains where it is.
    4) both pointers are not null, but
    value in pointer 2 > value in pointer 1
    main should point to pointer 1 and pointer 1 is moved to next node
    pointer 2 remains where it is.
    always move main pointer to point to next node at the end of the loop.
  */
  while(temp_1 != NULL || temp_2 != NULL){
    if(temp_1 == NULL){
      main_ptr->next = temp_2;
      temp_2 = temp_2->next;
      break;
    }
    else if(temp_2 == NULL){
      main_ptr->next = temp_1;
      temp_1 = temp_1->next;
      break;
    }
    else if (temp_1->data > temp_2->data){
      main_ptr->next = temp_2;
      temp_2 = temp_2->next;
    }
    else{
      main_ptr->next = temp_1;
      temp_1 = temp_1->next;
    }
    main_ptr= main_ptr->next;
  }
  l2->next = NULL;
}

/*
  removes the duplicate values from the given list.
  assumes that the given list is sorted in ascending order
*/
void remove_duplicates(struct node * my_list){
  /*
   create 2 pointers, main pointer to point to the current value
   temp pointer that stores the value temporarily so that the chain isn't lost.
  */
  struct node * main_ptr = my_list;
  struct node * temp_ptr = NULL;

  /*
    how are duplcates removed?
    loop till the second last node
    check if the value in current node is equal to the value in next node
    if true, remove the next node, and current node points to next next node.
    if false, move the current pointer to next node.
  */
  while (main_ptr->next!=NULL){
    if(main_ptr->data == main_ptr->next->data){
      temp_ptr = main_ptr->next;
      main_ptr->next = temp_ptr->next;
      free(temp_ptr);
      continue;
    }
    main_ptr = main_ptr->next;
  }
  return;
}

/*
  populates a list with values from input file
*/
struct node * populate_list(struct node * my_list,  FILE * ptr, int size){
  /*
    Variables
    i: loop variable
    temp_var: store the node data temporarily
    curr_ptr: ptr to the current node
  */
  int i, temp_var;
  struct node * curr_ptr = NULL;
  /*
    check if given list is null or not
    destroy the given list if not null
  */
  if(!is_null(my_list)){
    destroy_list(my_list);
  }
  printf("\nReading list from file....\n");
  /*
  create a new list
  and set curr_ptr to point to the first dummy node.
  */
  my_list = new_list();
  curr_ptr = my_list;
  /*
  loop for the number of items to be added in the list
  read value from the file 
  create a new node with the value read from file.
  set the next node equal to new node.
  move the current pointer to next node.
  */
  for (i=0; i<size; i++){
    fscanf(ptr, "%d", &temp_var);
    struct node * my_node = new_node(temp_var, NULL);
    curr_ptr->next = my_node;
    curr_ptr = my_node;
  }
  return my_list;
}

//----------------------------------------------------------//
nodePt list_from_list (nodePT L){
	nodePT curr_ptr = L;
	nodePT new_list = new_list();
	nodePT new_list_ptr = new_list;
	while (curr_ptr != NULL)
	{
		nodePT temp = new_node(curr_ptr->data, NULL);
		new_list_ptr->next = temp;
		new_list_ptr = new_list_ptr->next;
		curr_ptr = curr_ptr->next;
	}
	return new_list;
}

voide delete (nodePT L)
{
	nodePT curr = L;
	nodePT next = NULL;
	while(curr!=NULL){
		next = curr->next;
		free(curr)
		curr = next;
	}
}

void reverse(nodePT L){
	//assuming dummy list
	nodePT curr = L->next;
	nodePT previous = L;
	while (curr != NULL){
		nodePT temp = curr->next;
		if (previous == L){
			curr->next = NULL;
		}
		else{
			curr->next = previous;
		}
		previous = curr;
		curr = temp;
	}
}

nodePT removeKth(nodePT L, int k){
	nodePT curr = L;
	nodePT prev = NULL;
	for(i = 0; i <= k; curr!=NULL; i++; prev = curr; curr = curr-> next);
	if (curr == NULL){
		printf("Node not found");
		return NULL;
	}
	else{
		prev->next = curr->next;
		return curr;
	}
}

nodePT removeByValue(nodePT nd, int val){
	nodePT curr = L;
	nodePT prev = NULL;
	while (curr!=NULL && curr->data!=k){
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL){
		printf("Node not found");
		return NULL;
	}
	else{
		prev->next = curr->next;
		return curr;
	}
}

void insert(nodePT L, int val)
{
	nodePT curr = L;
	nodePT prev = NULL;
	nodePT mynode = new_node(val, NULL);
	while(curr != NULL && cur->data < val){
		prev = curr;
		curr = curr->next;
	}
	if(curr == NULL){
		prev->next = mynode;
	}
	else{
		prev->next = mynode;
		mynode->next = curr;
	}
}

void insertKth(nodePT L, int k, int val){
	nodePT curr = L;
	nodePT prev = NULL;
	mynode = new_node(val, NULL);
	for (i=0; i<k; curr != NULL; i++; prev = curr; curr=curr->next);
	prev-> next = mynode;
	mynode->next = curr;
}