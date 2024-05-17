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