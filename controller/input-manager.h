#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <vector>
#include "input-stream.h"
#include "input-controller.h"
#include "../utility/observer.h"

class InputManager {
    std::vector<InputController*> inputControllers;

public:
    void addInputController(InputController *ic);

    void removeInputController(InputController *ic);

    void scanAllInputs();

    ~InputManager();
};

#endif
