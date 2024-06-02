#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "input-controller.h"
#include "../utility/enums.h"

class KeyboardController : public InputController {
    Input encode(char c);

public:
    KeyboardController();

    void scanForInputs() override;
};

#endif
