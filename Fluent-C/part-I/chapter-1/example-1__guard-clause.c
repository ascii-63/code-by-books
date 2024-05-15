#include <stdio.h>

#define ERROR ""
#define BUFFER_SIZE 0
#define NO_KEYWORD_FOUND 0
#define KEYWORD_ONE_FOUND_FIRST ""
#define KEYWORD_TWO_FOUND_FIRST ""

int searchFileForKeywords(char *buffer, FILE *file_pointer)
{
    while (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
    {
        if (strcmp("KEYWORD_ONE\n", buffer) == 0)
        {
            return KEYWORD_ONE_FOUND_FIRST;
        }
        if (strcmp("KEYWORD_TWO\n", buffer) == 0)
        {
            return KEYWORD_TWO_FOUND_FIRST;
        }
    }
    return NO_KEYWORD_FOUND;
}

int parseFile(char *file_name)
{
    int return_value = ERROR;
    FILE *file_pointer = 0;
    char *buffer = 0;

    // If invalid parameters are provided, we immediately return and no cleanup is
    // required because no resources were acquired yet.
    if (file_name == NULL)
    {
        return ERROR;
    }
    if (file_pointer = fopen(file_name, "r"))
    {
        if (buffer = malloc(BUFFER_SIZE))
        {
            return_value = searchFileForKeywords(buffer, file_pointer);
            free(buffer);
        }
        fclose(file_pointer);
    }
    return return_value;
}