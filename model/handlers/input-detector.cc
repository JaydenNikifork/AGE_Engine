#include <iostream>
#include "../../utility/enums.h"
#include "input-detector.h"
#include "../../controller/input-stream.h"

void InputDetector::detect() {
    Input input; 
    while (iStream >> input) {
        for (auto &handler : handlers) {
            handler->onDetected(InputDetected{input});
        }
    }
}
