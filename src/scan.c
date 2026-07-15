#include "scan.h"

#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/* Private helpers */
static bool scan_dir_recursive(const char *dir,
                               DirectoryList *dl,
                               int depth,
                               int max_depth);

static bool is_python_env(const char *path);
static bool contains_env_files(const char *path);

/* Public API */
bool scan_dir(const char *dir, DirectoryList *dl, int max_depth)
{
    if (dir == NULL || dl == NULL)
    {
        return false;
    }

    return scan_dir_recursive(dir, dl, 0, max_depth);
}

/* Recursive implementation */
static bool scan_dir_recursive(const char *dir,
                               DirectoryList *dl,
                               int depth,
                               int max_depth)
{
    if (max_depth >= 0 && depth > max_depth)
    {
        return true;
    }

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

        if (!S_ISDIR(info.st_mode))
        {
            continue;
        }

        if (is_python_env(path) && contains_env_files(path))
        {
            directory_list_add(dl, path);
        }

        scan_dir_recursive(path, dl, depth + 1, max_depth);
    }

    closedir(root);

    return true;
}

/* Check if <path>/bin exists */
static bool is_python_env(const char *path)
{
    char bin_path[PATH_MAX];
    struct stat info;

    snprintf(bin_path, sizeof(bin_path), "%s/bin", path);

    if (stat(bin_path, &info) == -1)
    {
        return false;
    }

    return S_ISDIR(info.st_mode);
}

/* Check if bin/activate and bin/python exist */
static bool contains_env_files(const char *path)
{
    char activate_path[PATH_MAX];
    char python_path[PATH_MAX];
    struct stat info;

    snprintf(activate_path,
             sizeof(activate_path),
             "%s/bin/activate",
             path);

    if (stat(activate_path, &info) == -1 || !S_ISREG(info.st_mode))
    {
        return false;
    }

    snprintf(python_path,
             sizeof(python_path),
             "%s/bin/python",
             path);

    if (stat(python_path, &info) == -1 || !S_ISREG(info.st_mode))
    {
        return false;
    }

    return true;
}