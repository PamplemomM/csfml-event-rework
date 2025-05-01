/*
** EPITECH PROJECT, 2025
** keys_controls.c
** File description:
** the file for the keys controls.
*/

#include "../../include/header_event.h"

presets_t **get_key_presets(void)
{
    static presets_t *key_presets = NULL;

    return &key_presets;
}

static int add_new_control(controls_t **head, keybind_t bind, sfKeyCode key)
{
    controls_t *list = *head;
    controls_t *new_control = NULL;

    new_control = malloc(sizeof(controls_t) * 1);
    if (new_control == NULL)
        return printf("Can't create the control %d\n", bind);
    new_control->bind = bind;
    new_control->key = key;
    new_control->is_pressed = FALSE;
    new_control->is_single_pressed = FALSE;
    if (list != NULL)
        new_control->next = list;
    else
        new_control->next = NULL;
    *head = new_control;
    return SUCCESS;
}

static controls_t *create_key_preset(key_config_t keyboard_layout)
{
    controls_t *head = NULL;
    const int total_controls = 14;
    const sfKeyCode layouts[][14] = {
        {sfKeyW, sfKeyS, sfKeyA, sfKeyD, sfKeySpace, sfKeyLControl, sfKeyE,
        sfKeyEnter, sfKeyEscape, sfKeyTab,
        sfKeyLeft, sfKeyRight, sfKeyUp, sfKeyDown},
        {sfKeyZ, sfKeyS, sfKeyQ, sfKeyD, sfKeySpace, sfKeyLControl, sfKeyE,
        sfKeyEnter, sfKeyEscape, sfKeyTab,
        sfKeyLeft, sfKeyRight, sfKeyUp, sfKeyDown},
        {sfKeyE, sfKeyD, sfKeyS, sfKeyF, sfKeySpace, sfKeyLControl, sfKeyW,
        sfKeyEnter, sfKeyEscape, sfKeyTab,
        sfKeyLeft, sfKeyRight, sfKeyUp, sfKeyDown}};
    const sfKeyCode *selected_keys;

    if (keyboard_layout < QWERTY || keyboard_layout > ESDF)
        return NULL;
    selected_keys = layouts[keyboard_layout];
    for (int i = total_controls - 1; i >= 0; i--)
        add_new_control(&head, i, selected_keys[i]);
    return head;
}

int set_user_key_preset(key_config_t keyboard_layout)
{
    user_t *user = USER;
    presets_t *current = *get_key_presets();

    if (user == NULL)
        return printf("Can't find the user");
    while (current != NULL) {
        if (current->id == keyboard_layout) {
            user->keybinds = current->keys;
            return SUCCESS;
        }
        current = current->next;
    }
    return SUCCESS;
}

int add_presets(key_config_t keyboard_layout)
{
    presets_t *new_preset = malloc(sizeof(presets_t) * 1);
    presets_t *current = *get_key_presets();

    if (new_preset == NULL)
        return printf("Can't create the key presets");
    new_preset->id = keyboard_layout;
    new_preset->keys = create_key_preset(keyboard_layout);
    new_preset->next = NULL;
    if (current == NULL) {
        *get_key_presets() = new_preset;
        return SUCCESS;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_preset;
    return SUCCESS;
}

int init_presets(key_config_t keyboard_layout)
{
    user_t *user = USER;

    if (user == NULL)
        return printf("Can't find the user");
    add_presets(keyboard_layout);
    add_presets(AZERTY);
    add_presets(ESDF);
    set_user_key_preset(keyboard_layout);
    return SUCCESS;
}

int free_all_presets(void)
{
    presets_t *current = *get_key_presets();
    presets_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        if (current != NULL)
            free_control(current->keys);
        free(current);
        current = next;
    }
    return SUCCESS;
}
