/*
** PamplemomM PROJECT, 2025
** key_preset_loading.c
** File description:
** The file for loading the user key presets.
*/

#include "../../include/header_event.h"

static int add_new_control(controls_t **head, keybind_t bind, sfKeyCode key)
{
    controls_t *list = *head;
    controls_t *new_control = malloc(sizeof(controls_t) * 1);

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

static controls_t *parse_key_preset(char *str)
{
    controls_t *head = NULL;
    int length = my_strlen(str);
    int cpt = 3;

    while (cpt < length) {
        add_new_control(&head, str[cpt] - 48, str[cpt + 2] - 48);
        cpt += 4;
    }
    return head;
}

static int add_presets_fromfile(char *filecontent, int id)
{
    presets_t *new_preset = malloc(sizeof(presets_t) * 1);
    presets_t *current = *get_key_presets();

    if (new_preset == NULL)
        return printf("addpreset fromfile: can't malloc presets");
    new_preset->id = id;
    new_preset->keys = parse_key_preset(filecontent);
    new_preset->next = NULL;
    if (current == NULL) {
        *get_key_presets() = new_preset;
        return SUCCESS;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_preset;
    return SUCCESS;
}

int load_presets(void)
{
    char **folder = open_directory(KEYBINDS_STORAGE);
    char *filecontent = NULL;

    if (folder == NULL)
        return printf("Cant open folder %s.", KEYBINDS_STORAGE);
    my_sort_str_array(folder);
    for (int i = 0; folder[i] != NULL; i++) {
        filecontent = ac_load(folder[i]);
        if (filecontent == NULL)
            return printf("Can't read %s.", folder[i]);
        add_presets_fromfile(filecontent, i);
        free(filecontent);
    }
    for (int i = 0; folder[i] != NULL; i++)
        free(folder[i]);
    free(folder);
    return SUCCESS;
}
