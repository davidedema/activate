#ifndef DIR_LIST_H
#define DIR_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DirectoryList DirectoryList;

/* Create a pointer to a new DirectoryList, initialize the struct and return the pointer*/
DirectoryList *directory_list_create(void);
/* Add a new path to the directory list */
bool directory_list_add(DirectoryList *dl, const char *path);
/* get index element from the DirectoryList */
const char *directory_list_get(const DirectoryList *dl, size_t index);
/* returns the size of a DirectoryList */
size_t directory_list_size(const DirectoryList *dl);
/* returns the capacity of a DirectoryList */
size_t directory_list_capacity(const DirectoryList *dl);
/* free the DirectoryList*/
void directory_list_free(DirectoryList *dl);
/* print the directory list */
void directory_list_print(DirectoryList *dl);

#endif