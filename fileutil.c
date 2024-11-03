#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

char ** loadFileAA(char *filename, int *size)
{
    FILE *in = fopen(filename, "r");
    if (!in)
    {
        perror("Can't open file");
        exit(1);
    }
    
    char buffer[COLS];
    char **arr = NULL;
    int capacity = 10;
    *size = 0;
    
    // Initial allocation
    arr = malloc(capacity * sizeof(char*));
    
    while (fgets(buffer, COLS, in))
    {
        // Trim newline
        char *nl = strchr(buffer, '\n');
        if (nl) *nl = '\0';
        
        // Expand array if needed
        if (*size >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(char*));
        }
        
        // Allocate and copy string
        arr[*size] = malloc(strlen(buffer) + 1);
        strcpy(arr[*size], buffer);
        (*size)++;
    }
    
    fclose(in);
    return arr;
}

char * substringSearchAA(char *target, char **lines, int size)
{
    for (int i = 0; i < size; i++) {
        if (strstr(lines[i], target) != NULL) {
            return lines[i];
        }
    }
    return NULL;
}

void freeAA(char ** arr, int size)
{
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
