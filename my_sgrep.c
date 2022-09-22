//
//  my_sgrep.c
//  
//
//  Created by Devin Reina on 9/21/22.
//

#include <stdio.h>
#include <string.h>

// checks for -h -p -c -n in terminal line
void parseText(char** chars, int size, int* isPattern, int* location, int* isHead, int* isColor, int* isLineNum)
{
    for(int i = 0; i < size; i++)
    {
        if(strcmp(chars[i], "-h") == 0)
        {
            *isHead = 1;
        }
        if(strcmp(chars[i], "-n") == 0)
        {
            *isLineNum = 1;
        }
        if(strcmp(chars[i], "-p") == 0)
        {
            *isPattern = 1;
            *location = i;
        }
        if(strcmp(chars[i], "-c") == 0)
        {
            *isColor = 1;
        }
    }
}

int main(int argc, char **argv)
{
    char input [1024];
    int isHead = 0;
    int isPattern = 0;
    int isColor = 0;
    int isLineNum = 0;
    int pLocation = 0;
    
    // only terminal argument is executable
    if(argc == 1)
    {
        printf("Usage: ./sgrep [-n] [-c] [-h] [-p PATTERN]... FILE...\n");
        return 0;
    }
    
    // parse commands
    parseText(argv, argc, &isPattern, &pLocation, &isHead, &isColor, &isLineNum);
    
    // if -h is included
    if(isHead == 1)
    {
        printf("Usage: ./sgrep [-n] [-c] [-h] [-p PATTERN]... FILE...\n");
        return 0;
    }
    else
    {
        FILE *file = fopen(argv[argc-1], "r");
        
        
        if(file == NULL)
        {
            printf("Could not open file\n");
        }
        else
        {
            // if -p included
            if(isPattern)
            {
                char* pattern = argv[pLocation + 1];
                char* x;
                /* Read one character at a time from file, stopping at EOF, which
                indicates the end of the file. Note that the idiom of "assign
                to a variable, check the value" used below works because
                the assignment statement evaluates to the value assigned. */
                while(x)
                {
                    x = fgets(input, sizeof(input), file);
                    if(feof(file)) break;
                    
                    if(strstr(input, pattern) != NULL)
                    {
                        printf("%s", input);
                    }
                }
                fclose( file );
            }
            
        }
    }
    
    
}
