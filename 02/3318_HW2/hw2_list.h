/*
 * Author: Ahmad Omar Javed
 * Student Id: 1001877250
 * Assignment: 2
 * Implementing Linked List
 * Merging 2 sorted Linked List
 * Removing duplicates from Linked List
 * Checking if List is sorted
 */

/*-----------------------------------------------*/
/*-------------Function definitons---------------*/
/*-----------------------------------------------*/


/*
 * Function: print_instructions
 * ----------------------------
 * shows the choices available to the user on terminal
 * Choices 1-6 are printed on the terminal.
 * arguments: NA
 * return type: void
 */
void print_instructions();


/*
 * Function: is_null
 * ----------------------------
 * Checks if the linked list is NULL or not
 * Given Linked List is NULL if there is no dummy
 * or other nodes present in it i.e. the pointer points to NULL
 * argument type: struct node * 
 * arguments: my_list (the linked list that is to be checked)
 * return type: bool
 * returns true or false
 */
bool is_null(struct node * my_list);


/*
 * Function: has_dummy_node_only
 * ------------------------------
 * Checks if the linked list has only dummy node
 * argument type: struct node * 
 * arguments: my_list (the linked list that is to be checked)
 * return type: bool
 * returns true or false 
 */
bool has_dummy_node_only(struct node * my_list);


/*
 * Function: print_dummy_node
 * ------------------------------
 * Prints the dummy node of the linked list
 * if the linked list is not NULL.
 * "Dummy Node: data = <data> (adr = <address>)"
 * if list is null prints "print_dummy_node>: List is NULL"
 * argument type: struct node * 
 * arguments: my_list (the linked list that is to be checked)
 * return type: void
 */
void print_dummy_node(struct node * my_list);


/*
 * Function: is_increasing
 * ------------------------------
 * Checks if the given linked list is sorted
 * in ascending order or not.
 * if list is null or has only dummy node
 * prints "List with no nodes: no increasing order"
 * and returns false
 * argument type: struct node * 
 * arguments: my_list (the linked list that is to be checked)
 * return type: bool
 * returns true or false
 */
bool is_increasing(struct node * my_list);


/*
 * Function: merge_lists
 * ------------------------------
 * Merges two given linked lists in ascending order.
 * smaller elements come before larger elements.
 * Assumes that the given lists are in ascending order.
 * the merged list is stored in the first list in the argument
 * argument type: struct node * , struct node *
 * arguments: l1, l2 (the linked list that is to be checked)
 * return type: void
 */
void merge_lists(struct node * l1, struct node * l2);


/*
 * Function: remove_duplicates
 * --------------------------------------------
 * Removes all the duplicate elements present in
 * the given list.
 * The first element in the duplicates is kept with memory location.
 * all other duplicates with memory locations are cleaned.
 * assumes that the given list is sorted in ascending order.
 * argument type: struct node *
 * arguments: my_list
 * return type: void
 */
void remove_duplicates(struct node * my_list);


/*
 * Function: populate_list
 * ---------------------------------------------------
 * Reads list of integers from the given file pointer
 * and creates a list with the integers read
 * number of integers read is equal to the size given to the function
 * Checks if the given list is NULL or not.
 * Deletes the given list if it is not empty, freeing up the memory
 * Creates a new list and stores the numbers in it.
 * returns the populated list.
 * argument types: struct node*, File *, int
 * arguments: my_list(the list checked whether empty or not)
 * 			  ptr (pointer to the file where input is located)
 *  		  size (size of the list/number of integers to be read from the file)
 * return type: strucgt node *
 * returns the populated list.
 */
struct node * populate_list(struct node * my_list,  FILE * ptr, int size);
