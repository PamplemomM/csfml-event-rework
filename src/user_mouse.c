/*
** PamplemomM PROJECT, 2025
** user_mouse.c
** File description:
** user file for the user mouse control.
*/

#include "../../include/header_event.h"

static controls_t **get_mouse(void)
{
    static controls_t *mouse = NULL;

    return &mouse;
}

static int init_left_click(void)
{
    controls_t *left = malloc(sizeof(controls_t) * 1);

    if (left == NULL)
        return debug_print("Can't allocate the left button.");
    left->bind = -1;
    left->key = -1;
    left->is_pressed = FALSE;
    left->is_single_pressed = FALSE;
    left->is_released = FALSE;
    (*get_mouse()) = left;
    return SUCCESS;
}

static int init_right_click(void)
{
    controls_t *right = malloc(sizeof(controls_t) * 1);

    if (right == NULL)
        return debug_print("Can't allocate the right button.");
    right->bind = -1;
    right->key = -1;
    right->is_pressed = FALSE;
    right->is_single_pressed = FALSE;
    right->is_released = FALSE;
    (*get_mouse())->next = right;
    return SUCCESS;
}

int init_mouse(void)
{
    init_left_click();
    init_right_click();
    return SUCCESS;
}

static int reset_mouse_single_pressed(void)
{
    controls_t *current = (*get_mouse());

    if (current->is_single_pressed == TRUE || current->is_released == TRUE) {
        current->is_released = FALSE;
        current->is_single_pressed = FALSE;
    }
    current = current->next;
    if (current->is_single_pressed == TRUE || current->is_released == TRUE) {
        current->is_released = FALSE;
        current->is_single_pressed = FALSE;
    }
    return SUCCESS;
}

static void check_mouse(sfEvent event, controls_t *current)
{
    if (event.type == sfEvtMouseButtonPressed) {
        if (event.mouseButton.button == sfMouseLeft) {
            current->is_pressed = TRUE;
            current->is_single_pressed = TRUE;
        }
        if (event.mouseButton.button == sfMouseRight) {
            current->next->is_pressed = TRUE;
            current->next->is_single_pressed = TRUE;
        }
    }
    if (event.type == sfEvtMouseButtonReleased) {
        if (event.mouseButton.button == sfMouseLeft) {
            current->is_pressed = FALSE;
            current->is_released = TRUE;
        }
        if (event.mouseButton.button == sfMouseRight) {
            current->next->is_pressed = FALSE;
            current->next->is_released = TRUE;
        }
    }
}

int update_mouse(sfEvent event)
{
    controls_t *current = *get_mouse();

    reset_mouse_single_pressed();
    check_mouse(event, current);
    return SUCCESS;
}

int is_mouse_pressed(mouse_buttons_t mouse)
{
    controls_t *current = *get_mouse();

    if (current == NULL)
        return debug_print("Can't found the mouse.");
    if (mouse == RIGHT)
        current = current->next;
    return current->is_pressed;
}

int is_mouse_single_pressed(mouse_buttons_t mouse)
{
    controls_t *current = *get_mouse();

    if (current == NULL)
        return debug_print("Can't found the mouse.");
    if (mouse == RIGHT)
        current = current->next;
    return current->is_single_pressed;
}

int is_mouse_released(mouse_buttons_t mouse)
{
    controls_t *current = *get_mouse();

    if (current == NULL)
        return debug_print("Can't found the mouse.");
    if (mouse == RIGHT)
        current = current->next;
    return current->is_released;
}