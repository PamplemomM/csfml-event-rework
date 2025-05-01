/*
** PamplemomM PROJECT, 2025
** string_arsenal.c
** File description:
** An arsenal of functions that concern strings.
*/

#include "../../include/header_event.h"
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

static char *merge_two_strings(char *s1, char *s2)
{
    char *str[2] = {s1, s2};
    char *result = NULL;
    int len = 0;

    if (s1 == NULL || s2 == NULL)
        return NULL;
    len = strlen(s1) + strlen(s2);
    result = malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; i < strlen(s1); i++)
        result[i] = s1[i];
    for (int j = 0; j < strlen(s2); j++)
        result[j + strlen(s1)] = s2[j];
    result[len] = '\0';
    return result;
}

char *merge_str(char *first, ...)
{
    char *str = strdup(first);
    char *next = NULL;
    char *tmp = NULL;
    va_list arg;

    if (str == NULL)
        return NULL;
    va_start(arg, first);
    while (1) {
        next = va_arg(arg, char *);
        if (next == NULL)
            break;
        tmp = merge_two_strings(str, next);
        OMNIFREE(str, 1);
        if (tmp == NULL)
            break;
        str = tmp;
    }
    va_end(arg);
    return str;
}

char *int_to_str(int nbr)
{
    char *str;
    int len = digitcount(nbr);
    int neg = 0;

    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    if (nbr < 0) {
        str[0] = '-';
        nbr = abs(nbr);
        neg = 1;
    }
    for (int i = 0; i < len - neg; i++) {
        str[len - i - 1] = nbr % 10 + '0';
        nbr /= 10;
    }
    str[len] = '\0';
    return str;
}
