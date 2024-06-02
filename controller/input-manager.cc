#include "input-manager.h"

void InputManager::addInputController(InputController *ic) { inputControllers.push_back(ic); }

void InputManager::removeInputController(InputController *ic) {
    auto it = inputControllers.begin();

    while (it != inputControllers.end()) {
        if (*it == ic) {
            inputControllers.erase(it);
            return;
        }

        ++it;
    }
}

void InputManager::scanAllInputs() {
    for (auto &ic : inputControllers) {
        ic->scanForInputs();
    }
}

InputManager::~InputManager() {
    for (auto &ic : inputControllers) {
        removeInputController(ic);
    }
}
