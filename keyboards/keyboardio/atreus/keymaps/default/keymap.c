// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

#include "oneshot.h"

#define TH_LM LT(_NUM_NAV,KC_SPC)
#define TH_LR MT(MOD_LSFT, KC_TAB)
#define TH_RL MT(MOD_RSFT, KC_ENT)
#define TH_RM LT(_SYM,KC_BSPC)

// void oneshot_mods_changed_user(uint8_t mods) {
//   if (mods & MOD_MASK_SHIFT) {
//     println("Oneshot mods SHIFT");
//   }
//   if (mods & MOD_MASK_CTRL) {
//     println("Oneshot mods CTRL");
//   }
//   if (mods & MOD_MASK_ALT) {
//     println("Oneshot mods ALT");
//   }
//   if (mods & MOD_MASK_GUI) {
//     println("Oneshot mods GUI");
//   }
//   if (!mods) {
//     println("Oneshot mods off");
//   }
// };

enum layer_names {
    _BASE,
    _NUM_NAV,
    _SYM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    // SW_WIN,  // Switch to next window         (cmd-tab)
    // SW_LANG, // Switch to next input language (ctl-spc)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                       KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                       KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_PAUS,  KC_MNXT,  KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_QUES,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_ESC, TH_LM,  TH_LR,    TH_RL,    TH_RM,  KC_DEL, KC_BRIU, KC_BRID, KC_SLEP),

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_NUM_NAV] = LAYOUT( /* [> NUM_NAV <] */
    KC_0,    KC_1,    KC_2,    KC_3,    KC_4,                        KC_PGUP, LGUI(KC_Z), KC_UP,      LSG(KC_Z),  _______,
    OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, KC_5,                        KC_HOME, KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,
    KC_DOT,  KC_9,    KC_8,    KC_7,    KC_6,    _______,   _______, KC_PGDN, LGUI(KC_V), LGUI(KC_C), LGUI(KC_X), _______,
    _______, _______, _______, _______, _______, _______,   KC_ENT,  KC_BSPC, KC_DEL,     _______,    _______,    _______),

  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_SYM] = LAYOUT( /* [> SYM <] */
    KC_SLSH,  KC_PIPE,  KC_BSLS,  KC_LCBR,  KC_RCBR,                      KC_DLR,  KC_HASH, KC_AT,   KC_EXLM, KC_GRAVE,
    KC_LT,    KC_EQUAL, KC_GT,    KC_LPRN,  KC_RPRN,                      KC_PERC, OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
    KC_TILDE, KC_UNDS,  KC_MINUS, KC_LBRC,  KC_RBRC,  _______,   _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_QUOTE,
    _______,  _______,  _______,  KC_ESC,   KC_SPACE, KC_TAB,    _______, _______, _______, _______, _______, _______)
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case KC_ESC:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case TH_LM:
    case TH_LR:
    case TH_RL:
    case TH_RM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}
