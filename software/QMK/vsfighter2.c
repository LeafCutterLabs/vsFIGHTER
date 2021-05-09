#include "vsfighter2.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

#if defined(SOCD_CLEANER_LRN_UDU) || defined(SOCD_CLEANER_LAST_INPUT_WINS)
static uint16_t key_up;
static uint16_t key_down;
static uint16_t key_left;
static uint16_t key_right;

static bool pressed_up = false;
static bool pressed_down = false;
static bool pressed_left = false;
static bool pressed_right = false;

#ifdef SOCD_CLEANER_LAST_INPUT_WINS
static bool up_wins = false;
static bool left_wins = false;
#endif

void keyboard_post_init_user(void) {
	/*
	 * Read keymap from progmem after initialization. Only supports one layer.
	 * TODO: Figure out how to work with dynamic keymaps (VIA)
	 */
	key_up = pgm_read_word(&keymaps[0][0][0]);
	key_down = pgm_read_word(&keymaps[0][0][1]);
	key_left = pgm_read_word(&keymaps[0][0][2]);
	key_right = pgm_read_word(&keymaps[0][0][3]);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef SOCD_CLEANER_LRN_UDU
	/*
	 * Left + Right = Neutral
	 * Up + Down = Up
	 */
	if (keycode == key_up) {
		if (record->event.pressed) {
			pressed_up = true;
			if (pressed_down) {
				unregister_code(key_down);
				return true;
			}
		} else {
			pressed_up = false;
			if (pressed_down) {
				register_code(key_down);
				return true;
			}
		}
	} else if (keycode == key_down) {
		if (record->event.pressed) {
			pressed_down = true;
			if (pressed_up) {
				return false;
			}
		} else {
			pressed_down = false;
			if (pressed_up) {
				return false;
			}
		}
	} else if (keycode == key_left) {
		if (record->event.pressed) {
			pressed_left = true;
			if (pressed_right) {
				unregister_code(key_right);
				return false;
			}
		} else {
			pressed_left = false;
			if (pressed_right) {
				register_code(key_right);
				return false;
			}
		}
	} else if (keycode == key_right) {
		if (record->event.pressed) {
			pressed_right = true;
			if (pressed_left) {
				unregister_code(key_left);
				return false;
			}
		} else {
			pressed_right = false;
			if (pressed_left) {
				register_code(key_left);
				return false;
			}
		}
	}
#else
	/* Last input wins */
	if (keycode == key_up) {
		if (record->event.pressed) {
			pressed_up = true;
			if (pressed_down) {
				unregister_code(key_down);
				up_wins = true;
			}
		} else {
			pressed_up = false;
			if (pressed_down) {
				if (up_wins) {
					register_code(key_down);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_down) {
		if (record->event.pressed) {
			pressed_down = true;
			if (pressed_up) {
				unregister_code(key_up);
				up_wins = false;
			}
		} else {
			pressed_down = false;
			if (pressed_up) {
				if (!up_wins) {
					register_code(key_up);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_left) {
		if (record->event.pressed) {
			pressed_left = true;
			if (pressed_right) {
				unregister_code(key_right);
				left_wins = true;
			}
		} else {
			pressed_left = false;
			if (pressed_right) {
				if (left_wins) {
					register_code(key_right);
				} else {
					return false;
				}
			}
		}
	} else if (keycode == key_right) {
		if (record->event.pressed) {
			pressed_right = true;
			if (pressed_left) {
				unregister_code(key_left);
				left_wins = false;
			}
		} else {
			pressed_right = false;
			if (pressed_left) {
				if (!left_wins) {
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
