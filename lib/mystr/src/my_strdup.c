/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "mystr.h"

char *my_strdup(char const *src)
{
    char *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (!dest)
        return NULL;
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}
