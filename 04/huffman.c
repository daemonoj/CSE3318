/*
Author: Ahmad Omar Javed
Student ID: 1001877250
This program implemets 2 functionalities
1) Encoding a given text file using Huffman Encoding
2) Decoding a given text file with Huffman Tree structure and encoded text.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------Structures----------------------------------//

struct Tuple{
	int weight;
	char alphabet;
};

typedef struct Tuple Tuple;

struct HuffmanNode{
	Tuple t;
	struct HuffmanNode * left;
	struct HuffmanNode * right;
};

typedef struct HuffmanNode HuffmanNode;

//----------------------------------------------------------------------------//



//--------------------------------Constants-----------------------------------//

#define MAX_LEN 80000 // Max length of the file, although 
					 // srcFile is 1000 characters
					 // after encoding the dest file can be as large as 
					 // 8000 characters.
#define ASCII_LEN 128 // total count of ASCII characters to be encoded.

//----------------------------------------------------------------------------//



//---------------------------Function prototypes------------------------------//

char * readFile(char * fileName);
int writeFile(char * fileName, char * content);
void printTupleList(Tuple * t, int size);
Tuple * calculateWeight(char * str, int * tupleListSize);
void insertKey(HuffmanNode * heap, HuffmanNode t, int * size);
void sinkDown(HuffmanNode * heap, int parentIndex, int heapSize);
HuffmanNode removeMin(HuffmanNode * heap, int * heapSize);
void buildHuffmanTree(HuffmanNode * heap, int * heapSize, 
						HuffmanNode* huffmanTree);
void getStartingString(HuffmanNode* root, char * startStr);
char * encodeContent(char * srcFileContent);
void freeTree(HuffmanNode * root);
HuffmanNode * getHuffmanTreefromString(char * str, int * N);
char getCharfromCode(HuffmanNode * root, char * str, int * N);
void decodeContent(char * str);
void getCodes(HuffmanNode* root, int * code, int ptr, char * codes[]);

//----------------------------------------------------------------------------//


/*
	Main method where Magic happens :)
*/
int main(int argc, char * argv[]){
	int choice;
	char destFileName[50];
	char srcFileName[50];
	char * fileContent;
	char * encodedContent;
	
	printf("\nEnter your option (1-encode/ 2-decode): ");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			printf("\nEnter the name of DESTINATION file (encoded file): ");
			scanf("%s", destFileName);
			printf("\nEnter the name of the SOURCE file (to be encoded): ");
			scanf("%s", srcFileName);
			printf("Files:   %s, %s\n", srcFileName, destFileName);
			//read the content of files into a string
			fileContent = readFile(srcFileName);
			if (fileContent){
				//encode it
				encodedContent = encodeContent(fileContent);
				//write it to the destination file.
				int ret = writeFile(destFileName, encodedContent);
				free(fileContent);
				free(encodedContent);
				if(ret == -1){
					printf("Error Writing the file\n");
					return -1; 
				}
			}
			else{
				printf("File not found/ File Content not found\n");
				return -1;
			}
			break;
		case 2:
			printf("\nEnter the name of the DESTINATION file (encoded file): ");
			scanf("%s", destFileName);
			fileContent = readFile(destFileName);
			if(fileContent){
				decodeContent(fileContent);
				free(fileContent);
			}
			else{
				printf("File not found/ File Content not found\n");
				return -1;
			}
			break;
		if (choice != 1 || choice != 2){
			printf("Incorrect option selected. Closing the program.");
			return -1;
		}
	}
	return 0;
}



/*
	Function definition
	This function is used to read the file
	Args:
		fileName: name/path of the file to be read.
	Return type: char *
	Returns a string that contains the content of the file
	Maximum size of the file can be 8000 characters.
	You can change the maximum size by editing the constants MAX_LEN.
	Returns NULL if the file isnt found.
	char * readFile(char * fileName)
*/

char * readFile(char * fileName){	
	char * content = (char *)malloc(MAX_LEN*sizeof(char));
	FILE * fptr = fopen(fileName,"r");
	if (fptr == NULL){
		printf("SOURCE file doesn't exist\n");
		return NULL;
	}
	fgets(content, MAX_LEN, fptr);
	fclose(fptr);
	return content;
}



/*
	Function definition
	This function is used to write content to a file
	Args:
		fileName: name of the file where the content is to be written.
		content: String to be written to the file
	return type: int
	Returns 0 if file is written sucessfully
	Returns -1 if there was an error while writng the file.
*/

int writeFile(char * fileName, char * content){
	FILE * fptr = fopen(fileName, "w");
	if (fptr == NULL){
		printf("ERROR writing the file");
		return -1;
	}
	fprintf(fptr, "%s", content);
	fclose(fptr);
	return 0;
}



/*
	Function definition
	Creates a list of tuples containing the character and their weight
	Args: 
		str contains the string for which we need to get the frequency of all
		characters.
		tupleListSize: pointer to an int which is used to maintain the size
		of tuple list. 
	return type: Tuple *
	returns a tuple list which contains all the characters and their frequencies
	The tuple list returned contains the tuples in sorted order, which is done
	while adding the tuples to the list.
	The list starts at index 1.
*/

Tuple * calculateWeight(char* str, int * tupleListSize){
	//size is started as 1 since 0th position is left empty.
	int i, j, size = 1;
	//tuple list can't be larger than count of all the ascii characters
	Tuple * t = (Tuple *)malloc((ASCII_LEN+1)*sizeof(Tuple));
	for (i = 0; i < strlen(str); i++){
		char c = str[i];
		// check if the character is already in the tuple list
		// loop starts at 1 because the first character is stored at 1.
		for (j = 1; j < size; j++){
			if(t[j].alphabet == c){
				// increase the weight of the character if the character
				// is found in the tuple list 
				t[j].weight++;
				break;
			}
		}
		if (j>=size){
			// add new character if the character isn't already in the list
			// find the right location to insert the new character
			// this is to maintain the list in ordered fashion.
			while(j>1 && t[j-1].alphabet > c){
				// same algorithm as insertion sort.
				// keep shifting the tuples to the next tuple 
				// to make space for the new tuple
				t[j].alphabet = t[j-1].alphabet;
				t[j].weight = t[j-1].weight;
				j--;
			}
			// store the element in the emptied space
			// increase the size.
			t[j].alphabet = c;
			t[j].weight = 1;
			size++;
		}

	}
	// set the int at tupleListSize to size - 1.
	// this is so that we only iterate till size and not read unassigned 
	// locations
	*tupleListSize = size-1;
	// return the tuple list.
	return t;
}



/*
	Function definition
	void printTupleList(Tuple * t, int size)
	Used to print the tuple list
	Args
		t: tuple list that is to be printed
		size: size of the tuple list
	Return type: Void
	If the size provided is 0, it assumes that the
	list provided is a tuple pointer and not tuple list.

	the tuple list is assumed to start from 1 rather than 0
	it prints the tuple in the format (%c, %d).
	%c ---> character
	%d ---> frequency of the character
*/

void printTupleList(Tuple * t, int size){
	int i;
	if(size == 0){
		printf("(%c, %d)\n", t->alphabet, t->weight);
	}
	for (i = 1; i <= size; i++){
		printf("(%c, %d)\n", t[i].alphabet, t[i].weight);
	}
	return;
}



/*
	Function definition
	void insertKey(HuffmanNode * heap, HuffmanNode t, int * heapSize)
	This function is used to add an element in a min heap
	Args: 
		heap: heap where the element is supposed to be inserted
		t: the element to be inserted in the heap
		heapSize: pointer to integer used to maintain the heap size.
	Return type: void
	Asssumes that the heap starts at index 1.							
*/

void insertKey(HuffmanNode * heap, HuffmanNode t, int * heapSize){
	int i;
	// increase the heap size.
	(*heapSize)++;
	i = *heapSize;
	// add the element at the end.
	heap[i] = t;
	// Floating Up the new element.
	// while the new element added has lower frequency than its parent 
	// swap it with the parent
	while(i > 1 && heap[i].t.weight < heap[i/2].t.weight){
		HuffmanNode temp;
		temp = heap[i];
		heap[i] = heap[i/2];
		heap[i/2] = temp;
		i=i/2;
	}
	return;
}



/*
	Function definition
	HuffmanNode removeMin(HuffmanNode * heap, int * heapSize)
	This function returns the minimum from the min heap
	Args: 
		heap: heap from which the min is required
		heapSize: pointer to integer used to maintain the heap size.
	Return type: HuffmanNode
	returns the min node from the heap.
	Assumes that the heap starts at index 1.
*/

HuffmanNode removeMin(HuffmanNode * heap, int * heapSize){
	HuffmanNode ret;
	// check if the heapsize is less than or equal to zero.
	// return NULL
	if(*heapSize <= 0){
		return ret;
	}
	// we need to return 1st element
	// store it in another variable
	ret = heap[1];
	//move last element to 1st index.
	heap[1] = heap[*heapSize];
	// empty out the last element
	heap[*heapSize].t.alphabet = '\0';
	heap[*heapSize].t.weight = 0;
	//decrease the heap size.
	(*heapSize)--;
	// sinkdown the new added element to maintain min heap structure.
	sinkDown(heap, 1, *heapSize);
	//return the first element.
	return ret;
}



/*
	Function definition
	void sinkDown(HuffmanNode * heap, int parentIndex, int heapSize)
	This function sinks down the aprent node provided to it.
	This helps maintain the min heap structure
	Args: 
		heap: heap which needs to be maintained.
		parentIndex: the index of the node that needs to be sunk down.
		heapSize: the size of the heap.
	Return type: void
	Assumes that the heap starts at index 1.
*/

void sinkDown(HuffmanNode * heap, int parentIndex, int heapSize){
	// find the location of the left child and the right child
	int leftChildIndex = 2 * parentIndex;
	int rightChildIndex = 2 * parentIndex + 1;
	// create an index to store the location of the min node.
	// assign it the parent lcoation
	int index = parentIndex;
	// the order of sink down should be left child then right child.
	// check if the left child is less than parent node.
	// if true assign left child index to index.
	if (leftChildIndex <= heapSize && 
		heap[index].t.weight > heap[leftChildIndex].t.weight){
		index = leftChildIndex;
	}
	// check if the right child is less than node at index(parent/left).
	// if true assign right child index to index.
	if (rightChildIndex <= heapSize && 
		heap[index].t.weight > heap[rightChildIndex].t.weight){
		index = rightChildIndex;
	}
	// If we found a child node that is less than parent node
	// Swap Parent with Index.
	if(index != parentIndex){
		HuffmanNode temp;
		temp = heap[index];
		heap[index] = heap[parentIndex];
		heap[parentIndex] = temp;
		//Call sink down at the new index.
		sinkDown(heap, index, heapSize);
	}
	//else the parent node is at its rightful location end the function ends.
}




/*
	Function definition
	void buildHuffmanTree(HuffmanNode * heap, int * heapSize, 
													HuffmanNode* huffmanTree)
	This function builds a huffman tree from the heap.
	Args: 
		heap: heap from which the min is required
		heapSize: pointer to integer used to maintain the heap size.
		huffmanTree: this is a pointer to store the final root for 
					 the huffman tree
	Return type: void.
	Assumes that the heap starts at index 1.
*/

void buildHuffmanTree(HuffmanNode * heap, int * heapSize, 
						HuffmanNode* huffmanTree){
	while(*heapSize>0){
		// creating new nodes for tree, 
		// so that changes to the heap doesnt affect my huffman tree
		HuffmanNode *  nodeL = (HuffmanNode* )malloc(sizeof(HuffmanNode));
		HuffmanNode ret1 = removeMin(heap, heapSize);
		// assign the values to the left node from the first min.
		nodeL->t = ret1.t;
		nodeL->left = ret1.left;
		nodeL->right = ret1.right;
		//check if the heap is empty
		// if so it means this was the last node, which is root node
		// assign the left node to root node
		// free the left node.
		if (*heapSize == 0){
			huffmanTree->t = nodeL->t;
			huffmanTree->left = nodeL->left;
			huffmanTree->right = nodeL->right;
			free(nodeL);
			break;
		}
		// creating new nodes for tree, 
		// so that changes to the heap doesn't affect my huffman tree
		HuffmanNode * nodeR = (HuffmanNode* )malloc(sizeof(HuffmanNode));
		HuffmanNode ret2 = removeMin(heap, heapSize);
		// assign the values from the 2nd min to my right node.
		nodeR->t = ret2.t;
		nodeR->left = ret2.left;
		nodeR->right = ret2.right;
		// creating parent node for left and right node
		// this will be an internal node
		HuffmanNode * nodeP = (HuffmanNode*)malloc(sizeof(HuffmanNode));
		nodeP->t.alphabet = '\0';
		nodeP->t.weight = nodeL->t.weight + nodeR->t.weight;
		nodeP->left = nodeL;
		nodeP->right = nodeR;
		// insert the parent to the heap.
		insertKey(heap, *nodeP, heapSize);
		printf("buildHuffmanTree: (%c, %d) + (%c, %d) -> (%c, %d);\t\tN=%d\n", 
				nodeL->t.alphabet =='\0'?'$':nodeL->t.alphabet,
				nodeL->t.weight, nodeR->t.alphabet =='\0'?'$':nodeR->t.alphabet,
				nodeR->t.weight, '$', nodeP->t.weight, *heapSize);
		// free parent node
		// the parent node is passed as value and not pointer.
		// this will not affect my heap.
		free(nodeP);
	}
	return;
}



/*
	Function definition
	void getCodes(HuffmanNode* root, int * code, int ptr, char * codes[])
	Args:
		root: root node for the HuffmanTree.
		code: the array to store the path of the charaters
		ptr: the index where the path value is to be added.
		codes: string array where codes for each character is stored
				the location is ascii code of the character.
	Return type: void
*/

void getCodes(HuffmanNode* root, int * code, int ptr, char * codes[]){
    // if there is a left child, add 0 to the code
    // move left.
    if (root->left) { 
        code[ptr] = 0; 
        getCodes(root->left, code, ptr + 1, codes); 
    }
    // if there is a right child, add 0 to the code
    // move right.
    if (root->right) { 
        code[ptr] = 1; 
        getCodes(root->right, code, ptr + 1, codes); 
    }
    // if we are at a child node,
    // store the code in the string array.
    if (root->left == NULL && root->right == NULL) {
        int i;
        int c = root->t.alphabet;
        printf("%c - ", c);
        codes[(int)c] = (char*) malloc((ptr+1)*sizeof(char));
        for (i=0; i<ptr; i++){
    		codes[(int)c][i] = (char)(code[i]+48);
        	printf("%d", code[i]);
        }
     	codes[(int)c][i] = '\0';
        printf("\n"); 
    } 
} 



/*
	Function definition
	void getStartingString(HuffmanNode* root, char * startStr)
	Args:
		root: root node for the HuffmanTree.
		starStr: starting string to store the code for huffmantree
	Return type: void
*/

void getStartingString(HuffmanNode* root, char * startStr){
	if (root == NULL){
		return;
	}
	if (root->left == NULL && root->right == NULL){
		char c[2];
		c[0] = root->t.alphabet;
		c[1] = '\0';
		strcat(startStr, "1");
		strcat(startStr, c);
		return;
	}
	strcat(startStr, "0");
	getStartingString(root->left, startStr);
	getStartingString(root->right, startStr);
}



/*
	Function definition
	char * encodeContent(char * srcFileContent)
	This function returns the encoded string after generating the huffman tree
	Args:
		srcFileContent: content of the source file to be encoded.
	Return Type: char *
	assumes that the srcFileContent exists, and is not NULL.
*/

char * encodeContent(char * srcFileContent){
	int j,i;
	int code[10];
	int ptr = 0;
	char * codes[128];
	// to store the encoded string.
	char * encodedStr = (char*)malloc(8000*sizeof(char));
	encodedStr[0] = '\0';
	// Node to store the root of tree.
	HuffmanNode * huffmanTree = (HuffmanNode*)malloc(sizeof(HuffmanNode));
	int * heapSize = (int *) malloc(sizeof(int));
	int * tupleListSize = (int *)malloc(sizeof(int));
	Tuple * t = calculateWeight(srcFileContent, tupleListSize);
	HuffmanNode * heap = 
			(HuffmanNode*)malloc((*tupleListSize + 1) * sizeof(HuffmanNode));
	// set heapSize to tupleList size, since both will be the same.	
	*heapSize = *tupleListSize;
	printTupleList(t, *tupleListSize);
	printf("---------------------------------------------------------\n");
	// store the tuples in the list to the heap as nodes.
	for (i = 0; i <= *tupleListSize; i++){
		heap[i].t = t[i];
		heap[i].left = NULL;
		heap[i].right = NULL;
	}
	int * tempHeapSize = (int*)malloc(sizeof(int));
	*tempHeapSize = *heapSize;
	// Call Sink down for all internal nodes of list //
	//last parent node should be present at size/2.
	int parentNode = (*heapSize)/2;
	int cntr;
	for(cntr = parentNode; cntr>0; cntr--){
		sinkDown(heap, cntr, *heapSize);
	}
	// build huffman tree.
	buildHuffmanTree(heap, tempHeapSize, huffmanTree);
	printf("---------------------------------------------------------\n");
	getStartingString(huffmanTree, encodedStr);
	getCodes(huffmanTree, code, ptr, codes);
	// iterate through the string, for each character encountered 
	// add the code for the character in the encoded String.
	for (j = 0; j < strlen(srcFileContent); j++){
		char * code;
		char c = srcFileContent[j];
		code = codes[(int)c];
		strcat(encodedStr, code);
	}

	// free the encoding table.
	for (j=1; j<=*tupleListSize; j++){
		free(codes[(int)t[j].alphabet]);
	}
	free(t);
	free(heap);
	free(heapSize);
	free(tempHeapSize);
	free(tupleListSize);
	freeTree(huffmanTree);
	return encodedStr;
}



/*
	Function definition
	void freeTree(HuffmanNode * root)
	This function frees up a given huffman tree.
	Args
		root: the root node of the tree that is to be freed
	return type: void 
*/

void freeTree(HuffmanNode * root){
	if (root == NULL){
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	free(root);
	return;
}



/*
	Function definition
	HuffmanNode * getHuffmanTreefromString(char * str, int * N)
	This function is used while decoding
	It generates a huffman tree from the string in decoding file
	The string must follow the pattern: 0 for internal node,
	1 for leaf node, followed by the character to be stored in leaf node.
	
	Args
		str: the string that contains the structure of huffman tree 
		and the encoded string
		N: pointer to an integer that stores the number of characters read.
		This pointer will point to the start of the encoded string, which needs 
		to be deciphered, after the huffman tree is generated
	
	Return type: HuffmanNode *
	Assumes that the huffman encoding provided in the string is correct.
*/

HuffmanNode * getHuffmanTreefromString(char * str, int * N){
	HuffmanNode * root = (HuffmanNode*) malloc(sizeof(HuffmanNode));
	// check if the character is 1
	// in that case its a leaf node
	if(str[*N] == '1'){
		// store the leaf node contents
		root->t.alphabet = str[*N + 1];
		root->t.weight = 0;
		root->left = NULL;
		root->right = NULL;
		// increase the pointer by 2 sice 2 characters are read 1, c.
		*N = *N + 2;
		// return this leaf node to the calling function
		return root;
	}
	// check if the character is 0
	// in that case its an internal node
	// all internal nodes will have left and right child.
	if (str[*N] == '0'){
		// set values to default for internal node
		root->t.alphabet = '\0';
		root->t.weight = 0;
		// increase pointer count by 1, since 1 character has been read.
		(*N) = *N + 1;
		// generate the left subtree
		root->left = getHuffmanTreefromString(str, N);
		// generate the right subtree
		root->right = getHuffmanTreefromString(str, N);
	}
	// return the root to the calling function.
	return root;
}



/*
	Function definition
	char getCharfromCode(HuffmanNode * root, char * str, int * N)
	This function returns the character corresponding to the encoded string
	It traverses the path stored in the encoding string, left for 0
	right for 1 and returns the character stored in the leaf node it encounters.
	Args:
		root: the root node of the huffman tree used for encoding the file.
		str: the encoded string
		N: pointer to the integer that holds the number of characters read
		this points to the next characcter that is supposed to be read.
	Assumes that string provided is encoded with given huffman tree and 
	isn't missing any characters in the middle or end	
*/

char getCharfromCode(HuffmanNode * root, char * str, int * N){
	char c;
	// check if we are at a leaf node
	// if yes, return the character stored in the leaf node
	if(root->left == NULL && root->right == NULL){
		return root->t.alphabet;
	}
	// check if the string asks to go left or right
	// increment the pointer since 1 character has been read
	// call the function again for the next character in the string
	if(str[*N] == '0'){
		*N = *N + 1;
		c = getCharfromCode(root->left, str, N);
	}
	else if(str[*N] == '1'){
		*N = *N + 1;
		c = getCharfromCode(root->right, str, N);	
	}
	// return the character found at the leaf node.
	return c;
}



/*
	Function definition
	void decodeContent(char* str)
	Main function to decode the string and print the decoded string
	This function calls sub functions to generate the huffman tree and 
	decode each character.
	Args:
		str: the cstring that needs to be decoded along with the 
		huffman tree structure
	return type: void
	Assumes that the string provided ahs content and follows the 
	established pattern	
*/

void decodeContent(char* str){
	int index = 0, N = 0;
	// string to store the decode content
	char * decodedContent = (char *)malloc(MAX_LEN * sizeof(char));
	decodedContent[0] = '\0';
	// generate the huffman tree from the given structure
	HuffmanNode * root = getHuffmanTreefromString(str, &N);
	// iterate till you reach the end of the file
	// decode each character from the path given in the output file.
	while(N < strlen(str)){
		decodedContent[index++] = getCharfromCode(root, str, &N);
	}
	decodedContent[index] = '\0';
	printf("---------------------------------------------------------\n");
	printf("decoded string: %s\n", decodedContent);
	printf("---------------------------------------------------------\n");
	freeTree(root);
	free(decodedContent);
}
