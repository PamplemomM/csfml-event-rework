/*
** PamplemomM PROJECT, 2025
** open_directory.c
** File description:
** the file for opening a directory.
*/

#include "../../include/header_event.h"
#include <dirent.h>

static int get_directory_len(char *directory)
{
    DIR *dirp;
    struct dirent *dp;
    int size = 0;

    dirp = opendir(directory);
    if (dirp == NULL)
        return ERROR;
    dp = readdir(dirp);
    while (dp != NULL) {
        if (dp->d_name[0] != '.')
            size++;
        dp = readdir(dirp);
    }
    closedir(dirp);
    return size;
}

char **open_directory(char *folder)
{
    char **result = malloc(sizeof(char *) * (get_directory_len(folder) + 1));
    DIR *dirp = opendir(folder);
    struct dirent *dp;
    int i = 0;

    if (result == NULL || dirp == NULL) {
        if (result != NULL)
            free(result);
        return NULL;
    }
    dp = readdir(dirp);
    while (dp != NULL) {
        if (dp->d_name[0] != '.') {
            result[i] = MERGESTR(folder, dp->d_name);
            i++;
        }
        dp = readdir(dirp);
    }
    result[i] = NULL;
    closedir(dirp);
    return result;
}
