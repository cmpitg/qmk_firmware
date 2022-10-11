/* Copyright 2017 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
// To flash steno firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   Reset keyboard or press hw reset button on base (hole)
//
//   cd qmk_firmware/keyboards/steno
//   sudo make KEYMAP=sdothum dfu
//
//   sudo make clean          (good practice before flashing)
//   sudo make KEYMAP=<...>   (to compile check)
//
// Package requirements (for arch linux)
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   avr-gcc-atmel
//   avr-libc-atmel
//   dfu-programmer
//
// Code
// ▔▔▔▔
//   This source is shamelessly based on the "default" steno layout
//
//   #ifdef/#endif block structures are not indented, as syntax highlighting
//   in vim is sufficient for identification
//
//   c++ commenting style is used throughout

#include "config.h"
#include "splitography.h"
#include "action_layer.h"
#include "keymap_steno.h"
#include "eeconfig.h"
/* #include "cmpitg.h" */
/* #include "keymap_dvp.h" */
#include "send_string.h"

extern keymap_config_t keymap_config;

enum splitography_layers {
  _QWERTY = 0
  ,_TXBOLT
  ,_PLOVER
  ,_BLUE
  ,_ORANGE
  ,_GREEN
  ,_NUM
  ,_END_LAYERS
};

enum splitography_keycodes {
  QWERTY = SAFE_RANGE
  ,QWERTY1
  ,QWERTY2
  ,TXBOLT
  ,PLOVER
  ,BLUE
  ,ORANGE

  // Programmer Dvorak
  ,PD_AMPR    // & | %
  ,PD_LBRC    // [ | 7
  ,PD_LCBR    // { | 5
  ,PD_RCBR    // } | 3
  ,PD_LPRN    // ( | 1
  ,PD_EQL     // = | 9
  ,PD_ASTR    // * | 0
  ,PD_RPRN    // ) | 2
  ,PD_PLUS    // + | 4
  ,PD_RBRC    // ] | 6
  ,PD_EXLM    // ! | 8
  ,PD_DLR     // $ | ~
  ,PD_HASH    // # | `
  ,PD_AT      // @ | ^
};

// keycodes
#define ___x___ KC_TRNS
#ifdef _______
#undef _______
#endif
#define _______ KC_NO

#define ST_BOLT QK_STENO_BOLT

#define PD_SPR  KC_LGUI
#define PD_ALGR KC_ALGR
// #define PD_ALGR KC_HYPR
#define PD_X KC_B
#define PD_C KC_I
#define PD_V KC_DOT
#define PD_Z KC_SLSH

// #define COPY    LCTL(KC_C)
#define COPY    LALT(PD_C)
// #define CUT     LCTL(KC_X)
#define CUT     LALT(PD_X)
// #define PASTE   LCTL(KC_V)
#define PASTE   LALT(PD_V)
// #define UNDO    LCTL(KC_Z)
#define UNDO    LALT(PD_Z)
#define SWITCHR LGUI(KC_TAB)
#define ACTV_KM LCTL(LALT(LGUI(KC_BSLS)))
// #define OMN_RUN LCTL(KC_1)
#define OMN_RUN LCTL(PD_AMPR)
#define TG_NUM  TG(_NUM)

/*
 * Escape        KC_ESC
 * Left-Control  KC_LCLT
 * Right-Control KC_RCLT
 * Left-Alt      KC_LALT
 * Right-Alt     KC_RALT
 * Left-Shift    KC_LSFT
 * Right-Shift   KC_RSFT
 * Left-Super    KC_LGUI
 * Right-Super   KC_RGUI
 * Hyper         KC_HYPR
 * AltGr         PD_ALGR
 * Capslock      KC_CAPS
 *
 * PrintScreen    KC_PSCR
 * ScrollLock     KC_SLCK
 * Pause          KC_PAUS
 * Backspace      KC_BSPC
 * Enter          KC_ENT
 *
 * &            KC_AMPR
 * %            KC_PERC
 *
 * TXBOLT
 * PLOVER
 * TG_NUM
 */

/*
 * Notes
 * + Layer QWERTY is for Programmer Dvorak
 * + Layer BLUE is for extended symbols & functions
 * + Layer ORANGE is for
 * + Layer GREEN is for shortcuts
 * + Layer NUM is for QWERTY
 * + Layer PLOVER is for Plover
 * + Layer TXBOLT is for Txbolt Stenomachine
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // ... LAYER: Qwerty turning Programmer Dvorak ...
  // ,-----------------------------------------------------------------------------------.
  // | Super|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // |  Alt |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | AltGr|
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |Orange| Blue | Space| Shift|                           |
  // `-----------------------------------------------------------------------------------'

  [_QWERTY] = {
    {PD_SPR,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, PD_ALGR},
    {_______, _______, _______, _______, ORANGE,  BLUE,    KC_SPC,  KC_LSFT, _______, _______, _______, _______},
  },

  // ... LAYER DVP: Programmer Dvorak ...
  // ,-----------------------------------------------------------------------------------.
  // | Super|   ;  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |   /  |
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // | Ctrl |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |   -  |
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // |  Alt |   '  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | AltGr|
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |Orange| Blue | Space| Shift|                           |
  // `-----------------------------------------------------------------------------------'

  /* [_QWERTY] = { */
  /*   {PD_SPR,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH}, */
  /*   {KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS}, */
  /*   {KC_LALT, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    PD_ALGR}, */
  /*   {_______, _______, _______, _______, ORANGE,  BLUE,    KC_SPC,  KC_LSFT, _______, _______, _______, _______}, */
  /* }, */

  // ... LAYER: Blue (Blue) - Extended symbols & functions...
  // .-----------------------------------------------------------------------------------.
  // | Super|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |   ~  |      |      |      | Enter|   \  |   ]  |      |      |      |   =  |
  // |-----------------------------------------------------------------------------------|
  // |  Alt |      |      |      |      |BSpace|  Del |      |      |      |      | AltGr|
  // |-----------------------------------------------------------------------------------|
  // |                           |Orange|  f() | Space| Shift|                           |
  // '-----------------------------------------------------------------------------------'

  [_BLUE] = {
    {PD_SPR,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS},
    {KC_LCTL, KC_TILD, _______, _______, _______, KC_ENT,  KC_BSLS, KC_RBRC, _______, _______, _______, KC_EQL },
    {KC_LALT, _______, _______, _______, _______, KC_BSPC, KC_DEL,  _______, _______, _______, _______, PD_ALGR},
    {_______, _______, _______, _______, ORANGE,  ___x___, KC_SPC,  KC_LSFT, _______, _______, _______, _______},
  },

  // ... LAYER DVP: Blue (Blue) - Extended symbols & functions...
  // .-----------------------------------------------------------------------------------.
  // | Super|   &  |   [  |   {  |   }  |   (  |   =  |   *  |   )  |   +  |   ]  |   !  |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |   $  |      |      |      | Enter|   \  |   @  |      |      |      |   #  |
  // |-----------------------------------------------------------------------------------|
  // |  Alt |      |      |      |      |BSpace|  Del |      |      |      |      | AltGr|
  // |-----------------------------------------------------------------------------------|
  // |                           |Orange|  f() | Space| Shift|                           |
  // '-----------------------------------------------------------------------------------'

  /* [_BLUE] = { */
  /*   {PD_SPR,  PD_AMPR, PD_LBRC, PD_LCBR, PD_RCBR, PD_LPRN, PD_EQL,  PD_ASTR, PD_RPRN, PD_PLUS, PD_RBRC, PD_EXLM}, */
  /*   {KC_LCTL, PD_DLR,  _______, _______, _______, KC_ENT,  KC_BSLS, KC_AT,   _______, _______, _______, PD_HASH}, */
  /*   {KC_LALT, _______, _______, _______, _______, KC_BSPC, KC_DEL,  _______, _______, _______, _______, PD_ALGR}, */
  /*   {_______, _______, _______, _______, ORANGE,  ___x___, KC_SPC,  KC_LSFT, _______, _______, _______, _______}, */
  /* }, */

  // ... LAYER: Orange (Orange) - TODO ...
  // .-----------------------------------------------------------------------------------.
  // | Super|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |  Tab |      | +Vol | PgUp | Home |      |      |      |      |      |  F12 |
  // |-----------------------------------------------------------------------------------|
  // |  Alt |      | Mute | -Vol | PgDn |  End |      |      |      |      |      | AltGr|
  // |-----------------------------------------------------------------------------------|
  // |                           |  f() | Blue | Space| Shift|                           |
  // '-----------------------------------------------------------------------------------'

  [_ORANGE] = {
    {PD_SPR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 },
    {KC_LCTL, KC_TAB,  _______, KC_VOLU, KC_PGUP, KC_HOME, _______, _______, _______, _______, _______, KC_F12},
    {KC_LALT, _______, KC_MUTE, KC_VOLD, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, PD_ALGR},
    {_______, _______, _______, _______, ___x___, BLUE,    KC_SPC,  KC_LSFT, _______, _______, _______, _______},
  },

  // [_ORANGE] = {
  //   {PD_SPR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_APP,  KC_PSCR, KC_SLCK, KC_PAUS, _______, _______},
  //   {KC_LCTL, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______},
  //   {KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_DEL,  KC_END,  KC_PGDN, KC_BSLS, KC_LALT},
  //   {_______, _______, _______, _______, ___x___, BLUE,    KC_TAB,  PD_ALGR, _______, _______, _______, _______},
  // },

  // ... LAYER: Green (Blue + Orange) - shortcuts ...
  // .-----------------------------------------------------------------------------------.
  // | Super|OmnRun|      |      |      |Escape|      |      |  Up  |      |      |      |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl | Caps |      |      |ActvKM|      |      | Left | Down | Right|      | RCtrl|
  // |-----------------------------------------------------------------------------------|
  // |  Alt |Switch|  Cut | Copy | Paste|      |      |      |      |      |      | AltGr|
  // |-----------------------------------------------------------------------------------|
  // |                           |  f() |  f() |TxBolt| Shift|                           |
  // '-----------------------------------------------------------------------------------'

  [_GREEN] = {
    {PD_SPR,  OMN_RUN, _______, _______, _______, KC_ESC,  _______, _______, KC_UP,   _______, _______, _______},
    {KC_LCTL, KC_CAPS, _______, _______, ACTV_KM, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_RCTL},
    {KC_LALT, SWITCHR, CUT,     COPY,    PASTE,   _______, _______, _______, _______, _______, _______, PD_ALGR},
    {_______, _______, _______, _______, ___x___, ___x___, TXBOLT,  KC_LSFT, _______, _______, _______, _______},
  },

  // ... LAYER: Num (Numlock) - QWERTY ...
  // ,-----------------------------------------------------------------------------------.
  // | Super|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
  // -------|------+------+------+------+------+------+------+------+------+-------------|
  // |  Alt |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | AltGr|
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |Orange| Blue | Space| Shift|                           |
  // `-----------------------------------------------------------------------------------'

  [_NUM] = {
    {PD_SPR,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
    {KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, PD_ALGR},
    {_______, _______, _______, _______, ORANGE,  BLUE,    KC_SPC,  KC_LSFT, _______, _______, _______, _______},
  },

  // ... LAYER: Plover - Plover ...
  // ,-----------------------------------------------------------------------------------.
  // |   1  |   1  |   1  |   1  |   1  |   1  |   1  |   1  |   1  |   1  |   1  |   1  |
  // +-------------+------+------+------+------+------+------+------+------+------+------|
  // |Qwerty|   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
  // +------|------+------+------+------+------+------+------+------+------+------+------|
  // |Qwerty|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
  // +------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |   A  |   O  |   E  |   U  |                           |
  // `-----------------------------------------------------------------------------------'

  [_PLOVER] = {
    {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
    {QWERTY1, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
    {QWERTY2, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {_______, _______, _______, _______, KC_C,    KC_V,    KC_N,    KC_M,    _______, _______, _______, _______},
  },

  // ... LAYER: Txbolt - Txbolt steno ...
  // ,-----------------------------------------------------------------------------------.
  // |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |Qwerty|   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |Qwerty|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |   A  |   O  |   E  |   U  |                           |
  // `-----------------------------------------------------------------------------------'

  [_TXBOLT] = {
    {STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC },
    {QWERTY1, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR },
    {QWERTY2, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR },
    {_______, _______, _______, _______, STN_A,   STN_O,   STN_E,   STN_U,   _______, _______, _______, _______},
  },

};

//////////////////////////////////////////////////////////////////////////////
// Keymaps
//////////////////////////////////////////////////////////////////////////////

void clear_layers(void)
{
  uint8_t layer;
  for (layer = 0; layer < _END_LAYERS; layer++) {
    layer_off(layer);
  }
}

#define QWERTY_1  1
#define QWERTY_2  2
#define QWERTY_12 3
static uint8_t qwerty_n = 0;

void qwerty(void)
{
  qwerty_n = 0;
  clear_layers();
  set_single_persistent_default_layer(_QWERTY);
}

void plover(keyrecord_t *record)
{
  if (record->event.pressed) {
    clear_layers();
    layer_on(_PLOVER);
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
  }
}

void txbolt(void)
{
  clear_layers();
  layer_on(_TXBOLT);
}

//////////////////////////////////////////////////////////////////////////////
// Custom processing of keycodes
//////////////////////////////////////////////////////////////////////////////

void timer_timeout(void);
void timer_timeout_keymap(void);
// Interrupts all timers
void timer_timeout(void){
  timer_timeout_keymap();
}
__attribute__((weak))
void timer_timeout_keymap(void){
}

bool shift_is_pressed(void) {
  return (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
}

bool dvp_send(keyrecord_t *record, const char *str1, const char *str2) {
  if (record->event.pressed) {
    if (!shift_is_pressed()) {
      send_string(str1);
    } else {
      unregister_code(KC_LSFT);
      send_string(str2);
      register_code(KC_LSFT);
    }
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    // Programmer Dvorak
  case PD_AMPR:
    return dvp_send(record, "&", "%");
  case PD_LBRC:
    return dvp_send(record, "[", "7");
  case PD_LCBR:
    return dvp_send(record, "{", "5");
  case PD_RCBR:
    return dvp_send(record, "}", "3");
  case PD_LPRN:
    return dvp_send(record, "(", "1");
  case PD_EQL:
    return dvp_send(record, "=", "9");
  case PD_ASTR:
    return dvp_send(record, "*", "0");
  case PD_RPRN:
    return dvp_send(record, ")", "2");
  case PD_PLUS:
    return dvp_send(record, "+", "4");
  case PD_RBRC:
    return dvp_send(record, "]", "6");
  case PD_EXLM:
    return dvp_send(record, "!", "8");
  case PD_DLR:
    return dvp_send(record, "$", "~");
  case PD_HASH:
    return dvp_send(record, "#", "`");
  case PD_AT:
    return dvp_send(record, "@", "^");

  case QWERTY:
    if (record->event.pressed) {
      qwerty();
    }
    return false;
  case QWERTY1:
    if (record->event.pressed) {
      qwerty_n = qwerty_n | QWERTY_1;
      if (qwerty_n == QWERTY_12) {
        qwerty();
      }
    } else {
      qwerty_n = qwerty_n & ~QWERTY_1;
    }
    return false;
  case QWERTY2:
    if (record->event.pressed) {
      qwerty_n = qwerty_n | QWERTY_2;
      if (qwerty_n == QWERTY_12) {
        qwerty();
      }
    } else {
      qwerty_n = qwerty_n & ~QWERTY_2;
    }
    return false;
  case BLUE:
    if (record->event.pressed) {
      layer_on        (_BLUE);
      update_tri_layer(_BLUE, _ORANGE, _GREEN);
    } else {
      layer_off       (_BLUE);
      update_tri_layer(_BLUE, _ORANGE, _GREEN);
    }
    return false;
  case ORANGE:
    if (record->event.pressed) {
      layer_on        (_ORANGE);
      update_tri_layer(_BLUE, _ORANGE, _GREEN);
    } else {
      layer_off       (_ORANGE);
      update_tri_layer(_BLUE, _ORANGE, _GREEN);
    }
    return false;
  case PLOVER:
    plover(record);
    return false;
  case TXBOLT:
    if (record->event.pressed) {
      txbolt();
    }
    return false;
  }
  return true;
}

// initialize steno protocol
void matrix_init_user(void)
{
  steno_set_mode(STENO_MODE_BOLT);
}
