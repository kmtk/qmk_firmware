#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define L_BASIC  0   // Basic layer
#define L_CODE   1   // Coding layer
#define L_NAVI   2   // Mavigation layer
#define L_RESET  3   // Reset layer

// The most portable copy/paste keys
#define KT_CUT    LCTL(KC_X)   // ctrl + x
#define KT_COPY   LCTL(KC_C)   // ctrl + c
#define KT_PSTE   LCTL(KC_V)   // ctrl + v
#define KT_UNDO   LCTL(KC_Z)   // ctrl + z

// Original define
#define KT_TGCO   TG(L_CODE)         // Toggle: Coding layer
#define KT_TGNV   TG(L_NAVI)         // Toggle: Navigation layer
#define KT_MORS   MO(L_RESET)        // Momentary: Reset layer
#define KT_WIN    GUI_T(KC_NO)       // windows key
#define KT_KEYP   LALT(KC_SPC)       // keypirinha shortcut
#define KT_SPSF   SFT_T(KC_SPC)      // tap: Space / hold: Shift
#define KT_SPCO   LT(L_CODE,KC_SPC)  // tap: Space / hold: Coding layer
#define KT_TBCO   LT(L_CODE,KC_TAB)  // tap: Tab   / hold: Coding layer
#define KT_TBNV   LT(L_NAVI,KC_TAB)  // tap: Tab   / hold: Navigation layer
#define KT_F2AL   ALT_T(KC_F2)       // tap: F2    / hold: Alt
#define KT_ESWN   GUI_T(KC_ESC)      // tap: Esc   / hold: Win
#define KT_BSCO   LT(L_CODE,KC_BSPC) // tap: BS    / hold: Coding layer
#define KT_BSNV   LT(L_NAVI,KC_BSPC) // tap: BS    / hold: Navigation layer
#define KT_ENCL   RCTL_T(KC_ENT)     // tap: Enter / hold: Ctrl

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      |           |MO(RS)|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------| Cut  |           | Undo |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Copy |           | Paste|   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |TG(NV)| Win  |      |Alt+SP| MHEN |                                       | HENK |Alt+SP|      |      |TG(CO)|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | DEL  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Space | Tab  |Alt+SP|       |      |      |ENTER |
 *                                 |  /   |  /   |------|       |------| BS   | /    |
 *                                 | L2   |F2/Alt|       |Esc/Wn|      |RCtrl |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_BASIC] = LAYOUT_ergodox(  // layer 0 : default
       // left hand
       KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KT_CUT,
       KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KT_COPY,
       KT_TGNV, KT_WIN,  _______, KT_KEYP, KC_MHEN,
                                           _______, _______,
                                                    KT_KEYP,
                                  KT_SPCO, KT_TBNV, KT_F2AL,
       // right hand
       KT_MORS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
       KT_UNDO, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
       KT_PSTE ,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                         KC_HENK, KT_KEYP, _______, _______, KT_TGCO,
       _______, KC_DEL,
       _______,
       KT_ESWN, KC_BSPC, KT_ENCL
    ),
/* Keymap 1: Coding Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  | JYEN |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ***   |      |      |      |      |                                       |   0  |    . |      |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      | ***  |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CODE] = LAYOUT_ergodox(
       // left hand
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
       _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_JYEN,
       _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
       _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
       // right hand
       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
       _______, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
                         KC_0,    KC_DOT,  _______, KC_EQL,  _______,
       _______, _______,
       _______,
       _______, _______, _______
    ),
/* Keymap 2: mouse and cursol keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |MsWlLt| MsUp |MsWlRt|      |      |           |      |      | HOME |  Up  | END  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Rght |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsWlDn|      |MsWlUp|      |      |           |      |      | PgDn |      | PgUp |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      | ***  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------| ***  |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_NAVI] = LAYOUT_ergodox(
       // left hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, KC_WH_D, _______, KC_WH_U, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  KC_BTN1, KC_BTN2, _______,
       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______,
                _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
       _______, _______, KC_PGDN, _______, KC_PGUP, _______, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
    ),

/* Keymap 9: reset
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |           | ***  |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_RESET] = LAYOUT_ergodox(
       // left hand
       RESET,   _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
   ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(L_CODE)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
