#include "makro06.h"
//#include "oled.c"
#include "animation_frames.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		RGB_MOD, KC_1, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(1)
        ),

    [1] = LAYOUT(
        RGB_MOD, KC_2, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(2)
    ),

    [2] = LAYOUT(
        RGB_MOD, KC_3, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(3)
    ),

    [3] = LAYOUT(
        RGB_MOD, KC_4, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(0)
    ),
};



void keyboard_post_init_user(void) {
    /* stuff keyboard should do after boot */
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

#ifdef OLED_ENABLE
#define IDLE_FRAME_DURATION 200 // Idle animation iteration rate in ms

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;

bool tap_anim        = false;
bool tap_anim_toggle = false;


// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i=0; i<NUM_OLED_BYTES; i++) {
        uint8_t bit = i%8;
        uint8_t map_index = i/8;
        uint8_t _block_map = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#endif

static void render_anim(void) {
    // Idle animation
    void animation_phase(void) {
        if (!tap_anim) {
            current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
            uint8_t idx = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
            #ifdef USE_OLED_BITMAP_COMPRESSION
            oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);
            #else
            oled_write_raw_P(idle_frames[idx], NUM_OLED_BYTES);
            #endif
        }
    }

    // Idle behaviour
    if (get_current_wpm() != 000) {  // prevent sleep
        oled_on();
        if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {  // Turn off screen when timer threshold elapsed or reset time since last input
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

bool oled_task_user(void) {
    render_anim();
    oled_set_cursor(0, 14);

    uint8_t n = get_current_wpm();
    char wpm_counter[6];
    wpm_counter[5] = '\0';
    wpm_counter[4] = '0' + n % 10;
    wpm_counter[3] = '0' + (n /= 10) % 10;
    wpm_counter[2] = '0' + n / 10 ;
    wpm_counter[1] = '0';
    wpm_counter[0] = '>';
    oled_write_ln(wpm_counter, false);

    return false;
}
#endif

// Animate tap
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_ENABLE
    // Check if non-mod
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLASH)) {
        if (record->event.pressed) {
            // Display tap frames
            tap_anim_toggle = !tap_anim_toggle;
            #ifdef USE_OLED_BITMAP_COMPRESSION
            oled_write_compressed_P(tap_block_map[tap_anim_toggle], tap_frames[tap_anim_toggle]);
            #else
            oled_write_raw_P(tap_frames[tap_anim_toggle], NUM_OLED_BYTES);
            #endif
        }
    }
    #endif


    return true;
}
