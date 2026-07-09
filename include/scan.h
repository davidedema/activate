#ifndef SCAN_H
#define SCAN_H

#include "dir_list.h"
#include <stdbool.h>

/* Scan if in the dir directories are present possible python environments */
bool scan_dir(const char *dir, DirectoryList *dl);

#endif