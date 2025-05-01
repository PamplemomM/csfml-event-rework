/*
** PamplemomM PROJECT, 2025
** main_test.c
** File description:
** The file for the main test.
*/

#include "../include/header_event.h"

// You can here process calculations only if a registered key is pressed
int process_action(void)
{
    return SUCCESS;
}

int events(void)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
        update_controls(event);
    }
}

int run(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        events();
        if (is_pressed(MV_FORWARD))
            printf("MV_FORWARD pressed\n");
        if (is_single_pressed(TAB))
            printf("TAB toggle pressed\n");
        if (is_key_pressed())
            process_action();
        sfRenderWindow_clear(WINDOW, sfBlack);
        sfRenderWindow_display(WINDOW);
    }
    return SUCCESS;
}

int main(void)
{
    create_window(800, 600, "Event test");
    init_user();
    init_presets(QWERTY);
    load_presets();
    run();
    save_presets();
    free_all_presets();
    destroy_window();
    return SUCCESS;
}
