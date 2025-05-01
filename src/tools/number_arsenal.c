/*
** EPITECH PROJECT, 2025
** number_arsenal.c
** File description:
** An arsenal of functions that concern numbers.
*/

#include "../../include/header_event.h"
#include <stdlib.h>

int digitcount(int nbr)
{
    int len = 0;

    if (nbr == 0)
        return 1;
    if (nbr < 0)
        len++;
    while (nbr != nbr / 10) {
        nbr /= 10;
        len++;
    }
    return len;
}
