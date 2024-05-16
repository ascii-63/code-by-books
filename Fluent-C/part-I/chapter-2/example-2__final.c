#include <stdlib.h>
#include <stdbool.h>

/* max. size of string parameters (including NULL-termination) */
#define STRING_SIZE 100

/* Error codes returned by this registry */
typedef enum
{
    OK,
    CANNOT_ADD_KEY
} RegError;

/* Handle for registry keys */
typedef struct Key *RegKey;

/* Create a new registry key identified via the provided `key_name`
(must not be `NULL`, max. `STRING_SIZE` characters). Returns a handle
to the key or `NULL` on error. */
RegKey createKey(char *key_name);

/* Store the provided `value` (must not be `NULL`, max. `STRING_SIZE` characters)
to the `key` (MUST NOT BE `NULL`) */
void storeValue(RegKey key, char *value);

/* Make the `key` (must not be `NULL`) available for being read.
Returns `OK` if no problem occurs or `CANNOT_ADD_KEY` if the
registry is full and no more keys can be published. */
RegError publishKey(RegKey key);

////////// Registry implementation //////////
#define MAX_KEYS 40
struct Key
{
    char key_name[STRING_SIZE];
    char key_value[STRING_SIZE];
};

/* macro to log debug info and to assert */
#define logAssert(X)                          \
    if (!(X))                                 \
    {                                         \
                                              \
        printf("Error at line %i", __LINE__); \
        assert(false);                        \
    }

/* file-global array holding all registry keys */
static struct Key *key_list[MAX_KEYS];

RegKey createKey(char *key_name)
{
    logAssert(key_name != NULL)
        logAssert(STRING_SIZE > strlen(key_name))
            RegKey newKey = calloc(1, sizeof(struct Key));
    if (newKey == NULL)
    {
        return NULL;
    }
    strcpy(newKey->key_name, key_name);
    return newKey;
}

void storeValue(RegKey key, char *value)
{
    logAssert(key != NULL && value != NULL)
        logAssert(STRING_SIZE > strlen(value))
            strcpy(key->key_value, value);
}

RegError publishKey(RegKey key)
{
    logAssert(key != NULL) int i;
    for (i = 0; i < MAX_KEYS; i++)
    {
        if (key_list[i] == NULL)
        {
            key_list[i] = key;
            return OK;
        }
    }
    return CANNOT_ADD_KEY;
}