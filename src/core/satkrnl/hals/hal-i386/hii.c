#include "../include/tty.h"
#include "../include/irq.h"
#include "../include/hii.h"
#include "../include/port.h"

char kbdus[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/* Handles the keyboard interrupt */
void HALKeyboardHandler(RegisterContext *r) {
    unsigned char scancode;
    NEVER_REFERENCED(r);
    scancode = HALInputFromPort(0x60);

    if (scancode & 0x80) {
        // todo: ctrl, alt, del
    }
    else {
        TtyMgrPutCharacter(kbdus[scancode]);
    }
}
status HALInitializeHumanInteraction() {
    if (HALInitializeKeyboard() != SUCCESS) {
        TtyMgrLog(FAILED_NOTAVAL, "hii", "couldn't initialize keyboard!");
    }
    if (HALInitializeMouse() != SUCCESS) {
        TtyMgrLog(FAILED_NOTAVAL, "hii", "couldn't initialize mouse!");
    }
    return SUCCESS;
}
status HALInitializeKeyboard() {
    HALSetIRQHandler(1, HALKeyboardHandler);
    return SUCCESS;
}
status HALInitializeMouse() {
    return SUCCESS;
}