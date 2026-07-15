#include "scan.h"
#include "dir_list.h"
#include "activate.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_MAX_DEPTH 5

int main(int argc, char **argv)
{
    DirectoryList *dl = directory_list_create();

    if (dl == NULL)
    {
        return 1;
    }

    char *cwd = NULL;
    const char *root;
    int max_depth = DEFAULT_MAX_DEPTH;

    if (argc >= 2)
    {
        root = argv[1];
    }
    else
    {
        cwd = getcwd(NULL, 0);

        if (cwd == NULL)
        {
            perror("getcwd");
            directory_list_free(dl);
            return 1;
        }

        root = cwd;
    }

    if (argc >= 3)
    {
        max_depth = atoi(argv[2]);

        if (max_depth < -1)
        {
            max_depth = DEFAULT_MAX_DEPTH;
        }
    }

    scan_dir(root, dl, max_depth);

    free(cwd);

    for (size_t i = 0; i < directory_list_size(dl); i++)
    {
        const char *env = directory_list_get(dl, i);

        char *activate_path = build_activate_path(env);

        if (activate_path != NULL)
        {
            puts(activate_path);
            free(activate_path);
        }
    }

    directory_list_free(dl);

    return 0;
}