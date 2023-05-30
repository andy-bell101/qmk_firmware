/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include <stdio.h>

#define RGB_MODE_PRINTER(buffer_size, format, rgb_mode)             \
    {                                                               \
        char buffer[buffer_size];                                   \
        snprintf(buffer, buffer_size, format, mode - rgb_mode + 1); \
        oled_write_ln(buffer, false);                               \
    }

enum layers {
    _QWERTY_UK = 0,
    _QWERTY_US,
    _GAMING,
    // _DVORAK,
    // _COLEMAK_DH,
    _NAV,
    _SYM_UK,
    _SYM_US,
    _FUNCTION_UK,
    _FUNCTION_US,
    _ADJUST,
};

// Aliases for readability
#define QWERTY_UK DF(_QWERTY_UK)
#define QWERTY_US DF(_QWERTY_US)
#define GAMING DF(_GAMING)
#define QWERTY_US_MASK (1 << _QWERTY_US)
#define GAMING_MASK (1 << _GAMING)
// #define COLEMAK  DF(_COLEMAK_DH)
// #define DVORAK   DF(_DVORAK)

#define SYM_UK MO(_SYM_UK)
#define SYM_US MO(_SYM_US)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define ADJUST MO(_ADJUST)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, UK_QUOT)
#define CTL_MINS MT(MOD_RCTL, UK_MINS)
#define LALT_ENT MT(MOD_LALT, KC_ENT)
#define RALT_ENT MT(MOD_RALT, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

enum td_keycodes {
    CTL_QUOTE_DQUO,  // Ctl when held, single tap quote, double tap double quote
    O_BRKT,          // tap (, double tap [, triple tap {
    C_BRKT,          // tap ), double tap ], triple tap }
    SLASH_BACKSLASH, // tap /, double tap backslash
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
} td_state_t;

static td_state_t td_state;

// Declare your tap dance functions

td_state_t cur_dance(tap_dance_state_t *state);

void ctl_quote_dquo_finished(tap_dance_state_t *state, void *user_data);
void ctl_quote_dquo_reset(tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────────┬───┬───┬──────────────┬──────┬──────────┐                                                        ┌──────┬──────┬───────────────────┬───┬─────────────────────┬────────────────────┐
//    │      tab      │ q │ w │      e       │  r   │    t     │                                                        │  y   │  u   │         i         │ o │          p          │        bspc        │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┤                                                        ├──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │    CTL_ESC    │ a │ s │      d       │  f   │    g     │                                                        │  h   │  j   │         k         │ l │          ;          │ TD(CTL_QUOTE_DQUO) │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┼────────────┬──────────────┐   ┌───────────┬────────────┼──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │ OSM(MOD_LSFT) │ z │ x │      c       │  v   │    b     │ TD(O_BRKT) │     mply     │   │   mute    │ TD(C_BRKT) │  n   │  m   │         ,         │ . │ TD(SLASH_BACKSLASH) │         -          │
//    └───────────────┴───┴───┼──────────────┼──────┼──────────┼────────────┼──────────────┤   ├───────────┼────────────┼──────┼──────┼───────────────────┼───┴─────────────────────┴────────────────────┘
//                            │ OSL(_ADJUST) │ lgui │ LALT_ENT │    spc     │ OSL(_SYM_UK) │   │ OSL(_NAV) │  RALT_ENT  │ bspc │ rgui │ OSL(_FUNCTION_UK) │
//                            └──────────────┴──────┴──────────┴────────────┴──────────────┘   └───────────┴────────────┴──────┴──────┴───────────────────┘
[_QWERTY_UK] = LAYOUT(
  KC_TAB        , UK_Q , UK_W , UK_E         , UK_R    , UK_T     ,                                                          UK_Y    , UK_U    , UK_I              , UK_O   , UK_P                , KC_BSPC           ,
  CTL_ESC       , UK_A , UK_S , UK_D         , UK_F    , UK_G     ,                                                          UK_H    , UK_J    , UK_K              , UK_L   , UK_SCLN             , TD(CTL_QUOTE_DQUO),
  OSM(MOD_LSFT) , UK_Z , UK_X , UK_C         , UK_V    , UK_B     , TD(O_BRKT) , KC_MPLY      ,     KC_MUTE   , TD(C_BRKT) , UK_N    , UK_M    , UK_COMM           , UK_DOT , TD(SLASH_BACKSLASH) , UK_MINS           ,
                                OSL(_ADJUST) , KC_LGUI , LALT_ENT , KC_SPC     , OSL(_SYM_UK) ,     OSL(_NAV) , RALT_ENT   , KC_BSPC , KC_RGUI , OSL(_FUNCTION_UK)
),

//    ┌───────────────┬───┬───┬──────────────┬──────┬──────────┐                                                        ┌──────┬──────┬───────────────────┬───┬─────────────────────┬────────────────────┐
//    │      tab      │ q │ w │      e       │  r   │    t     │                                                        │  y   │  u   │         i         │ o │          p          │        bspc        │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┤                                                        ├──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │    CTL_ESC    │ a │ s │      d       │  f   │    g     │                                                        │  h   │  j   │         k         │ l │          ;          │ TD(CTL_QUOTE_DQUO) │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┼────────────┬──────────────┐   ┌───────────┬────────────┼──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │ OSM(MOD_LSFT) │ z │ x │      c       │  v   │    b     │ TD(O_BRKT) │     mply     │   │   mute    │ TD(C_BRKT) │  n   │  m   │         ,         │ . │ TD(SLASH_BACKSLASH) │         -          │
//    └───────────────┴───┴───┼──────────────┼──────┼──────────┼────────────┼──────────────┤   ├───────────┼────────────┼──────┼──────┼───────────────────┼───┴─────────────────────┴────────────────────┘
//                            │ OSL(_ADJUST) │ lgui │ LALT_ENT │    spc     │ OSL(_SYM_US) │   │ OSL(_NAV) │  RALT_ENT  │ bspc │ rgui │ OSL(_FUNCTION_US) │
//                            └──────────────┴──────┴──────────┴────────────┴──────────────┘   └───────────┴────────────┴──────┴──────┴───────────────────┘
[_QWERTY_US] = LAYOUT(
  KC_TAB        , KC_Q , KC_W , KC_E         , KC_R    , KC_T     ,                                                          KC_Y    , KC_U    , KC_I              , KC_O   , KC_P                , KC_BSPC           ,
  CTL_ESC       , KC_A , KC_S , KC_D         , KC_F    , KC_G     ,                                                          KC_H    , KC_J    , KC_K              , KC_L   , KC_SCLN             , TD(CTL_QUOTE_DQUO),
  OSM(MOD_LSFT) , KC_Z , KC_X , KC_C         , KC_V    , KC_B     , TD(O_BRKT) , KC_MPLY      ,     KC_MUTE   , TD(C_BRKT) , KC_N    , KC_M    , KC_COMM           , KC_DOT , TD(SLASH_BACKSLASH) , KC_MINS           ,
                                OSL(_ADJUST) , KC_LGUI , LALT_ENT , KC_SPC     , OSL(_SYM_US) ,     OSL(_NAV) , RALT_ENT   , KC_BSPC , KC_RGUI , OSL(_FUNCTION_US)
),

//    ┌───────────────┬───┬───┬──────────────┬──────┬──────────┐                                                        ┌──────┬──────┬───────────────────┬───┬─────────────────────┬────────────────────┐
//    │      tab      │ t │ q │      w       │  e   │    r     │                                                        │  y   │  u   │         i         │ o │          p          │        bspc        │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┤                                                        ├──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │    CTL_ESC    │ g │ a │      s       │  d   │    f     │                                                        │  h   │  j   │         k         │ l │          ;          │ TD(CTL_QUOTE_DQUO) │
//    ├───────────────┼───┼───┼──────────────┼──────┼──────────┼────────────┬──────────────┐   ┌───────────┬────────────┼──────┼──────┼───────────────────┼───┼─────────────────────┼────────────────────┤
//    │ OSM(MOD_LSFT) │ b │ z │      x       │  c   │    v     │ TD(O_BRKT) │     mply     │   │   mute    │ TD(C_BRKT) │  n   │  m   │         ,         │ . │ TD(SLASH_BACKSLASH) │         -          │
//    └───────────────┴───┴───┼──────────────┼──────┼──────────┼────────────┼──────────────┤   ├───────────┼────────────┼──────┼──────┼───────────────────┼───┴─────────────────────┴────────────────────┘
//                            │ OSL(_ADJUST) │ lgui │ LALT_ENT │    spc     │ OSL(_SYM_UK) │   │ OSL(_NAV) │  RALT_ENT  │ bspc │ rgui │ OSL(_FUNCTION_UK) │
//                            └──────────────┴──────┴──────────┴────────────┴──────────────┘   └───────────┴────────────┴──────┴──────┴───────────────────┘
[_GAMING] = LAYOUT(
  KC_TAB        , UK_T , UK_Q , UK_W         , UK_E    , UK_R     ,                                                          UK_Y    , UK_U    , UK_I              , UK_O   , UK_P                , KC_BSPC           ,
  CTL_ESC       , UK_G , UK_A , UK_S         , UK_D    , UK_F     ,                                                          UK_H    , UK_J    , UK_K              , UK_L   , UK_SCLN             , TD(CTL_QUOTE_DQUO),
  OSM(MOD_LSFT) , UK_B , UK_Z , UK_X         , UK_C    , UK_V     , TD(O_BRKT) , KC_MPLY      ,     KC_MUTE   , TD(C_BRKT) , UK_N    , UK_M    , UK_COMM           , UK_DOT , TD(SLASH_BACKSLASH) , UK_MINS           ,
                                OSL(_ADJUST) , KC_LGUI , LALT_ENT , KC_SPC     , OSL(_SYM_UK) ,     OSL(_NAV) , RALT_ENT   , KC_BSPC , KC_RGUI , OSL(_FUNCTION_UK)
),

//    ┌─────┬──────┬──────┬──────┬──────┬─────┐                            ┌──────┬──────┬──────┬──────┬──────┬──────┐
//    │     │      │      │      │      │     │                            │ home │ pgdn │ pgup │ end  │ volu │ del  │
//    ├─────┼──────┼──────┼──────┼──────┼─────┤                            ├──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │ lgui │ lalt │ lctl │ lsft │     │                            │ left │ down │  up  │ rght │ vold │ ins  │
//    ├─────┼──────┼──────┼──────┼──────┼─────┼─────┬──────┐   ┌─────┬─────┼──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │      │      │      │      │     │     │ sCRL │   │     │     │ paus │ mprv │ mply │ mnxt │ mute │ pscr │
//    └─────┴──────┴──────┼──────┼──────┼─────┼─────┼──────┤   ├─────┼─────┼──────┼──────┼──────┼──────┴──────┴──────┘
//                        │      │      │     │     │      │   │     │     │      │      │      │
//                        └──────┴──────┴─────┴─────┴──────┘   └─────┴─────┴──────┴──────┴──────┘
[_NAV] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                                             KC_HOME  , KC_PGDN , KC_PGUP , KC_END  , KC_VOLU , KC_DEL ,
  _______ , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,                                             KC_LEFT  , KC_DOWN , KC_UP   , KC_RGHT , KC_VOLD , KC_INS ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_SCRL ,     _______ , _______ , KC_PAUSE , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , KC_PSCR,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______  , _______ , _______
),

//    ┌───┬───┬───┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬───┬───┬───┐
//    │ ` │ 1 │ 2 │  3  │  4  │  5  │                           │  6  │  7  │  8  │ 9 │ 0 │ = │
//    ├───┼───┼───┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼───┼───┼───┤
//    │ ~ │ ! │ @ │  #  │  $  │  %  │                           │  ^  │  &  │  *  │ ( │ ) │ + │
//    ├───┼───┼───┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼───┼───┼───┤
//    │ | │ \ │ : │  ;  │  -  │  [  │  {  │     │   │     │  }  │  ]  │  _  │  ,  │ . │ / │ ? │
//    └───┴───┴───┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼───┴───┴───┘
//                │     │     │     │     │     │   │     │     │     │     │     │
//                └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_SYM_UK] = LAYOUT(
  UK_GRV  , UK_1    , UK_2    , UK_3    , UK_4    , UK_5    ,                                             UK_6    , UK_7    , UK_8    , UK_9    , UK_0    , UK_EQL ,
  UK_TILD , UK_EXLM , UK_AT   , UK_HASH , UK_DLR  , UK_PERC ,                                             UK_CIRC , UK_AMPR , UK_ASTR , UK_LPRN , UK_RPRN , UK_PLUS,
  UK_PIPE , UK_BSLS , UK_COLN , UK_SCLN , UK_MINS , UK_LBRC , UK_LCBR , _______ ,     _______ , UK_RCBR , UK_RBRC , UK_UNDS , UK_COMM , UK_DOT  , UK_SLSH , UK_QUES,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌───┬───┬───┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬───┬───┬───┐
//    │ ` │ 1 │ 2 │  3  │  4  │  5  │                           │  6  │  7  │  8  │ 9 │ 0 │ = │
//    ├───┼───┼───┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼───┼───┼───┤
//    │ ~ │ ! │ @ │  #  │  $  │  %  │                           │  ^  │  &  │  *  │ ( │ ) │ + │
//    ├───┼───┼───┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼───┼───┼───┤
//    │ | │ \ │ : │  ;  │  -  │  [  │  {  │     │   │     │  }  │  ]  │  _  │  ,  │ . │ / │ ? │
//    └───┴───┴───┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼───┴───┴───┘
//                │     │     │     │     │     │   │     │     │     │     │     │
//                └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_SYM_US] = LAYOUT(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                             KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_EQL ,
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                                             KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PLUS,
  KC_PIPE , KC_BSLS , KC_COLN , KC_SCLN , KC_MINS , KC_LBRC , KC_LCBR , _______ ,     _______ , KC_RCBR , KC_RBRC , KC_UNDS , KC_COMM , KC_DOT  , KC_SLSH , KC_QUES,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬───┬───┬─────┐
//    │     │ f9 │ f10 │ f11 │ f12 │     │                           │  *  │  7  │  8  │ 9 │ + │     │
//    ├─────┼────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼───┼───┼─────┤
//    │     │ f5 │ f6  │ f7  │ f8  │     │                           │  /  │  4  │  5  │ 6 │ - │     │
//    ├─────┼────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼───┼───┼─────┤
//    │     │ f1 │ f2  │ f3  │ f4  │     │     │     │   │     │     │  0  │  1  │  2  │ 3 │ . │     │
//    └─────┴────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼───┴───┴─────┘
//                     │     │     │     │     │     │   │     │     │     │     │     │
//                     └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_FUNCTION_UK] = LAYOUT(
  _______ , KC_F9 , KC_F10 , KC_F11  , KC_F12  , _______ ,                                             UK_ASTR , UK_7    , UK_8    , UK_9 , UK_PLUS , _______,
  _______ , KC_F5 , KC_F6  , KC_F7   , KC_F8   , _______ ,                                             UK_SLSH , UK_4    , UK_5    , UK_6 , UK_MINS , _______,
  _______ , KC_F1 , KC_F2  , KC_F3   , KC_F4   , _______ , _______ , _______ ,     _______ , _______ , UK_0    , UK_1    , UK_2    , UK_3 , UK_DOT  , _______,
                             _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬───┬───┬─────┐
//    │     │ f9 │ f10 │ f11 │ f12 │     │                           │  *  │  7  │  8  │ 9 │ + │     │
//    ├─────┼────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼───┼───┼─────┤
//    │     │ f5 │ f6  │ f7  │ f8  │     │                           │  /  │  4  │  5  │ 6 │ - │     │
//    ├─────┼────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼───┼───┼─────┤
//    │     │ f1 │ f2  │ f3  │ f4  │     │     │     │   │     │     │  0  │  1  │  2  │ 3 │ . │     │
//    └─────┴────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼───┴───┴─────┘
//                     │     │     │     │     │     │   │     │     │     │     │     │
//                     └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_FUNCTION_US] = LAYOUT(
  _______ , KC_F9 , KC_F10 , KC_F11  , KC_F12  , _______ ,                                             KC_ASTR , KC_7    , KC_8    , KC_9 , KC_PLUS , _______,
  _______ , KC_F5 , KC_F6  , KC_F7   , KC_F8   , _______ ,                                             KC_SLSH , KC_4    , KC_5    , KC_6 , KC_MINS , _______,
  _______ , KC_F1 , KC_F2  , KC_F3   , KC_F4   , _______ , _______ , _______ ,     _______ , _______ , KC_0    , KC_1    , KC_2    , KC_3 , KC_DOT  , _______,
                             _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬───────────┬─────┬─────┬─────┐                           ┌─────────┬─────────┬─────────┬─────────┬──────────┬─────┐
//    │     │     │ QWERTY_UK │     │     │     │                           │         │         │         │         │          │     │
//    ├─────┼─────┼───────────┼─────┼─────┼─────┤                           ├─────────┼─────────┼─────────┼─────────┼──────────┼─────┤
//    │     │     │ QWERTY_US │     │     │     │                           │ RGB_TOG │ RGB_SAI │ RGB_HUI │ RGB_VAI │ RGB_MOD  │     │
//    ├─────┼─────┼───────────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────────┼─────────┼─────────┼─────────┼──────────┼─────┤
//    │     │     │  GAMING   │     │     │     │     │     │   │     │     │         │ RGB_SAD │ RGB_HUD │ RGB_VAD │ RGB_RMOD │     │
//    └─────┴─────┴───────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────────┼─────────┼─────────┼─────────┴──────────┴─────┘
//                            │     │     │     │     │     │   │     │     │         │         │         │
//                            └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────────┴─────────┴─────────┘
[_ADJUST] = LAYOUT(
  _______ , _______ , QWERTY_UK , _______ , _______ , _______ ,                                             _______ , _______ , _______ , _______ , _______  , _______,
  _______ , _______ , QWERTY_US , _______ , _______ , _______ ,                                             RGB_TOG , RGB_SAI , RGB_HUI , RGB_VAI , RGB_MOD  , _______,
  _______ , _______ , GAMING    , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , RGB_SAD , RGB_HUD , RGB_VAD , RGB_RMOD , _______,
                                  _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
)
};

// more tap-dance stuff
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    }

    return TD_UNKNOWN;
}

void ctl_quote_dquo_finished(tap_dance_state_t *state, void *user_data) {
    uint16_t quote = UK_QUOT;
    uint16_t dquot = UK_DQUO;
    if (default_layer_state == QWERTY_US_MASK) {
        quote = KC_QUOT;
        dquot = KC_DQUO;
    }
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code16(quote);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(dquot);
            break;
        default:
            break;
    }
}

void ctl_quote_dquo_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
        default:
            break;
    }
}

void o_brkt_fn(tap_dance_state_t *state, void *user_data) {
    uint16_t open_bracket = UK_LPRN;
    uint16_t open_square = UK_LBRC;
    uint16_t open_curly = UK_LCBR;
    if (default_layer_state == QWERTY_US_MASK) {
        open_bracket = KC_LPRN;
        open_square = KC_LBRC;
        open_curly = KC_LCBR;
    }
    switch (state->count) {
        case 1:
            tap_code16(open_bracket);
            reset_tap_dance(state);
            break;
        case 2:
            tap_code(open_square);
            reset_tap_dance(state);
            break;
        case 3:
            tap_code16(open_curly);
            reset_tap_dance(state);
            break;
        default:
            break;
    }
}

void c_brkt_fn(tap_dance_state_t *state, void *user_data) {
    uint16_t close_bracket = UK_RPRN;
    uint16_t close_square = UK_RBRC;
    uint16_t close_curly = UK_RCBR;
    if (default_layer_state == QWERTY_US_MASK) {
        close_bracket = KC_RPRN;
        close_square = KC_RBRC;
        close_curly = KC_RCBR;
    }
    switch (state->count) {
        case 1:
            tap_code16(close_bracket);
            reset_tap_dance(state);
            break;
        case 2:
            tap_code(close_square);
            reset_tap_dance(state);
            break;
        case 3:
            tap_code16(close_curly);
            reset_tap_dance(state);
            break;
        default:
            break;
    }
}

#define TAP_DOUBLE_TAP_FN(tap_key, dtap_key) \
    uint16_t stap_code = UK_##tap_key;    \
    uint16_t dtap_code = UK_##dtap_key;  \
    if (default_layer_state == QWERTY_US_MASK) { \
        stap_code = KC_##tap_key; \
        dtap_code = KC_##dtap_key; \
    } \
    switch (state->count) { \
        case 1: \
            tap_code16(stap_code); \
            reset_tap_dance(state); \
            break; \
        case 2: \
            tap_code(dtap_code); \
            reset_tap_dance(state); \
            break; \
        default: \
            break; \
    }

void slash_backslash_fn(tap_dance_state_t *state, void *user_data) {
    TAP_DOUBLE_TAP_FN(SLSH, BSLS);
}

// Define ACTION_TAP_DANCE_FN_ADVANCED for each tapdance keycode, passing in finished and reset functions
tap_dance_action_t tap_dance_actions[] = {
    [CTL_QUOTE_DQUO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_quote_dquo_finished, ctl_quote_dquo_reset),
    [O_BRKT] = ACTION_TAP_DANCE_FN(o_brkt_fn),
    [C_BRKT] = ACTION_TAP_DANCE_FN(c_brkt_fn),
    [SLASH_BACKSLASH] = ACTION_TAP_DANCE_FN(slash_backslash_fn),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY_UK:
                oled_write_P(PSTR("QWERTY UK\n"), false);
                break;
            case _QWERTY_US:
                oled_write_P(PSTR("QWERTY US\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("GAMING\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM_UK:
            case _SYM_US:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION_UK:
            case _FUNCTION_US:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        if (rgblight_is_enabled()) {
            // RGB mode
            oled_write_P(PSTR("RGB mode: "), false);
            uint8_t mode = rgblight_get_mode();
            if (mode == RGBLIGHT_MODE_STATIC_LIGHT) {
                oled_write_P(PSTR("Static\n"), false);
            } else if (RGBLIGHT_MODE_BREATHING <= mode && mode <= RGBLIGHT_MODE_BREATHING + 3) {
                RGB_MODE_PRINTER(10, "Breathe %d", RGBLIGHT_MODE_BREATHING);
            } else if (RGBLIGHT_MODE_RAINBOW_MOOD <= mode && mode <= RGBLIGHT_MODE_RAINBOW_MOOD + 2) {
                RGB_MODE_PRINTER(10, "Rainbow %d", RGBLIGHT_MODE_RAINBOW_MOOD);
            }
            else if (RGBLIGHT_MODE_RAINBOW_SWIRL <= mode && mode <= RGBLIGHT_MODE_RAINBOW_SWIRL + 5) {
                RGB_MODE_PRINTER(8, "Swirl %d", RGBLIGHT_MODE_RAINBOW_SWIRL);
            }
            else if (RGBLIGHT_MODE_SNAKE <= mode && mode <= RGBLIGHT_MODE_SNAKE + 5) {
                RGB_MODE_PRINTER(8, "Snake %d", RGBLIGHT_MODE_SNAKE);
            }
            else if (RGBLIGHT_MODE_KNIGHT <= mode && mode <= RGBLIGHT_MODE_KNIGHT + 2) {
                RGB_MODE_PRINTER(9, "Knight %d", RGBLIGHT_MODE_KNIGHT);
            }
            else if (mode == RGBLIGHT_MODE_CHRISTMAS) {
                    oled_write_P(PSTR("Christmas\n"), false);
            }
            else if (RGBLIGHT_MODE_STATIC_GRADIENT <= mode && mode <= RGBLIGHT_MODE_STATIC_GRADIENT + 9) {
                RGB_MODE_PRINTER(12, "Gradient %d", RGBLIGHT_MODE_STATIC_GRADIENT);
            }
            else if (RGBLIGHT_MODE_TWINKLE <= mode && mode <= RGBLIGHT_MODE_TWINKLE + 5) {
                RGB_MODE_PRINTER(10, "Twinkle %d", RGBLIGHT_MODE_TWINKLE);
            }
            else {
                oled_write_P(PSTR("Undefined\n"), false);
            }
        }

        oled_write_P(PSTR("Modifier: "), false);
        uint8_t mods = get_mods();
        uint8_t one_shot_mods = get_oneshot_mods();
        if (mods & MOD_MASK_GUI || one_shot_mods & MOD_MASK_GUI) {
            oled_write_P(PSTR("G"), false);
        }
        if (mods & MOD_MASK_ALT || one_shot_mods & MOD_MASK_ALT) {
            oled_write_P(PSTR("A"), false);
        }
        if (mods & MOD_MASK_CTRL || one_shot_mods & MOD_MASK_CTRL) {
            oled_write_P(PSTR("C"), false);
        }
        if (mods & MOD_MASK_SHIFT || one_shot_mods & MOD_MASK_SHIFT) {
            oled_write_P(PSTR("S"), false);
        }
        oled_write_P(PSTR("\n"), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    bool left  = index == 0;
    bool right = index == 1;

    // Base layer
    if (IS_LAYER_ON(_QWERTY_UK) || IS_LAYER_ON(_QWERTY_US) || IS_LAYER_ON(_GAMING)) {
        if (left) {
            if (clockwise) {
                tap_code(KC_MS_WH_DOWN);
            } else {
                tap_code(KC_MS_WH_UP);
            }
        } else if (right) {
            if (clockwise) {
                tap_code(KC_MS_WH_LEFT);
            } else {
                tap_code(KC_MS_WH_RIGHT);
            }
        }
    } else if (IS_LAYER_ON(_NAV)) {
        if (left) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (right) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    return false;
}
#endif
