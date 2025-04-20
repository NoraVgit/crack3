#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	*size = 0;//assign pointer to an int value
	//++*size;
	//printf("%d",*size);
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	char line[100];
	int cap = 10;
	// TODO
	// Allocate memory for an array of strings (arr).
	char **arr = malloc(cap * sizeof(char *));//mem for array of strings so array of array
	// Read the file line by line.
	while(fgets(line,99,in) != NULL)
	{
    	//   Trim newline.
		
		int i = 0;
		while(line[i] != '\0' && line[i] != '\n')//if line at i does equal the end of string or a new line increase i by 1
			i++;
		
		if(line[i] == '\n')// if line at i is equal to a new line replace it with an end of string terminator
			line[i] = '\0';
			
		//   Expand array if necessary (realloc).	
		if(*size == cap)// if the number of elements is equal to the capacity of the array increase it
		{
			cap = cap  + (cap/2);//increase cap by half of caps current size
			arr = realloc(arr,cap * sizeof(char *));//reallocate memory
		}
		//   Allocate memory for the string (str).
		arr[*size] = malloc(strlen(line) + 1);
		//   Copy each line into the string (use strcpy).
		strcpy(arr[*size],line);
		//   Attach the string to the large array (assignment =).
		//printf("%s\n",arr[*size]);//debug code
		++*size;//the thing size is pointing to increase by one
	}
    // Close the file.
	fclose(in);
	// The size should be the number of entries in the array.
	
	
	// Return pointer to the array of strings.
	return arr;
}

char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an 2D array, using COLS as the width.
	// Read the file line by line into a buffer.
    //   Trim newline.
	//   Expand array if necessary (realloc).
	//   Copy each line from the buffer into the array (use strcpy).
    // Close the file.
	
	// The size should be the number of entries in the array.
	*size = 0;
	
	// Return pointer to the array.
	return NULL;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	
	for(int i = 0; i < size; i++)
	{
		//printf("%s",lines[i]); test code
		if(strcmp(target,lines[i]) == 0)//if target is found in the array of strings return it
			return lines[i];
	}
	return NULL;
}
char * bsearchAA(char * target, char **lines, int size)
{
	int low = 0;
	int high = size - 1;
	
	while(low <= high)
	{
		int mid = (low + high)/2;
		
		if(strcmp(lines[mid],target) == 0)
			return lines[mid];
		else if(strcmp(lines[mid],target) < 0)//if mid comes before target
			low = mid + 1;
		else
			high = mid - 1;
	}
	return NULL;
}

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    
    return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for(int i = 0; i < size; i++)//for the size of the array
	{
		free(arr[i]);//for every instance of a string held in arr at i clear the malloc memory
	}
	free(arr);//free the whole array
}

void free2D(char (*arr)[COLS])
{

}
