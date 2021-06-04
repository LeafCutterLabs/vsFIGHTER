#include "vsfighter2.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

#if defined(SOCD_CLEANER_LRN_UDU) || defined(SOCD_CLEANER_LAST_INPUT_WINS)
static keypos_t keypos_up = {0, 0};
static keypos_t keypos_down = {1, 0};
static keypos_t keypos_left = {2, 0};
static keypos_t keypos_right = {3, 0};

static uint8_t pressed_up = 0;
static uint8_t pressed_down = 0;
static uint8_t pressed_left = 0;
static uint8_t pressed_right = 0;

#ifdef SOCD_CLEANER_LAST_INPUT_WINS
static uint8_t up_wins = 0;
static uint8_t left_wins = 0;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint8_t layer = layer_switch_get_layer(record->event.key);
	uint16_t key_up = keymap_key_to_keycode(layer, keypos_up);
	uint16_t key_down = keymap_key_to_keycode(layer, keypos_down);
	uint16_t key_left = keymap_key_to_keycode(layer, keypos_left);
	uint16_t key_right = keymap_key_to_keycode(layer, keypos_right);
	uint8_t layer_mask = (1 << layer);
#ifdef SOCD_CLEANER_LRN_UDU
	/*
	 * Left + Right = Neutral
	 * Up + Down = Up
	 */
	if (keycode == key_up) {
		if (record->event.pressed) {
			pressed_up |= layer_mask;
			if (pressed_down & layer_mask) {
				unregister_code(key_down);
				return true;
			}
		} else {
			pressed_up &= (~layer_mask);
			if (pressed_down & layer_mask) {
				register_code(key_down);
				return true;
			}
		}
	} else if (keycode == key_down) {
		if (record->event.pressed) {
			pressed_down |= layer_mask;
			if (pressed_up & layer_mask) {
				return false;
			}
		} else {
			pressed_down &= (~layer_mask);
			if (pressed_up & layer_mask) {
				return false;
			}
		}
	} else if (keycode == key_left) {
		if (record->event.pressed) {
			pressed_left |= layer_mask;
			if (pressed_right & layer_mask) {
				unregister_code(key_right);
				return false;
			}
		} else {
			pressed_left &= (~layer_mask);
			if (pressed_right & layer_mask) {
				register_code(key_right);
				return false;
			}
		}
	} else if (keycode == key_right) {
		if (record->event.pressed) {
			pressed_right |= layer_mask;
			if (pressed_left & layer_mask) {
				unregister_code(key_left);
				return false;
			}
		} else {
			pressed_right &= (~layer_mask);
			if (pressed_left & layer_mask) {
				register_code(key_left);
				return false;
			}
		}
	}
#else
	/* Last input wins */
	if (keycode == key_up) {
		if (record->event.pressed) {
			pressed_up |= layer_mask;
			if (pressed_down & layer_mask) {
				unregister_code(key_down);
				up_wins |= layer_mask;
			}
		} else {
			pressed_up &= (~layer_mask);
			if (pressed_down & layer_mask) {
				if (up_wins & layer_mask) {
					register_code(key_down);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_down) {
		if (record->event.pressed) {
			pressed_down |= layer_mask;
			if (pressed_up & layer_mask) {
				unregister_code(key_up);
				up_wins &= (~layer_mask);
			}
		} else {
			pressed_down &= (~layer_mask);
			if (pressed_up & layer_mask) {
				if (!(up_wins & layer_mask)) {
					register_code(key_up);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_left) {
		if (record->event.pressed) {
			pressed_left |= layer_mask;
			if (pressed_right & layer_mask) {
				unregister_code(key_right);
				left_wins |= layer_mask;
			}
		} else {
			pressed_left &= (~layer_mask);
			if (pressed_right & layer_mask) {
				if (left_wins & layer_mask) {
					register_code(key_right);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_right) {
		if (record->event.pressed) {
			pressed_right |= layer_mask;
			if (pressed_left & layer_mask) {
				unregister_code(key_left);
				left_wins &= (~layer_mask);
			}
		} else {
			pressed_right &= (~layer_mask);
			if (pressed_left & layer_mask) {
				if (!(left_wins & layer_mask)) {
					register_code(key_left);
				} else {
					return false;
				}
			}
		}
	}
#endif
	return true;
}
#endif
