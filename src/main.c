#include "scan.h"
#include "dir_list.h"
#include "activate.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    DirectoryList *dl = directory_list_create();

    if (dl == NULL)
    {
        return 1;
    }

    char *root = NULL;

    if (argc == 1)
    {
        root = getcwd(NULL, 0);

        if (root == NULL)
        {
            perror("getcwd");
            directory_list_free(dl);
            return 1;
        }
    }
    else
    {
        root = argv[1];
    }

    scan_dir(root, dl);

    if (argc == 1)
    {
        free(root);
    }

    /*
     * Output only activation paths.
     * The shell wrapper handles the interaction.
     */
    for (size_t i = 0; i < directory_list_size(dl); i++)
    {
        const char *env = directory_list_get(dl, i);

        char *activate_path = build_activate_path(env);

        if (activate_path != NULL)
        {
            printf("%s\n", activate_path);
            free(activate_path);
        }
    }

    directory_list_free(dl);

    return 0;
}