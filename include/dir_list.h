#ifndef DIR_LIST_H
#define DIR_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct DirectoryList DirectoryList;

DirectoryList *directory_list_create(void);
bool directory_list_add(DirectoryList *dl, const char *path);
const char *directory_list_get(const DirectoryList *dl, size_t index);
size_t directory_list_size(const DirectoryList *dl);
size_t directory_list_capacity(const DirectoryList *dl);
void directory_list_free(DirectoryList *dl);

#endif