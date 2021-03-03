/* 
 * Updated 2/11/2020 - Alexandra Stefan
 */


#ifndef LIST_H
#define	LIST_H

struct node {
    int data;
    struct node * next;
};

struct node * build_list_of_ints();
struct node * array_2_list(int arr[], int sz);
    
/* Creates a new node, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
struct node * new_node(int value_in, struct node * next_in);

/*  Note that these functions may not have all the security checks.
E.g. not all the functions reading and setting members of a node pointer, 
check that the node is not NULL  */


/*  --------  LIST  */
// List implementation uses a DUMMY NODE

// Creates and returns an empty list.
struct node * new_list();

void destroy_list(struct node * Ld);

// Iterates through list and counts nodes.
int compute_length(struct node * Ld);  

// Inserts new_node to the specified list, at the position right after
// the node called "previous".
void insert_node(struct node * previous, struct node * new_node);

void print_list_vert(struct node * my_list);

void print_list_horiz(struct node * my_list);

void print_list_pointer(struct node * my_list);
   
#endif	/* LIST_H */

