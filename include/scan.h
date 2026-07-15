#ifndef SCAN_H
#define SCAN_H

#include <stdbool.h>
#include "dir_list.h"

/**
 * Recursively scan a directory looking for Python virtual environments.
 *
 * @param dir        Root directory to scan.
 * @param dl         DirectoryList where found environments are stored.
 * @param max_depth  Maximum recursion depth.
 *                   -1 means unlimited recursion.
 *
 * @return true on success, false if the root directory cannot be opened.
 */
bool scan_dir(const char *dir, DirectoryList *dl, int max_depth);

#endif