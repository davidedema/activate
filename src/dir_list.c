#include "dir_list.h"

#define INITIAL_CAPACITY 10

struct DirectoryList
{
    char **paths;
    size_t size;
    size_t capacity;
};

static char *strdup(const char *c);
static bool directory_list_grow(DirectoryList *dl);

/* Create a pointer to a new DirectoryList, initialize the struct and return the pointer*/
DirectoryList *directory_list_create(void)
{
    DirectoryList *dl;
    dl = malloc(sizeof(*dl));

    if (dl == NULL)
    {
        // return NULL when malloc fails
        return NULL;
    }

    dl->size = 0;
    dl->capacity = INITIAL_CAPACITY;
    // initialize to 0 the memory with calloc
    dl->paths = calloc(INITIAL_CAPACITY, sizeof(char *));

    if (dl->paths == NULL)
    {
        // return NULL when malloc fails
        free(dl);
        return NULL;
    }

    return dl;
}

/* Add a new path to the directory list */
bool directory_list_add(DirectoryList *dl, const char *path)
{
    // check if dl exists
    if (dl == NULL)
        return false;

    // TODO check if path exits
    if (path == NULL)
        return false;
    if (dl->size >= dl->capacity)
        if (!directory_list_grow(dl))
            return false;
    char *s = strdup(path);
    if (s == NULL)
        return false;
    dl->paths[dl->size] = s;
    dl->size++;
    return true;
}

/* get index element from the DirectoryList */
const char *directory_list_get(const DirectoryList *dl, size_t index)
{
    if (dl == NULL)
        return NULL;
    if (index >= dl->capacity)
        return NULL;

    return dl->paths[index];
}

/* returns the size of a DirectoryList */
size_t directory_list_size(const DirectoryList *dl)
{
    if (dl == NULL)
        return 0;
    return dl->size;
}

/* returns the capacity of a DirectoryList */
size_t directory_list_capacity(const DirectoryList *dl)
{
    if (dl == NULL)
        return 0;
    return dl->capacity;
}

/* free the DirectoryList*/
void directory_list_free(DirectoryList *dl)
{
    if (dl == NULL)
        return;
    for (size_t i = 0; i < dl->size; i++)
    {
        free(dl->paths[i]);
    }
    free(dl->paths);
    free(dl);
}

/* implementation of strdup */
static char *strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);

    if (dup != NULL)
        strcpy(dup, c);

    return dup;
}

/* Helper for reallocating memory when dl->size >= dl->capacity */
static bool directory_list_grow(DirectoryList *dl)
{
    char **tmp;
    size_t new_capacity = dl->capacity * 2;
    tmp = realloc(dl->paths, new_capacity * sizeof(char *));
    if (tmp == NULL)
        return false;
    dl->paths = tmp;
    dl->capacity = new_capacity;
    return true;
}