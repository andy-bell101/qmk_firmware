// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

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
    _NAV,
    _SYM_UK,
    _SYM_US,
    _FUNCTION,
    _ADJUST,
};

// Aliases for readability
#define QWERTY_UK   DF(_QWERTY_UK)
#define QWERTY_US   DF(_QWERTY_US)
#define GAMING   DF(_GAMING)
#define QWERTY_UK_MASK (1 << _QWERTY_UK)
#define QWERTY_US_MASK (1 << _QWERTY_US)
#define GAMING_MASK (1 << _GAMING)

#define SYM_UK      MO(_SYM_UK)
#define SYM_US      MO(_SYM_US)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define LALT_ENT  MT(MOD_LALT, KC_ENT)
#define RALT_ENT  MT(MOD_RALT, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────────┬──────┬──────┬──────────────┬──────┬──────────┐     ┌──────────────┐   ┌───────────┐          ┌──────┬──────┬────────────────┬──────┬───┬──────┐
//    │      esc      │  1   │  2   │      3       │  4   │    5     │     │     lsft     │   │   rsft    │          │  6   │  7   │       8        │  9   │ 0 │  \   │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │      tab      │  q   │  w   │      e       │  r   │    t     │     │     lctl     │   │   rctl    │          │  y   │  u   │       i        │  o   │ p │ bspc │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │    CTL_ESC    │  a   │  s   │      d       │  f   │    g     │     │     lalt     │   │   ralt    │          │  h   │  j   │       k        │  l   │ ; │  '   │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┼───┼──────┤
//    │ OSM(MOD_LSFT) │  z   │  x   │      c       │  v   │    b     │  [  │     caps     │   │   FKEYS   │    ]     │  n   │  m   │       ,        │  .   │ / │  -   │
//    └───────────────┴──────┴──────┼──────────────┼──────┼──────────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┴───┴──────┘
//                                  │ OSL(_ADJUST) │ lgui │ LALT_ENT │ spc │ OSL(_SYM_UK) │   │ OSL(_NAV) │ RALT_ENT │  `   │  =   │ OSL(_FUNCTION) │
//    ┌───────────────┬──────┬──────┼──────────────┼──────┼──────────┼─────┴──────────────┘   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┐
//    │     mprv      │ mnxt │ mply │     mstp     │      │   mute   │                        │   mprv    │   mnxt   │ mply │ mstp │                │ mute │
//    └───────────────┴──────┴──────┴──────────────┘      └──────────┘                        └───────────┴──────────┴──────┴──────┘                └──────┘
[_QWERTY_UK] = LAYOUT_myr(
  KC_ESC        , UK_1    , UK_2    , UK_3         , UK_4    , UK_5     ,           KC_LSFT      ,     KC_RSFT   ,            UK_6    , UK_7    , UK_8           , UK_9    , UK_0    , UK_BSLS,
  KC_TAB        , UK_Q    , UK_W    , UK_E         , UK_R    , UK_T     ,           KC_LCTL      ,     KC_RCTL   ,            UK_Y    , UK_U    , UK_I           , UK_O    , UK_P    , KC_BSPC,
  CTL_ESC       , UK_A    , UK_S    , UK_D         , UK_F    , UK_G     ,           KC_LALT      ,     KC_RALT   ,            UK_H    , UK_J    , UK_K           , UK_L    , UK_SCLN , UK_QUOT,
  OSM(MOD_LSFT) , UK_Z    , UK_X    , UK_C         , UK_V    , UK_B     , KC_LBRC , KC_CAPS      ,     FKEYS     , KC_RBRC  , UK_N    , UK_M    , UK_COMM        , UK_DOT  , UK_SLSH , UK_MINS,
                                      OSL(_ADJUST) , KC_LGUI , LALT_ENT , KC_SPC  , OSL(_SYM_UK) ,     OSL(_NAV) , RALT_ENT , UK_GRV  , UK_EQL  , OSL(_FUNCTION)                              ,
  KC_MPRV       , KC_MNXT , KC_MPLY , KC_MSTP      ,           KC_MUTE  ,                              KC_MPRV   , KC_MNXT  , KC_MPLY , KC_MSTP ,                  KC_MUTE
),

//    ┌───────────────┬──────┬──────┬──────────────┬──────┬──────────┐     ┌──────────────┐   ┌───────────┐          ┌──────┬──────┬────────────────┬──────┬───┬──────┐
//    │      esc      │  1   │  2   │      3       │  4   │    5     │     │     lsft     │   │   rsft    │          │  6   │  7   │       8        │  9   │ 0 │  \   │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │      tab      │  q   │  w   │      e       │  r   │    t     │     │     lctl     │   │   rctl    │          │  y   │  u   │       i        │  o   │ p │ bspc │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │    CTL_ESC    │  a   │  s   │      d       │  f   │    g     │     │     lalt     │   │   ralt    │          │  h   │  j   │       k        │  l   │ ; │  '   │
//    ├───────────────┼──────┼──────┼──────────────┼──────┼──────────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┼───┼──────┤
//    │ OSM(MOD_LSFT) │  z   │  x   │      c       │  v   │    b     │  [  │     caps     │   │   FKEYS   │    ]     │  n   │  m   │       ,        │  .   │ / │  -   │
//    └───────────────┴──────┴──────┼──────────────┼──────┼──────────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┴───┴──────┘
//                                  │ OSL(_ADJUST) │ lgui │ LALT_ENT │ spc │ OSL(_SYM_US) │   │ OSL(_NAV) │ RALT_ENT │  `   │  =   │ OSL(_FUNCTION) │
//    ┌───────────────┬──────┬──────┼──────────────┼──────┼──────────┼─────┴──────────────┘   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┐
//    │     mprv      │ mnxt │ mply │     mstp     │      │   mute   │                        │   mprv    │   mnxt   │ mply │ mstp │                │ mute │
//    └───────────────┴──────┴──────┴──────────────┘      └──────────┘                        └───────────┴──────────┴──────┴──────┘                └──────┘
[_QWERTY_US] = LAYOUT_myr(
  KC_ESC        , KC_1    , KC_2    , KC_3         , KC_4    , KC_5     ,           KC_LSFT      ,     KC_RSFT   ,            KC_6    , KC_7    , KC_8           , KC_9    , KC_0    , KC_BSLS,
  KC_TAB        , KC_Q    , KC_W    , KC_E         , KC_R    , KC_T     ,           KC_LCTL      ,     KC_RCTL   ,            KC_Y    , KC_U    , KC_I           , KC_O    , KC_P    , KC_BSPC,
  CTL_ESC       , KC_A    , KC_S    , KC_D         , KC_F    , KC_G     ,           KC_LALT      ,     KC_RALT   ,            KC_H    , KC_J    , KC_K           , KC_L    , KC_SCLN , KC_QUOT,
  OSM(MOD_LSFT) , KC_Z    , KC_X    , KC_C         , KC_V    , KC_B     , KC_LBRC , KC_CAPS      ,     FKEYS     , KC_RBRC  , KC_N    , KC_M    , KC_COMM        , KC_DOT  , KC_SLSH , KC_MINS,
                                      OSL(_ADJUST) , KC_LGUI , LALT_ENT , KC_SPC  , OSL(_SYM_US) ,     OSL(_NAV) , RALT_ENT , KC_GRV  , KC_EQL  , OSL(_FUNCTION)                              ,
  KC_MPRV       , KC_MNXT , KC_MPLY , KC_MSTP      ,           KC_MUTE  ,                              KC_MPRV   , KC_MNXT  , KC_MPLY , KC_MSTP ,                  KC_MUTE
),

//    ┌──────┬──────┬──────┬────────┬──────┬──────┐     ┌──────────────┐   ┌───────────┐          ┌──────┬──────┬────────────────┬──────┬───┬──────┐
//    │ esc  │  1   │  2   │   3    │  4   │  5   │     │     lsft     │   │   rsft    │          │  6   │  7   │       8        │  9   │ 0 │  \   │
//    ├──────┼──────┼──────┼────────┼──────┼──────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │ tab  │  t   │  q   │   w    │  e   │  r   │     │     lctl     │   │   rctl    │          │  y   │  u   │       i        │  o   │ p │ bspc │
//    ├──────┼──────┼──────┼────────┼──────┼──────┤     ├──────────────┤   ├───────────┤          ├──────┼──────┼────────────────┼──────┼───┼──────┤
//    │ lctl │  g   │  a   │   s    │  d   │  f   │     │     lalt     │   │   ralt    │          │  h   │  j   │       k        │  l   │ ; │  '   │
//    ├──────┼──────┼──────┼────────┼──────┼──────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┼───┼──────┤
//    │ lsft │  b   │  z   │   x    │  c   │  v   │  [  │     caps     │   │   FKEYS   │    ]     │  n   │  m   │       ,        │  .   │ / │  -   │
//    └──────┴──────┴──────┼────────┼──────┼──────┼─────┼──────────────┤   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┴───┴──────┘
//                         │ ADJUST │ lgui │ lalt │ spc │ OSL(_SYM_UK) │   │ OSL(_NAV) │ RALT_ENT │  `   │  =   │ OSL(_FUNCTION) │
//    ┌──────┬──────┬──────┼────────┼──────┼──────┼─────┴──────────────┘   ├───────────┼──────────┼──────┼──────┼────────────────┼──────┐
//    │ mprv │ mnxt │ mply │  mstp  │      │ mute │                        │   mprv    │   mnxt   │ mply │ mstp │                │ mute │
//    └──────┴──────┴──────┴────────┘      └──────┘                        └───────────┴──────────┴──────┴──────┘                └──────┘
[_GAMING] = LAYOUT_myr(
  KC_ESC  , UK_1    , UK_2    , UK_3    , UK_4    , UK_5    ,           KC_LSFT      ,     KC_RSFT   ,            UK_6    , UK_7    , UK_8           , UK_9    , UK_0    , UK_BSLS,
  KC_TAB  , UK_T    , UK_Q    , UK_W    , UK_E    , UK_R    ,           KC_LCTL      ,     KC_RCTL   ,            UK_Y    , UK_U    , UK_I           , UK_O    , UK_P    , KC_BSPC,
  KC_LCTL , UK_G    , UK_A    , UK_S    , UK_D    , UK_F    ,           KC_LALT      ,     KC_RALT   ,            UK_H    , UK_J    , UK_K           , UK_L    , UK_SCLN , UK_QUOT,
  KC_LSFT , UK_B    , UK_Z    , UK_X    , UK_C    , UK_V    , KC_LBRC , KC_CAPS      ,     FKEYS     , KC_RBRC  , UK_N    , UK_M    , UK_COMM        , UK_DOT  , UK_SLSH , UK_MINS,
                                ADJUST  , KC_LGUI , KC_LALT , KC_SPC  , OSL(_SYM_UK) ,     OSL(_NAV) , RALT_ENT , UK_GRV  , UK_EQL  , OSL(_FUNCTION)                              ,
  KC_MPRV , KC_MNXT , KC_MPLY , KC_MSTP ,           KC_MUTE ,                              KC_MPRV   , KC_MNXT  , KC_MPLY , KC_MSTP ,                  KC_MUTE
),

//    ┌─────┬──────┬──────┬──────┬──────┬─────┐     ┌──────┐   ┌─────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
//    │     │      │      │      │      │     │     │      │   │     │     │      │      │      │      │      │      │
//    ├─────┼──────┼──────┼──────┼──────┼─────┤     ├──────┤   ├─────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │      │      │      │      │     │     │      │   │     │     │ home │ pgdn │ pgup │ end  │ volu │ del  │
//    ├─────┼──────┼──────┼──────┼──────┼─────┤     ├──────┤   ├─────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │ lgui │ lalt │ lctl │ lsft │     │     │      │   │     │     │ left │ down │  up  │ rght │ vold │ ins  │
//    ├─────┼──────┼──────┼──────┼──────┼─────┼─────┼──────┤   ├─────┼─────┼──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │      │      │      │      │     │     │ sCRL │   │     │     │ paus │ mprv │ mply │ mnxt │ mute │ pscr │
//    └─────┴──────┴──────┼──────┼──────┼─────┼─────┼──────┤   ├─────┼─────┼──────┼──────┼──────┼──────┴──────┴──────┘
//                        │      │      │     │     │      │   │     │     │      │      │      │
//    ┌─────┬──────┬──────┼──────┼──────┼─────┼─────┴──────┘   ├─────┼─────┼──────┼──────┼──────┼──────┐
//    │     │      │      │      │      │     │                │     │     │      │      │      │      │
//    └─────┴──────┴──────┴──────┘      └─────┘                └─────┴─────┴──────┴──────┘      └──────┘
[_NAV] = LAYOUT_myr(
  _______ , _______ , _______ , _______ , _______ , _______ ,           _______ ,     _______ ,           _______  , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,           _______ ,     _______ ,           KC_HOME  , KC_PGDN , KC_PGUP , KC_END  , KC_VOLU , KC_DEL ,
  _______ , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,           _______ ,     _______ ,           KC_LEFT  , KC_DOWN , KC_UP   , KC_RGHT , KC_VOLD , KC_INS ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_SCRL ,     _______ , _______ , KC_PAUSE , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , KC_PSCR,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______  , _______ , _______                              ,
  _______ , _______ , _______ , _______ ,           _______ ,                         _______ , _______ , _______  , _______ ,           _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┐   ┌─────┐     ┌─────┬─────┬─────┬─────┬───┬───┐
//    │  `  │  1  │  2  │  3  │  4  │  5  │     │     │   │     │     │  6  │  7  │  8  │  9  │ 0 │ = │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼─────┼─────┼─────┼───┼───┤
//    │  `  │  1  │  2  │  3  │  4  │  5  │     │     │   │     │     │  6  │  7  │  8  │  9  │ 0 │ = │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼─────┼─────┼─────┼───┼───┤
//    │  ~  │  !  │  @  │  #  │  $  │  %  │     │     │   │     │     │  ^  │  &  │  *  │  (  │ ) │ + │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼───┼───┤
//    │  |  │  \  │  :  │  ;  │  -  │  [  │  {  │     │   │     │  }  │  ]  │  _  │  ,  │  .  │ / │ ? │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴───┴───┘
//                      │     │     │     │     │     │   │     │     │     │     │     │
//    ┌─────┬─────┬─────┼─────┼─────┼─────┼─────┴─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┐
//    │     │     │     │     │     │     │               │     │     │     │     │     │     │
//    └─────┴─────┴─────┴─────┘     └─────┘               └─────┴─────┴─────┴─────┘     └─────┘
[_SYM_UK] = LAYOUT_myr(
  UK_GRV  , UK_1    , UK_2    , UK_3    , UK_4    , UK_5    ,           _______ ,     _______ ,           UK_6    , UK_7    , UK_8    , UK_9    , UK_0    , UK_EQL ,
  UK_GRV  , UK_1    , UK_2    , UK_3    , UK_4    , UK_5    ,           _______ ,     _______ ,           UK_6    , UK_7    , UK_8    , UK_9    , UK_0    , UK_EQL ,
  UK_TILD , UK_EXLM , UK_AT   , UK_HASH , UK_DLR  , UK_PERC ,           _______ ,     _______ ,           UK_CIRC , UK_AMPR , UK_ASTR , UK_LPRN , UK_RPRN , UK_PLUS,
  UK_PIPE , UK_BSLS , UK_COLN , UK_SCLN , UK_MINS , UK_LBRC , UK_LCBR , _______ ,     _______ , UK_RCBR , UK_RBRC , UK_UNDS , UK_COMM , UK_DOT  , UK_SLSH , UK_QUES,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                              ,
  _______ , _______ , _______ , _______ ,           _______ ,                         _______ , _______ , _______ , _______ ,           _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┐   ┌─────┐     ┌─────┬─────┬─────┬─────┬───┬───┐
//    │  `  │  1  │  2  │  3  │  4  │  5  │     │     │   │     │     │  6  │  7  │  8  │  9  │ 0 │ = │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼─────┼─────┼─────┼───┼───┤
//    │  `  │  1  │  2  │  3  │  4  │  5  │     │     │   │     │     │  6  │  7  │  8  │  9  │ 0 │ = │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼─────┼─────┼─────┼───┼───┤
//    │  ~  │  !  │  @  │  #  │  $  │  %  │     │     │   │     │     │  ^  │  &  │  *  │  (  │ ) │ + │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼───┼───┤
//    │  |  │  \  │  :  │  ;  │  -  │  [  │  {  │     │   │     │  }  │  ]  │  _  │  ,  │  .  │ / │ ? │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴───┴───┘
//                      │     │     │     │     │     │   │     │     │     │     │     │
//    ┌─────┬─────┬─────┼─────┼─────┼─────┼─────┴─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┐
//    │     │     │     │     │     │     │               │     │     │     │     │     │     │
//    └─────┴─────┴─────┴─────┘     └─────┘               └─────┴─────┴─────┴─────┘     └─────┘
[_SYM_US] = LAYOUT_myr(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,           _______ ,     _______ ,           KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_EQL ,
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,           _______ ,     _______ ,           KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_EQL ,
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,           _______ ,     _______ ,           KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PLUS,
  KC_PIPE , KC_BSLS , KC_COLN , KC_SCLN , KC_MINS , KC_LBRC , KC_LCBR , _______ ,     _______ , KC_RCBR , KC_RBRC , KC_UNDS , KC_COMM , KC_DOT  , KC_SLSH , KC_QUES,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                              ,
  _______ , _______ , _______ , _______ ,           _______ ,                         _______ , _______ , _______ , _______ ,           _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┐   ┌─────┐     ┌─────┬──────┬──────┬──────┬──────┬─────┐
//    │     │     │     │     │     │     │     │     │   │     │     │     │      │      │      │      │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │ f9  │ f10 │ f11 │ f12 │     │     │     │   │     │     │     │      │      │      │      │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │ f5  │ f6  │ f7  │ f8  │     │     │     │   │     │     │     │ rsft │ rctl │ lalt │ rgui │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──────┼──────┼──────┼──────┼─────┤
//    │     │ f1  │ f2  │ f3  │ f4  │     │     │     │   │     │     │     │      │      │      │      │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──────┼──────┼──────┴──────┴─────┘
//                      │     │     │     │     │     │   │     │     │     │      │      │
//    ┌─────┬─────┬─────┼─────┼─────┼─────┼─────┴─────┘   ├─────┼─────┼─────┼──────┼──────┼──────┐
//    │     │     │     │     │     │     │               │     │     │     │      │      │      │
//    └─────┴─────┴─────┴─────┘     └─────┘               └─────┴─────┴─────┴──────┘      └──────┘
[_FUNCTION] = LAYOUT_myr(
  _______ , _______ , _______ , _______ , _______ , _______ ,           _______ ,     _______ ,           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,           _______ ,     _______ ,           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , _______ ,           _______ ,     _______ ,           _______ , KC_RSFT , KC_RCTL , KC_LALT , KC_RGUI , _______,
  _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                              ,
  _______ , _______ , _______ , _______ ,           _______ ,                         _______ , _______ , _______ , _______ ,           _______
),

//    ┌─────┬─────┬─────┬───────────┬─────┬─────┐     ┌─────┐   ┌─────┐     ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────┐
//    │     │     │     │           │     │     │     │     │   │     │     │         │         │         │         │         │     │
//    ├─────┼─────┼─────┼───────────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────────┼─────────┼─────────┼─────────┼─────────┼─────┤
//    │     │     │     │ QWERTY_UK │     │     │     │     │   │     │     │         │         │         │         │         │     │
//    ├─────┼─────┼─────┼───────────┼─────┼─────┤     ├─────┤   ├─────┤     ├─────────┼─────────┼─────────┼─────────┼─────────┼─────┤
//    │     │     │     │ QWERTY_US │     │     │     │     │   │     │     │ UG_TOGG │ UG_SATU │ UG_HUEU │ UG_VALU │ UG_NEXT │     │
//    ├─────┼─────┼─────┼───────────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┤
//    │     │     │     │  GAMING   │     │     │     │     │   │     │     │         │ UG_SATD │ UG_HUED │ UG_VALD │ UG_PREV │     │
//    └─────┴─────┴─────┼───────────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────┘
//                      │           │     │     │     │     │   │     │     │         │         │         │
//    ┌─────┬─────┬─────┼───────────┼─────┼─────┼─────┴─────┘   ├─────┼─────┼─────────┼─────────┼─────────┼─────────┐
//    │     │     │     │           │     │     │               │     │     │         │         │         │         │
//    └─────┴─────┴─────┴───────────┘     └─────┘               └─────┴─────┴─────────┴─────────┘         └─────────┘
[_ADJUST] = LAYOUT_myr(
  _______ , _______ , _______ , _______   , _______ , _______ ,           _______ ,     _______ ,           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , QWERTY_UK , _______ , _______ ,           _______ ,     _______ ,           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , QWERTY_US , _______ , _______ ,           _______ ,     _______ ,           UG_TOGG , UG_SATU , UG_HUEU , UG_VALU , UG_NEXT , _______,
  _______ , _______ , _______ , GAMING    , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , UG_SATD , UG_HUED , UG_VALD , UG_PREV , _______,
                                _______   , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                              ,
  _______ , _______ , _______ , _______   ,           _______ ,                         _______ , _______ , _______ , _______ ,           _______
)
};

// Override keys to match key caps
const key_override_t override_quote_key = ko_make_with_layers(MOD_MASK_SHIFT, UK_QUOT, UK_DQUO, QWERTY_UK_MASK);
const key_override_t override_2_key = ko_make_with_layers(MOD_MASK_SHIFT, UK_2, UK_AT, QWERTY_UK_MASK);
const key_override_t override_tick_key = ko_make_with_layers(MOD_MASK_SHIFT, UK_GRV, UK_TILD, QWERTY_UK_MASK);
const key_override_t *key_overrides[] = {
    &override_quote_key,
    &override_2_key,
    &override_tick_key,
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/elora/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Elora sigil
    // clang-format off
    static const char PROGMEM elora_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,224,240,248,120, 56, 60,188,158,158,222,206,207,207,207,239,239,239,239,239,239,207,207,207,206,222,158,158,188, 60, 56,120,248,240,224,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,248,252,126, 31,143,199,227,243,249,124, 60, 30, 31, 15,  7,  7,  3,  3,  3,131,193,225,241,249,253,255,255,255,255,127, 63, 31, 15,  7,  7,  7,143,223,254,252,252,249,243,227,199,143, 31,126,252,248,224,192,  0,  0,  0,  0,  0,
        0,192,240,254,255, 63,  7,227,248,252,127, 31, 15,  3,  1,  0,  0,  0,128,192,224,240,248,252,254,255,255,255,127, 63, 31, 15,  7,  3,  1,128,192,224,240,248,252,254,255,255,255,255,127, 63, 31, 15,  7, 15, 31,255,252,248,227,  7, 63,255,254,240,192,  0,252,255,255,255,  1,224,255,255,255,  7,  0,  0,  0,  0,  0,  0,  0,  0, 31, 31, 31, 31, 31, 15,  7,  3,  1,  0,  0,  0,240,248,252,254,255,255,255,255,127, 63, 31, 15,  7,  3,  1,128,192,224,240,248,252,254,255,255,255,255,255,255,224,  1,255,255,255,252,
        63,255,255,255,128,  7,255,255,255,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,248,248,248,248,248,248,  0,  3,  3,  3,  3,  3,  3,  1,128,192,224,240,248,252,254,255,255,255,127, 63, 31, 15,  7,  3,  1,224,255,255,255,  7,128,255,255,255, 63,  0,  3, 15,127,255,252,224,199, 31, 63,254,248,240,192,128,  0,  0,  0,  0, 31, 31, 31, 31, 31, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0, 62, 63, 63, 63, 63, 63, 31, 15,  7,  3,  1,  0,  0,  0,128,192,240,248,254, 63, 31,199,224,252,255,127, 15,  3,  0,
        0,  0,  0,  0,  0,  3,  7, 31, 63,126,248,241,227,199,207,159, 62, 60,120,248,240,224,224,192,192,192,192,128,128,128,128,128,128,128,128,128,128,192,192,192,192,224,224,240,248,120, 60, 62,159,207,199,227,241,248,126, 63, 31,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7,  7, 15, 31, 30, 28, 60, 61,121,121,123,115,243,243,243,247,247,247,247,247,247,243,243,243,115,123,121,121, 61, 60, 28, 30, 31, 15,  7,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    // clang-format on
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Lay: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY_UK:
                oled_write_P(PSTR("UK\n"), false);
                break;
            case _QWERTY_US:
                oled_write_P(PSTR("US\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("Game\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM_UK:
            case _SYM_US:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Fun\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adj\n"), false);
                break;
            default:
                oled_write_P(PSTR("???\n"), false);
        }

        oled_write_P(PSTR("Mod: "), false);
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

        // RGB mode
        oled_write_P(PSTR("LED: "), false);
        if (!rgblight_is_enabled()) {
            oled_write_P(PSTR("Off\n"), false);
        } else {
            uint8_t mode = rgblight_get_mode();
            if (mode == RGBLIGHT_MODE_STATIC_LIGHT) {
                oled_write_P(PSTR("Stat\n"), false);
            } else if (RGBLIGHT_MODE_BREATHING <= mode && mode <= RGBLIGHT_MODE_BREATHING + 3) {
                RGB_MODE_PRINTER(6, "Air %d", RGBLIGHT_MODE_BREATHING);
            } else if (RGBLIGHT_MODE_RAINBOW_MOOD <= mode && mode <= RGBLIGHT_MODE_RAINBOW_MOOD + 2) {
                RGB_MODE_PRINTER(6, "Rai %d", RGBLIGHT_MODE_RAINBOW_MOOD);
            }
            else if (RGBLIGHT_MODE_RAINBOW_SWIRL <= mode && mode <= RGBLIGHT_MODE_RAINBOW_SWIRL + 5) {
                RGB_MODE_PRINTER(6, "Swi %d", RGBLIGHT_MODE_RAINBOW_SWIRL);
            }
            else if (RGBLIGHT_MODE_SNAKE <= mode && mode <= RGBLIGHT_MODE_SNAKE + 5) {
                RGB_MODE_PRINTER(6, "Sna %d", RGBLIGHT_MODE_SNAKE);
            }
            else if (RGBLIGHT_MODE_KNIGHT <= mode && mode <= RGBLIGHT_MODE_KNIGHT + 2) {
                RGB_MODE_PRINTER(6, "Kni %d", RGBLIGHT_MODE_KNIGHT);
            }
            else if (mode == RGBLIGHT_MODE_CHRISTMAS) {
                    oled_write_P(PSTR("Chris\n"), false);
            }
            else if (RGBLIGHT_MODE_STATIC_GRADIENT <= mode && mode <= RGBLIGHT_MODE_STATIC_GRADIENT + 9) {
                RGB_MODE_PRINTER(6, "Gra %d", RGBLIGHT_MODE_STATIC_GRADIENT);
            }
            else if (RGBLIGHT_MODE_TWINKLE <= mode && mode <= RGBLIGHT_MODE_TWINKLE + 5) {
                RGB_MODE_PRINTER(6, "Twi %d", RGBLIGHT_MODE_TWINKLE);
            }
            else {
                oled_write_P(PSTR("???\n"), false);
            }
        }
        oled_set_cursor(0, (oled_max_lines() - 10));
        oled_write_raw_P(elora_logo, sizeof(elora_logo));
    } else {
        oled_set_cursor(0, (oled_max_lines()/2)-4); // logo is 8 lines high, so center vertically
        oled_write_raw_P(elora_logo, sizeof(elora_logo));
    }
    return false;
}
#endif

/* #ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  // Your code goes here
}
#endif */
