/*
** PamplemomM PROJECT, 2025
** key_preset_saving.c
** File description:
** The file for saving the user key presets.
*/

#include "../../include/header_event.h"

static int get_preset_strlength(presets_t *current)
{
    controls_t *controls = current->keys;
    int res = digitcount(current->id) + 2;

    while (controls != NULL) {
        res += 4;
        controls = controls->next;
    }
    return res;
}

static char *get_preset_instring(presets_t *current)
{
    controls_t *controls = current->keys;
    char *str = malloc(sizeof(char) * get_preset_strlength(current));
    int cpt = 3;

    if (str == NULL)
        return NULL;
    controls = current->keys;
    str[0] = current->id + 48;
    str[1] = ':';
    str[2] = ' ';
    for (; controls != NULL; controls = controls->next) {
        str[cpt] = controls->bind + 48;
        str[cpt + 1] = ';';
        str[cpt + 2] = controls->key + 48;
        if (controls->next != NULL)
            str[cpt + 3] = ',';
        cpt += (controls->next != NULL) ? 4 : 3;
    }
    str[cpt] = '\0';
    return str;
}

static int save_single_preset(presets_t *current, int cpt)
{
    controls_t *controls = NULL;
    char *str = NULL;
    char *filename = NULL;
    char *number = NULL;

    if (current == NULL)
        return SUCCESS;
    str = get_preset_instring(current);
    if (str == NULL)
        return printf("Can't create the saving preset string.");
    number = int_to_str(cpt);
    filename = MERGESTR("save_data/keybinds/keyboard_preset", number);
    printf("%s\n", str);
    bc_save(str, filename);
    free(str);
    free(filename);
    free(number);
    return SUCCESS;
}

int save_presets(void)
{
    presets_t *current = *get_key_presets();
    int cpt = 0;

    if (current == NULL)
        return printf("Save presets: Can't find the presets");
    while (current != NULL) {
        save_single_preset(current, cpt);
        current = current->next;
        cpt++;
    }
    return SUCCESS;
}
