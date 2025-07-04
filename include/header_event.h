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
    #include <string.h>
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

    #define MERGESTR(...) merge_str(__VA_ARGS__, NULL)

    #define WINDOW (*get_window())
    #define USER (*get_user())


// --------- WOLF3D STRUCTURES --------

typedef enum key_config_s {
    QWERTY,
    AZERTY,
    ESDF,
    CUSTOM
} key_config_t;

typedef enum mouse_buttons_s {
    LEFT,
    RIGHT
} mouse_buttons_t;

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
    int is_released;
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

// --- single_control.c ---
int is_single_pressed(keybind_t bind);

// --- user.c ---
user_t **get_user(void);
user_t *init_user(void);
void free_user(void);

// --- user_controls.c ---
controls_t *get_control(keybind_t bind);
int free_control(controls_t *ctrl);
int is_pressed(keybind_t bind);
int is_key_pressed(void);
int update_controls(sfEvent event);

// --- user_mouse.c ---
int init_mouse(void);
int update_mouse(sfEvent event);
int is_mouse_pressed(mouse_buttons_t mouse);
int is_mouse_single_pressed(mouse_buttons_t mouse);
int is_mouse_released(mouse_buttons_t mouse);


// ------- C TOOL LIB FUNCTIONS --------

// --- string_arsenal.c ---
char *merge_str(char *first, ...);
char *int_to_str(int nbr);

// --- number_arsenal.c ---
int digitcount(int nbr);

// --- open_directory.c ---
char **open_directory(char *folder);

// --- read_filelib.c ---
char *open_file(char const *filepath);

// --- saveload.c ---
int bc_save(char *str, char *file);
char *ac_load(char *file);

// --------- CSFML HELP FUNCTIONS --------

// --- window_csfml.c ---
sfRenderWindow **get_window(void);
void create_window(unsigned int width, unsigned int height, char const *name);
void destroy_window(void);


#endif /* WOLF_H */
