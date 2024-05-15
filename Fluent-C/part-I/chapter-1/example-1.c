#include <stdio.h>

#define ERROR ""
#define BUFFER_SIZE 0
#define NO_KEYWORD_FOUND 0
#define KEYWORD_ONE_FOUND_FIRST ""
#define KEYWORD_TWO_FOUND_FIRST ""

/* A function that parses a file for certain keywords and that
returns information on which of the keywords was found.*/
int parseFile(char *file_name)
{
    int return_value = ERROR;
    FILE *file_pointer = 0;
    char *buffer = 0;
    if (file_name != NULL)
    {
        if (file_pointer = fopen(file_name, "r"))
        {
            if (buffer = malloc(BUFFER_SIZE))
            {
                /* parse file content*/
                return_value = NO_KEYWORD_FOUND;
                while (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
                {
                    if (strcmp("KEYWORD_ONE\n", buffer) == 0)
                    {
                        return_value = KEYWORD_ONE_FOUND_FIRST;
                        break;
                    }
                    if (strcmp("KEYWORD_TWO\n", buffer) == 0)
                    {
                        return_value = KEYWORD_TWO_FOUND_FIRST;
                        break;
                    }
                }
                free(buffer);
            }
            fclose(file_pointer);
        }
    }
    return return_value;
}