#define NULL ((void *)0)

////////// Registry API //////////

/* Error codes returned by this registry */
typedef enum
{
    OK,
    OUT_OF_MEMORY,
    INVALID_KEY,
    INVALID_STRING,
    STRING_TOO_LONG,
    CANNOT_ADD_KEY
} RegError;

/* Handle for registry keys */
typedef struct Key *RegKey;

/* Create a new registry key identified via the provided `key_name`
(must not be `NULL`, max. `STRING_SIZE` characters).
Returns a handle to the key or NULL on error. */
RegKey createKey(char *key_name);

/* Store the provided `value` to the provided `key`.
Returns `OK` if no problem occurs, `INVALID_KEY` if the `key`
parameter is `NULL`, `INVALID_STRING` if `value` is `NULL`, or
`STRING_TOO_LONG` if `value` is too long. */
RegError storeValue(RegKey key, char *value);

/* Make the key available for being read. Returns `OK` if no
problem occurs, `INVALID_KEY` if `key` is `NULL`, or `CANNOT_ADD_KEY`
if the registry is full and no more keys can be published. */
RegError publishKey(RegKey key);

////////// Registry implementation //////////

#define STRING_SIZE 100
#define MAX_KEYS 40
struct Key
{
    char key_name[STRING_SIZE];
    char key_value[STRING_SIZE];
};

/* file-global array holding all registry keys */
static struct Key *key_list[MAX_KEYS];

RegKey createKey(char *key_name)
{
    assert(key_name != NULL);
    assert(STRING_SIZE > strlen(key_name));
    RegKey newKey = calloc(1, sizeof(struct Key));
    if (newKey == NULL)
    {
        return NULL;
    }
    strcpy(newKey->key_name, key_name);
    return newKey;
}

RegError storeValue(RegKey key, char *value)
{
    if (key == NULL)
    {
        return INVALID_KEY;
    }
    if (value == NULL)
    {
        return INVALID_STRING;
    }
    if (STRING_SIZE <= strlen(value))
    {
        return STRING_TOO_LONG;
    }
    strcpy(key->key_value, value);
    return OK;
}

RegError publishKey(RegKey key)
{
    int i;
    if (key == NULL)
    {
        return INVALID_KEY;
    }
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

////////// Caller’s code //////////

int main()
{
}