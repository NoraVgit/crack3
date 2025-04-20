#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"   
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.
int comparison(const void * a, const void* b)
{
    char **aa = (char**)a;
    char **bb = (char**)b;
    return strcmp(*aa,*bb);
}

void removeNL(char * string)//removes new line and replaces with string termination
{
    for(int i = 0; string[i] != '\0'; i++)
        if(string[i] == '\n')
        {
            string[i] = '\0';
            return;
        }
    return;
}
int main(int argc, char *argv[])
{
 
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort. // COMPLETE
    qsort(hashes,size,sizeof(char * ),comparison); 

    // TODO
    // Open the password file for reading.

    //int nofp;
    //char **passes = loadFileAA(argv[2],&nofp);
    FILE * passwords = fopen(argv[2],"r");//open the passwords file for reading
    char password[PASS_LEN];//for storing of passwords of pass_len length or less
    
    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search. //COMPLETE
    int noffound = 0;//number of found
    while(fgets(password,PASS_LEN,passwords) != NULL)//read the passwords file and assign each line to a password of pass_len
    {
        removeNL(password);//removes the new line char in password
        
        char * hash = md5(password,strlen(password));//pointer to hash created with md5 and the plaintxt password
        char * found = bsearchAA(hash,hashes,size);//seach for the generated hash from the list of hashes
        if(found)//if the hash is found
        {
            printf("%s %s\n",found,password);//display it to the user
            noffound++;//increase the number of the found hashes
        }
        else
            printf("not found\n");//else tell the user the pass isnt found
    }
    
    // TODO
    // When done with the file:
    //   Close the file
    //   Display the number of hashes found.
    //   Free up memory.
    printf("\n%d hashes found!\n", noffound);//display to the user how many hashes were found
    fclose(passwords);
    freeAA(hashes,size);
}
