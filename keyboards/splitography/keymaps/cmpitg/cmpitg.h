#pragma once

#include "quantum.h"
#include "sendstring_dvp.h"
#include "send_string.h"

/*
Templates for Keys, with custom shifted and non shifted Characters
*/

// Normal shift status
#define SHIFT_NORM2(str1, str2)                 \
  if (record->event.pressed) {                  \
    if (lshift || rshift) {                     \
      send_string(str2);                        \
    } else {                                    \
      send_string(str1);                        \
    }                                           \
  }                                             \
  return false;

// Normal shift status
#define SHIFT_NORM(kc1, kc2)                    \
  if (record->event.pressed) {                  \
    timer_timeout();                            \
    if (lshift || rshift) {                     \
      register_code(KC_LSFT);                   \
      unregister_code(kc2);                     \
      register_code(kc2);                       \
      add_to_prev(kc2);                         \
    } else {                                    \
      unregister_code(KC_LSFT);                 \
      unregister_code(kc1);                     \
      register_code(kc1);                       \
    }                                           \
  } else {                                      \
    unregister_code(kc1);                       \
    unregister_code(kc2);                       \
  }                                             \
  return false;

// Inverted shift status
#define SHIFT_SWITCH(kc1, kc2)                  \
  if (record->event.pressed) {                  \
    timer_timeout();                            \
    if (lshift || rshift) {                     \
      unregister_code(KC_LSFT);                 \
      unregister_code(kc2);                     \
      register_code(kc2);                       \
      add_to_prev(kc2);                         \
    } else {                                    \
      register_code(KC_LSFT);                   \
      unregister_code(kc1);                     \
      register_code(kc1);                       \
      add_to_prev(kc1);                         \
    }                                           \
  } else {                                      \
    unregister_code(kc1);                       \
    unregister_code(kc2);                       \
    unreg_prev();                               \
    if (lshift || rshift)                       \
      register_code(KC_LSFT);                   \
    else                                        \
      unregister_code(KC_LSFT);                 \
  }                                             \
  return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2)                     \
  if (record->event.pressed) {                  \
    timer_timeout();                            \
    register_code(KC_LSFT);                     \
    if (lshift || rshift) {                     \
      unregister_code(kc2);                     \
      register_code(kc2);                       \
      add_to_prev(kc2);                         \
    } else {                                    \
      unregister_code(kc1);                     \
      register_code(kc1);                       \
      add_to_prev(kc1);                         \
    }                                           \
  } else {                                      \
    unregister_code(kc1);                       \
    unregister_code(kc2);                       \
    unreg_prev();                               \
    if (lshift || rshift)                       \
      register_code(KC_LSFT);                   \
    else                                        \
      unregister_code(KC_LSFT);                 \
  }                                             \
  return false;

// Never shifted
#define SHIFT_NO(kc1, kc2)                      \
  if (record->event.pressed) {                  \
    timer_timeout();                            \
    unregister_code(KC_LSFT);                   \
    if (lshift || rshift) {                     \
      unregister_code(kc2);                     \
      register_code(kc2);                       \
      add_to_prev(kc2);                         \
    } else {                                    \
      unregister_code(kc1);                     \
      register_code(kc1);                       \
    }                                           \
  } else {                                      \
    unregister_code(kc1);                       \
    unregister_code(kc2);                       \
    unreg_prev();                               \
    if (lshift || rshift)                       \
      register_code(KC_LSFT);                   \
    else                                        \
      unregister_code(KC_LSFT);                 \
  }                                             \
  return false;

void timer_timeout(void);
void timer_timeout_keymap(void);

// Interrupt and times for Nav/Esc
bool navesc = false;

// These indicate if left and right shift are physically pressed
bool lshift = false;
bool rshift = false;

extern uint8_t prev_indx;
extern uint16_t prev_kcs[6];
void add_to_prev(uint16_t kc);
void unreg_prev(void);
