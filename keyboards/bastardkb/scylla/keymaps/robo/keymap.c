/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
#include "color.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_split_4x6_5(
    KC_CAPS_LOCK,  KC_1, KC_2, KC_3, KC_4, KC_5,			   KC_6, KC_7, KC_8,    KC_9,   KC_0,     KC_GRAVE,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,			            KC_Y, KC_U, KC_I,    KC_O,   KC_P,     KC_MINS,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,	                KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,  KC_QUOT,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B,                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_BSLS,
//-------------------------------------------------//-----------------------------------------------------------//
                        KC_LCTL, KC_BSPC, TT(2),		     TT(1),  KC_SPC, KC_RSFT,
                                 KC_DEL,  TT(3),             KC_RGUI, KC_ENT
  ),

  [1] = LAYOUT_split_4x6_5(
   KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,			    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______,   _______, KC_MINS, KC_LBRC, KC_RBRC, _______,			_______, KC_P7,   KC_P8,   KC_P9,   _______,  KC_PLUS,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, _______, LSFT(KC_MINS), KC_LPRN, KC_RPRN,  _______,	      _______, KC_P4,   KC_P5,   KC_P6,   KC_MINS,  KC_PIPE,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, _______, KC_EQL, LSFT(KC_LBRC), LSFT(KC_RBRC), _______,       _______, KC_P1,   KC_P2,   KC_P3,   KC_EQL,   KC_UNDS,
//---------------------------------------------------------//-----------------------------------------------------------//
                               _______, _______, _______,		    _______, _______, KC_P0,
                                        _______,  _______,       _______, _______
  ),

  [2] = LAYOUT_split_4x6_5(
    _______,  _______,   _______,   _______,   _______,   _______,			    _______,   _______,   _______,   _______,   _______,   _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, KC_HOME, KC_UP, KC_END, KC_ENT,			  _______, KC_BTN1, KC_MS_U,  KC_BTN2, _______, _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_U,	      _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______,  _______, _______, KC_WH_D,        _______, KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               _______, _______, _______,		    _______, _______, _______,
                                        _______,  _______,       _______, _______
  ),

  [3] = LAYOUT_split_4x6_5(
    _______,  _______,   _______,   _______,   _______,   _______,			    KC_ASDN,   KC_ASUP,   KC_ASRP,   _______,   _______,   _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, _______, _______, _______,			  RGB_TOG, RGB_VAD, RGB_VAI, _______,  _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______,    _______, _______, _______,	      KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______,  _______, _______, _______,        KC_VOLD, _______, _______, _______, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               _______, _______, _______,		    _______, _______, _______,
                                        _______,  _______,       _______, _______
  ),
};


#define CAPS_LOCK_COLOR HSV_MAGENTA
#define CAPS_LOCK_COLOR_LED_INDEX 0

const uint8_t PROGMEM layercolors[][3] = {
  [0] = {HSV_GREEN},
  [1] = {HSV_RED},
  [2] = {HSV_BLUE},
  [3] = {HSV_PINK},
};

RGB hsv_to_rgb_with_brightness(HSV hsv_in) {
    HSV hsv = {hsv_in.h, hsv_in.s, rgb_matrix_get_val()};
    RGB rgb = hsv_to_rgb(hsv);
    return rgb;
}

void set_caps_color(void) {
    if (IS_LAYER_ON(0) && host_keyboard_led_state().caps_lock) {
        HSV hsv = {CAPS_LOCK_COLOR};
        RGB rgb = hsv_to_rgb_with_brightness(hsv);
        rgb_matrix_set_color(CAPS_LOCK_COLOR_LED_INDEX, rgb.r, rgb.g, rgb.b);
    }
}

void set_layer_color(void) {
    uint8_t layer = biton32(layer_state);
    HSV hsv = {.h = pgm_read_byte(&layercolors[layer][0]), .s = pgm_read_byte(&layercolors[layer][1]), .v = rgb_matrix_get_val()};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Handle layer colors
    set_layer_color();

    // Handle caps lock toggle
    set_caps_color();

}
