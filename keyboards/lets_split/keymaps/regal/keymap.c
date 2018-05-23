#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _DEV 8
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  DEV_ON,
  DEV_OFF,
  ADJUST,
  CPY_PST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CTL_ESC CTL_T(KC_ESC)
#define CMD_LSB LGUI(KC_LBRACKET)
#define CMD_RSB RGUI(KC_RBRACKET)

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 300

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |^/Esc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Enter |Leader|  Alt |  Cmd |Lower |Space |Space |Raise | Cmd  | Alt  | Ctrl |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, \
  CTL_ESC, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
  KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT , \
  KC_ENT,  KC_LEAD, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTRL, KC_ENT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |cmd+[ |cmd+] |  Up  |      |      |  =   |   -  |      |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift | Dev  | Left | Down |Right |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |  Cmd |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_LCTRL, CMD_LSB, CMD_RSB, KC_UP,   _______, _______, KC_EQL,  KC_MINS, _______, KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_LSFT,  DEV_ON,     KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_ENT, \
  _______,  _______, KC_LALT, KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |      |  (   |  {   |  }   |  )   |   +  |   _  |  Up  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |      |      |      |      |      |      | Left | Down |Right | Dev  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |  Cmd |      |             |      | Cmd  | Alt  | Ctrl |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_LCTRL, _______, KC_LPRN, KC_LCBR, KC_RCBR, KC_RPRN, KC_UNDS, KC_UNDS, KC_UP,   KC_LCBR, KC_RCBR, KC_BSLS, \
  KC_LSFT, _______,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, DEV_ON,  KC_RSFT, \
  _______, _______,  KC_LALT, KC_LGUI, _______, _______, _______, _______, KC_RGUI, KC_RALT, KC_RCTRL,KC_ENT \
),

/* Dev
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |cpypst|      |      |emcscp|viLast|scrnsht|ntpd |      |      | // emcsp = alt+| pbcopy<RET>
 * |------+------+------+------+------+-------------+------+------+------+------+------| // viLast = vim $(!! -l)
 * |      | Redo | El   | cnsl |      |      | Redo | El   | cnsl |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |      | Undo | Cut  | Copy |Paste |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Leave|      |      |      |      |             |      |      |      |      | Leave|
 * `-----------------------------------------------------------------------------------'
 */
[_DEV] = LAYOUT( \
  _______, _______,  _______, CPY_PST, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  DEV_OFF, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, DEV_OFF \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case DEV_ON:
      if (record->event.pressed) {
        layer_on(_DEV);
      }
      return false;
      break;
    case DEV_OFF:
      if (record->event.pressed) {
        layer_off(_DEV);
      }
      return false;
      break;
    case CPY_PST:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
      } else {
        SEND_STRING(SS_LGUI("v"));
      }
      return false;
      break;
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_E) {
      // Open blank text editor (TextEdit.app via spotlight)
      SEND_STRING(SS_LGUI(" ")"textedit"SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_V) {
      // Open last ag results in vim
      SEND_STRING("vim $(!! -l)"SS_TAP(X_ENTER)SS_TAP(X_ENTER));
    }
  }
}
