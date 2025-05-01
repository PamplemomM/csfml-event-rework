/*
** PamplemomM PROJECT, 2025
** single_control.c
** File description:
** the file for a single keys controls.
*/

#include "../include/header_event.h"

int is_single_pressed(keybind_t bind)
{
    controls_t *control = NULL;

    if (!is_key_pressed())
        return FALSE;
    control = get_control(bind);
    if (control == NULL)
        return FALSE;
    if (control->is_single_pressed) {
        control->is_single_pressed = FALSE;
        return TRUE;
    }
    return FALSE;
}
