#include "scan.h"
#include "dir_list.h"
#include "activate.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    /***
     * Main of the activate command:
     * usage: activate <root_folder>
     *      - if no argument is provided the root folder is assumed to be the current directory
     *      - if multiple evironments are find, user is asked to select the one that wants to activate
     *      - if only one environment is found it will be auto-activated
     */

    DirectoryList *dl = directory_list_create();
    if (argc == 1)
    {
        scan_dir(".", dl);
    }
    else
    {
        scan_dir(argv[0], dl);
    }
    if (directory_list_size(dl) == 0)
    {
        // print error, no environments found in the current directory
        return 0;
    }
    if (directory_list_size(dl) == 1)
    {
        // auto activate the current environment
        const char *env = directory_list_get(dl, 0);

        char *activate_path = build_activate_path(env);

        printf("source %s\n", activate_path);

        free(activate_path);
        return 0;
    }
    printf("Multiple environments found, select one:\n");
    directory_list_print(dl);
    size_t index;
    scanf("%ld", &index);
    // auto activate the current environment
    const char *env = directory_list_get(dl, index);

    char *activate_path = build_activate_path(env);

    printf("source %s\n", activate_path);

    free(activate_path);
    return 0;
}
