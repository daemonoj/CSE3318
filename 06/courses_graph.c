/*
Ahmad Omar Javed
1001877250

Special file:
Case: Only one course with dependency on itself. This is a cyclic graph and shouldn't give any output.
Special file #2:
Case: No prerequisites for any course. Disjoined graph, where we have no edges only vertices.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILENAME_LEN 30
#define COURSELEN 30
#define NUMOFLINE 1000

void print_2D(int ** d_arr, int len);
bool DFS_visit(int ** g, int u, int * color, int * ret, int* indx, int n);
int * DFS(int ** g, int n);
void free_int_2D(int ** int_arr, int len);
void free_char_2D(char ** str_arr, int len);

int main()
{
	char content;
	int lineCount = 0, i, j;
	char * fileName = malloc(MAX_FILENAME_LEN * sizeof(char));
	printf("This program will read, from a file, ");
	printf("a list of courses and their prerequisites ");
	printf("and will print the list in which to take courses.\n");
	printf("Enter filename: ");
	scanf("%s", fileName);
	//get number of vertices
	//countLines in File
	FILE * fptr = fopen(fileName,"r");
	if(fptr==NULL)
	{
		printf("Couldn't open the file '%s'. EXIT.\n", fileName);
		free(fileName);
		printf("Failed to read from file. Program will terminate.\n");
		return -1;
	}
	while(fscanf(fptr, "%c", &content)!= EOF)
	{
		if(content == '\n')
			lineCount++;
	}
	
	printf("Number of vertices in built graph:  N = %d\n", lineCount);
	
	int ** graph = malloc(lineCount*sizeof(int*));
	
	char ** course = malloc(lineCount * sizeof(char*));
	
	for(i = 0; i< lineCount; i++)
		graph[i] = calloc(lineCount,sizeof(int));
	
	for(i = 0; i < lineCount; i++)
		course[i] = malloc(COURSELEN * sizeof(char));
	
	bool first_space = true;
	char * courseName = malloc(COURSELEN * sizeof(char));

	// fptr = fopen(fileName,"r");
	fseek(fptr, 0 ,SEEK_SET);
	i = 0;
	j = 0;
	while(fscanf(fptr, "%c", &content)!= EOF)
	{		
		if(first_space && content == ' ' || first_space && content == '\n')
		{
			courseName[i] = '\0';
			i = 0;
			strcpy(course[j],  courseName);
			j++;
			if(content == ' ')
				first_space = false;
		}
		else if (content == '\n')
		{
			i = 0;
			first_space = true;	
		}
		else if(content == ' ')
		{
			i = 0;
		}
		else
		{
			courseName[i++] = content;
		}
	}
	// fclose(fptr);

	printf("Vertex - coursename correspondence\n");
	for(i = lineCount - 1; i>= 0; i--)
	{
		printf("%d - %s\n", i, course[i]);
	}

	fseek(fptr, 0 , SEEK_SET);
	// fptr = fopen(fileName,"r");

	int idx = 0;
	int ptr = 0;
	while(fscanf(fptr, "%c", &content)!= EOF)
	{
		if(first_space && content == ' ' || first_space && content == '\n')
		{
			courseName[idx] = '\0';
			idx = 0;
			for(i = 0; i< lineCount; i++ )
			{
				if(strcmp(course[i], courseName) == 0)
					ptr = i;
			}
			if(content == ' ')
				first_space = false;
		}
		else if(content == ' ')
		{
			courseName[idx] = '\0';
			idx = 0;
			for(i = 0; i< lineCount; i++ )
			{

				if(strcmp(course[i], courseName) == 0)
				{
					graph[i][ptr] = 1;
				}
			}			
		}
		else if (content == '\n')
		{
			i = 0;
			courseName[idx] = '\0';
			idx = 0;
			for(i = 0; i< lineCount; i++ )
			{
				if(strcmp(course[i], courseName) == 0)
					graph[i][ptr] = 1;
			}	
			first_space = true;
		}
		else
		{
			courseName[idx++] = content;
		}
	}
	fclose(fptr);
	printf("\nAdjacency Matrix: \n");
	print_2D(graph, lineCount);
	int * ret = DFS(graph, lineCount);
	if(ret != NULL)
	{
		printf("\n\nOrder in which to take courses:\n");
		for(int i = lineCount - 1; i>=0; i--)
		{
			printf("%d. - %s (corresponds to graph vertex %d)\n", lineCount - i, course[ret[i]], ret[i]);
		}
		free(ret);
	}
	free_char_2D(course, lineCount);
	free_int_2D(graph, lineCount);
	free(fileName);
	free(courseName);
}



void print_2D(int ** d_arr, int len)
{
	int i,j;
	printf("   |");
	for(i = 0; i< len; i++)
		printf("%3d|", i);
	printf("\n");
	printf("----");
	for(i = 0; i<len; i++)
		printf("----");
	printf("\n");
	for(i=0;i<len;i++)
	{
		printf("%3d|", i);
		for(j = 0; j< len; j++)
		{
			printf("%3d|", d_arr[i][j]);
		}
		printf("\n");
	}
}

int * DFS(int ** g, int n)
{
	/*
		WHITE = 0
		GREY = 1
		BLACK = -1
	*/
	int i = 0;
	bool flag;
	int * color = calloc(n, sizeof(int));
	int * pred = calloc(n, sizeof(int));
	for(i = 0; i< n; i++)
		pred[i] = -1;
	int index = 0;
	for(i=0;i<n;i++)
	{
		if(color[i] == 0)
		{
			flag = DFS_visit(g,i, color, pred, &index, n);
		}
		if(flag)
		{
			printf("\n\nThere was at least one cycle.");
			printf(" There is no possible ordering of the courses.\n");
			free(color);
			free(pred);
			return NULL;
		}
	}
	free(color);
	return pred;
}

bool DFS_visit(int ** g, int u, int * color, int * ret, int * indx, int n)
{
	int i;
	color[u] = 1;
	bool flag;
	for(i=0;i<n;i++)
	{
		if(g[u][i] == 1)
		{
			if(color[i] == 0)
			{
				flag = DFS_visit(g, i, color, ret, indx, n);	
				if(flag)
					return true;
			}
			if(color[i] == 1)
			{
				return true;
			}
		}
	}
	color[u] = -1;
	ret[(*indx)++] = u;
	return false;
}

void free_char_2D(char ** str_arr, int len)
{
	int i;
	for(i=0; i<len; i++)
		free(str_arr[i]);
	free(str_arr);
}

void free_int_2D(int ** int_arr, int len)
{
	int i;
	for(i=0; i<len; i++)
		free(int_arr[i]);
	free(int_arr);
}
