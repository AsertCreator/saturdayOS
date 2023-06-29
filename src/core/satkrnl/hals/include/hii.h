#pragma once
#include "../../include/system.h"

extern char kbdus[];

void HALKeyboardHandler(RegisterContext* r);
status HALInitializeHumanInteraction();
status HALInitializeKeyboard();
status HALInitializeMouse();