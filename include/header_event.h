/*
** PamplemomM PROJECT, 2025
** header_event.h
** File description:
** Header file for the events.
*/

#ifndef WOLF_H
    #define WOLF_H

    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <SFML/System.h>
    #include <SFML/Graphics.h>
    #include <time.h>

    // defines:
    #define SUCCESS 0
    #define ERROR 84
    #define TRUE 1
    #define FALSE 0

    #define KEYBINDS_STORAGE "save_data/keybinds/"

    #define USER (*get_user())


// --------- WOLF3D STRUCTURES --------

typedef enum key_config_s {
    QWERTY,
    AZERTY,
    ESDF,
    CUSTOM
} key_config_t;

typedef enum keybind_s {
    MV_FORWARD,
    MV_BACKWARDS,
    MV_LEFT,
    MV_RIGHT,
    JUMP,
    CROUCH,
    ZOOM,
    CONFIRM,
    ESC,
    TAB,
    CAM_LEFT,
    CAM_RIGHT,
    CAM_UP,
    CAM_DOWN
} keybind_t;

typedef struct controls_s {
    struct controls_s *next;
    keybind_t bind;
    sfKeyCode key;
    int is_pressed;
    int is_single_pressed;
} controls_t;

typedef struct user_s {
    controls_t *keybinds;
    int is_key_pressed;
    key_config_t keybind_preset;
} user_t;

typedef struct presets_s {
    struct presets_s *next;
    key_config_t id;
    controls_t *keys;
} presets_t;


// --------- PROTOTYPES --------

// ----- KEY PRESET -----

// --- key_preset_loading.c ---
int load_presets(void);

// --- key_preset_saving.c ---
int save_presets(void);

// --- keys_controls.c ---
presets_t **get_key_presets(void);
int set_user_key_preset(key_config_t keyboard_layout);
int init_presets(key_config_t keyboard_layout);
int free_all_presets(void);


// ----- USER DATA -----

// --- user.c ---
user_t **get_user(void);
user_t *init_user(char *name, int posx, int posy);
void free_user(void);

// --- user_controls.c ---
controls_t *get_control(keybind_t bind);
int free_control(controls_t *ctrl);
int is_pressed(keybind_t bind);
int is_key_pressed(void);
int update_controls(sfEvent event);


#endif /* WOLF_H */
