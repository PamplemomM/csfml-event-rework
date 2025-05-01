/*
** PamplemomM PROJECT, 2025
** main_test.c
** File description:
** The file for the main test.
*/

#include "../include/header_event.h"

int run(void)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(WINDOW)) {
        while (sfRenderWindow_pollEvent(WINDOW, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(WINDOW);
            update_controls(event);
        }
        sfRenderWindow_clear(WINDOW, sfBlack);
        sfRenderWindow_display(WINDOW);
    }
    return SUCCESS;
}

int main(void)
{
    create_window(1920, 1080, "Event test");
    init_user();
    init_presets(QWERTY);
    load_presets();
    run();
    save_presets();
    free_all_presets();
    destroy_window();
    return SUCCESS;
}