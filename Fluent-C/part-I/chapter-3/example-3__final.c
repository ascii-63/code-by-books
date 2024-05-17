#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>

#define ELEMENT_SIZE 255
#define MAX_ELEMENTS 10
typedef struct
{
    bool occupied;
    char memory[ELEMENT_SIZE];
} PoolElement;

static PoolElement memory_pool[MAX_ELEMENTS];

void *poolTake(size_t size)
{
    if (size <= ELEMENT_SIZE)
    {
        for (int i = 0; i < MAX_ELEMENTS; i++)
        {
            if (memory_pool[i].occupied == false)
            {
                memory_pool[i].occupied = true;
                return &(memory_pool[i].memory);
            }
        }
    }
    return NULL;
}

void poolRelease(void *pointer)
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (&(memory_pool[i].memory) == pointer)
        {
            memory_pool[i].occupied = false;
            return;
        }
    }
}

#define MAX_FILENAME_SIZE ELEMENT_SIZE

/* Performs a Caesar encryption with the fixed key 3.
The parameter `text` must contain a text with only capital letters.
The parameter `length` must contain the length of the text excluding `NULL` termination. */
void caesar(char *text, int length)
{
    for (int i = 0; i < length; i++)
    {
        /* Characters in C are stored as numeric values, and you can shift the character
        down the alphabet by adding a numeric value to a character.
        */
        text[i] = text[i] + 3;
        if (text[i] > 'Z')
        {
            // If we shift beyond the letter Z, we restart at the beginning of the alphabet.
            text[i] = text[i] - 'Z' + 'A' - 1;
        }
    }
}

/* Returns the length of the file with the provided `filename` */
int getFileLength(char *filename)
{
    FILE *f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    int file_length = ftell(f);
    fclose(f);
    return file_length;
}

/* Stores the content of the file with the provided `filename` into the
provided `buffer` (which has to be least of size `file_length`). The
file must only contain capital letters with no newline in between
(that's what our caesar function accepts as input). */
void readFileContent(char *filename, char *buffer, int file_length)
{
    FILE *f = fopen(filename, "r");
    fseek(f, 0, SEEK_SET);
    int read_elements = fread(buffer, 1, file_length, f);
    buffer[read_elements] = '\0';
    fclose(f);
}

/* Prints the Caesar-encrypted 'filename'.This function is responsible for
allocating and deallocating the required buffers for storing the
file content.
Notes: The filename must be all capital letters and we accept that the
'.' of the filename will also be shifted by the Caesar encryption. */
void encryptCaesarFilename(char *filename)
{
    char *buffer = poolTake(MAX_FILENAME_SIZE);
    if (buffer != NULL)
    {
        strlcpy(buffer, filename, MAX_FILENAME_SIZE);
        caesar(buffer, strnlen(buffer, MAX_FILENAME_SIZE));
        printf("\nEncrypted filename: %s ", buffer);
        poolRelease(buffer);
    }
}

/* For all files in the current directory, this function reads text from the
file and prints the Caesar-encrypted text. */
void encryptDirectoryContent()
{
    struct dirent *directory_entry;
    DIR *directory = opendir(".");
    while ((directory_entry = readdir(directory)) != NULL)
    {
        encryptCaesarFilename(directory_entry->d_name);
        encryptCaesarFile(directory_entry->d_name);
    }
    closedir(directory);
}