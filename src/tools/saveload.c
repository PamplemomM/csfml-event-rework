/*
** EPITECH PROJECT, 2025
** saveload.c
** File description:
** Save or Load anything.
*/

#include "../../include/header_event.h"
#include <unistd.h>
#include <fcntl.h>

int bc_save(char *str, char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
        return printf("Can't open the file %s\n", file);
    if (write(fd, str, strlen(str)) == -1)
        return printf("Can't write in the file %s\n", file);
    close(fd);
    return SUCCESS;
}

char *ac_load(char *file)
{
    char *file_content = open_file(file);

    if (file_content == NULL)
        return NULL;
    return file_content;
}
