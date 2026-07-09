#include "activate.h"

char *build_activate_path(const char *env_path)
{
    size_t len = strlen(env_path) + strlen("/bin/activate") + 1;
    char *result = malloc(len);

    if (result != NULL)
    {
        snprintf(result, len, "%s/bin/activate", env_path);
    }
    return result;
}
