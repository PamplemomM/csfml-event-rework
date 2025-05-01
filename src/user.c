/*
** PamplemomM PROJECT, 2025
** user.c
** File description:
** user file for the user management.
*/

#include "../include/header_event.h"

user_t **get_user(void)
{
    static user_t *current_user = NULL;

    return &current_user;
}

user_t *init_user(char *name, int posx, int posy)
{
    user_t *new_user = malloc(sizeof(user_t) * 1);

    if (new_user == NULL) {
        printf("Failed to create the user");
        return NULL;
    }
    new_user->keybinds = NULL;
    new_user->is_key_pressed = 0;
    new_user->keybind_preset = QWERTY;
    if (USER == NULL)
        USER = new_user;
    return new_user;
}

void free_user(void)
{
    user_t *user = *get_user();

    if (user == NULL)
        return;
    free_control(user->keybinds);
    free(user);
    user = NULL;
}
