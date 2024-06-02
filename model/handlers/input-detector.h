#ifndef INPUT_DETECTOR_H
#define INPUT_DETECTOR_H

#include "detector.h"

struct InputDetected {
    Input input;
};

class InputDetector : public Detector<InputDetected> {
public:
    void detect() override;
};

#endif
