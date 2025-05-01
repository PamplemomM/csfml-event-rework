/*
** PamplemomM PROJECT, 2025
** user_controls.c
** File description:
** user file for the user controls.
*/

#include "../include/header_event.h"

controls_t *get_control(keybind_t bind)
{
    user_t *user = USER;
    controls_t *controls = NULL;

    if (user == NULL) {
        printf("Cant find the user\n");
        return NULL;
    }
    controls = user->keybinds;
    while (controls != NULL) {
        if (controls->bind == bind)
            return controls;
        controls = controls->next;
    }
    printf("get_control: Controls are not initialized\n");
    return NULL;
}

int free_control(controls_t *ctrl)
{
    controls_t *current = ctrl;
    controls_t *next = NULL;

    if (ctrl == NULL)
        return SUCCESS;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    return SUCCESS;
}

int is_pressed(keybind_t bind)
{
    controls_t *control = NULL;

    if (!is_key_pressed())
        return FALSE;
    control = get_control(bind);
    if (control == NULL)
        return FALSE;
    return control->is_pressed;
}

int is_key_pressed(void)
{
    user_t *user = USER;

    if (user == NULL)
        return printf("is_key_pressed: Can't find user");
    return user->is_key_pressed;
}

static int print_bind(keybind_t bind)
{
    static char *str[15] = {"MV_FORWARD", "MV_BACKWARDS", "MV_LEFT",
        "MV_RIGHT", "JUMP", "CROUCH", "ZOOM", "CONFIRM", "ESC",
        "TAB", "CAM_LEFT", "CAM_RIGHT", "CAM_UP", "CAM_DOWN", NULL};

    if (bind > 14)
        return SUCCESS;
    printf("%s", str[bind]);
    return bind;
}

static int detect_if_key_pressed(controls_t *controls)
{
    user_t *user = USER;
    controls_t *current = user->keybinds;

    while (current != NULL) {
        if (current->is_pressed == TRUE) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

static int update_key(sfEvent event, int is_pressed)
{
    user_t *user = USER;
    controls_t *controls = user->keybinds;

    while (controls != NULL) {
        if (event.key.code == controls->key) {
            controls->is_pressed = is_pressed;
            controls->is_single_pressed = is_pressed;
            user->is_key_pressed = detect_if_key_pressed(controls);
            return SUCCESS;
        }
        controls = controls->next;
    }
    user->is_key_pressed = (is_pressed) ? TRUE :
        detect_if_key_pressed(controls);
    return SUCCESS;
}

int update_controls(sfEvent event)
{
    if (event.type == sfEvtKeyPressed)
        update_key(event, TRUE);
    if (event.type == sfEvtKeyReleased)
        update_key(event, FALSE);
    return SUCCESS;
}
