/*
** PamplemomM PROJECT, 2025
** read_file_lib.c
** File description:
** The file for reading a file.
*/

#include "../../include/header_event.h"
#include <fcntl.h>

static char *read_line(int fd, int size)
{
    char *buffer = malloc(sizeof(char) * (size + 1));
    int i = 0;
    int res = 0;

    if (buffer == NULL)
        return NULL;
    while (i < size) {
        res = read(fd, &buffer[i], 1);
        if (res <= 0 || buffer[i] == '\n')
            break;
        i++;
    }
    if (res <= 0 && i == 0) {
        free(buffer);
        return NULL;
    }
    buffer[i] = '\0';
    return buffer;
}

static size_t get_total_size(int add)
{
    static size_t total_size = 0;

    total_size += add;
    return total_size;
}

static char *dup_result(char *result, char *line, int len)
{
    char *temp = realloc(result, get_total_size(0) + len + 2);

    if (temp == NULL)
        return NULL;
    result = temp;
    strcpy(result + get_total_size(0), line);
    get_total_size(len);
    result[get_total_size(0)] = '\n';
    result[get_total_size(0) + 1] = '\0';
    get_total_size(1);
    return result;
}

static char *read_file(int fd)
{
    char *result = NULL;
    char *new_result = NULL;
    int size = 256;
    char *line = read_line(fd, size);
    int len = 0;

    if (line == NULL)
        return NULL;
    while (line != NULL) {
        len += strlen(line) + 1;
        new_result = dup_result(result, line, strlen(line));
        free(line);
        line = read_line(fd, size);
        if (new_result == NULL)
            return NULL;
        result = new_result;
    }
    free(line);
    result[len] = '\0';
    return result;
}

char *open_file(char const *filepath)
{
    int fd = open(filepath, O_RDONLY | O_CREAT, 0644);
    char *result = NULL;

    if (fd < 0)
        return NULL;
    result = read_file(fd);
    close(fd);
    get_total_size(-get_total_size(0));
    return result;
}
