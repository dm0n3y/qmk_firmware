// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)

#define MT_LSFT(KC) MT(MOD_LSFT, KC)
#define MT_RSFT(KC) MT(MOD_RSFT, KC)

void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot mods GUI");
  }
  if (!mods) {
    println("Oneshot mods off");
  }
};

enum layer_names {
    _BASE,
    _NUM_NAV,
    _SYM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                                                     KC_Y,             KC_U,   KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                                                     KC_H,             KC_J,   KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                KC_PAUS,            KC_MNXT,         KC_N,             KC_M,   KC_COMM, KC_DOT,  KC_QUES,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_ESC, LT(_NUM_NAV,KC_SPC), MT_LSFT(KC_TAB),    MT_RSFT(KC_ENT), LT(_SYM,KC_BSPC), KC_DEL, KC_BRIU, KC_BRID, KC_SLEP),

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_NUM_NAV] = LAYOUT( /* [> NUM_NAV <] */
    KC_0,    KC_1,    KC_2,    KC_3,    KC_4,                        KC_PGUP, LGUI(KC_Z), KC_UP,      LSG(KC_Z),  _______,
    OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_5,                        KC_HOME, KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,
    KC_DOT,  KC_9,    KC_8,    KC_7,    KC_6,    _______,   _______, KC_PGDN, LGUI(KC_V), LGUI(KC_C), LGUI(KC_X), _______,
    _______, _______, _______, _______, _______, _______,   KC_ENT,  KC_BSPC, KC_DEL,     _______,    _______,    _______),
    // KC_EXLM, KC_AT,   KC_UP,   KC_DLR,  KC_PERC,                  KC_PGUP, KC_7,    KC_8,   KC_9, KC_BSPC,
    // KC_LPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_RPRN,                  KC_PGDN, KC_4,    KC_5,   KC_6, KC_BSLS,
    // KC_LBRC, KC_RBRC, KC_HASH, KC_LCBR, KC_RCBR, KC_CIRC, KC_AMPR,KC_ASTR, KC_1,    KC_2,   KC_3, KC_PLUS,
    // TG(_LW), KC_INS,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT,KC_SPC,  KC_TRNS, KC_DOT, KC_0, KC_EQL ),
  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_SYM] = LAYOUT( /* [> SYM <] */
    KC_SLSH,  KC_PIPE,  KC_BSLS,  KC_LCBR,  KC_RCBR,                      KC_DLR,  KC_HASH, KC_AT,   KC_EXLM, KC_GRAVE,
    KC_LT,    KC_EQUAL, KC_GT,    KC_LPRN,  KC_RPRN,                      KC_PERC, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL,
    KC_TILDE, KC_UNDS,  KC_MINUS, KC_LBRC,  KC_RBRC,  _______,   _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_QUOTE,
    _______,  _______,  _______,  KC_ESC,   KC_SPACE, KC_TAB,    _______, _______, _______, _______, _______, _______)
    // KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
    // KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11  ,
    // KC_NO,   KC_VOLU, KC_NO,   KC_NO,   QK_BOOT,   _______, _______, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12  ,
    // KC_NO,   KC_VOLD, KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  TO(_QW), KC_PSCR, KC_SCRL, KC_PAUS )
};
