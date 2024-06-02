#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "input-detector.h"
#include "handler.h"
#include "../../utility/enums.h"

class InputHandler : public Handler<InputDetected> {
    void onDetected(InputDetected inputDetected) override { onInput(inputDetected.input); }

public:
    virtual void onInput(Input input) {}
};

#endif
