/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#pragma once

/*
 * Custom configuration for theRoboticist.
 * Because the adapter in their Scylla is a Charybdis 1.2 adapter, instead of
 * the Scylla 1.44 adapter, a few values need to be adjusted, namely:
 *   - SOFT_SERIAL_PIN
 *   - RGB_DI_PIN
 */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D2

#undef RGB_DI_PIN
#define RGB_DI_PIN D3

/* Regular configuration unrelated to the adapter. */

#ifdef VIA_ENABLE
/* VIA configuration. */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#ifdef VIAL_ENABLE
/** Vial configuration. */
#define VIAL_KEYBOARD_UID \
  { 0x5B, 0x76, 0x3F, 0xFF, 0xA8, 0x70, 0x33, 0xC8 }
#define VIAL_UNLOCK_COMBO_ROWS \
  { 0, 5 }
#define VIAL_UNLOCK_COMBO_COLS \
  { 0, 0 }

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#endif  // VIAL_ENABLE

/* Disable action features. */
#define NO_ACTION_MACRO     // Disable old-style macro handling.
#define NO_ACTION_FUNCTION  // Disable old-style function handling.
#endif                      // VIA_ENABLE
