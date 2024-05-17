#include <stdio.h>
#include <dirent.h>

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

/* For the provided 'filename', this function reads text from the file and
prints the Caesar-encrypted text. This function is responsible for
allocating and deallocating the required buffers for storing the
file content */
void encryptCaesarFile(char *filename)
{
    char *text;
    int size = getFileLength(filename);
    if (size > 0)
    {
        text = malloc(size);
        readFileContent(filename, text, size);
        caesar(text, strnlen(text, size));
        printf("Encrypted text: %s\n", text);
        free(text);
    }
}

/* For all files in the current directory, this function reads text
from the file and prints the Caesar-encrypted text. */
void encryptDirectoryContent()
{
    struct dirent *directory_entry;
    DIR *directory = opendir(".");
    while ((directory_entry = readdir(directory)) != NULL)
    {
        encryptCaesarFile(directory_entry->d_name);
    }
    closedir(directory);
}