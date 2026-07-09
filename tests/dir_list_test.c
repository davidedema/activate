#include "dir_list.h"
#include <stdio.h>
int main(void)
{
    DirectoryList *dl = directory_list_create();
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    directory_list_add(dl, "ciao");
    printf("size of the dl is %d\n", (int)directory_list_size(dl));
    printf("capacity of the dl is %d\n", (int)directory_list_capacity(dl));
    printf("path %s\n", directory_list_get(dl, 10));
}
