#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "scan.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/* check if the directory is a python environment.
An heuristic could be:
    - the folder contains a bin/ folder with inside a file called activate and a file called python
*/
bool is_python_env(const char *path);
bool contains_env_files(const char *path);

bool scan_dir(const char *dir, DirectoryList *dl)
{
    DIR *root = opendir(dir);

    if (root == NULL)
    {
        return false;
    }

    struct dirent *entry;
    struct stat info;
    char path[PATH_MAX];

    while ((entry = readdir(root)) != NULL)
    {
        // skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        if (stat(path, &info) == -1)
        {
            continue;
        }

        if (S_ISDIR(info.st_mode))
        {
            bool possible = is_python_env(path);
            if (possible)
            {
                if (contains_env_files(path) == true)
                {
                    directory_list_add(dl, path);
                }
            }
            scan_dir(path, dl);
        }
    }

    closedir(root);
    return true;
}

bool is_python_env(const char *path)
{
    char bin_path[PATH_MAX];
    struct stat info;

    snprintf(bin_path, sizeof(bin_path), "%s/bin", path);

    if (stat(bin_path, &info) == -1)
    {
        return false;
    }

    if (S_ISDIR(info.st_mode))
    {
        return true;
    }

    return false;
}

bool contains_env_files(const char *path)
{
    char python_path[PATH_MAX];
    char activate_path[PATH_MAX];
    struct stat info_a;
    struct stat info_p;
    char bin_path[PATH_MAX];

    snprintf(bin_path, sizeof(bin_path), "%s/bin", path);

    snprintf(python_path, sizeof(python_path), "%s/python", bin_path);
    snprintf(activate_path, sizeof(activate_path), "%s/activate", bin_path);

    if (stat(activate_path, &info_a) == -1)
    {
        return false;
    }
    if (stat(python_path, &info_p) == -1)
    {
        return false;
    }
    if (!S_ISREG(info_a.st_mode))
    {
        return false;
    }
    if (!S_ISREG(info_p.st_mode))
    {
        return false;
    }
    return true;
}