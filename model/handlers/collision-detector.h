#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "detector.h"
#include "../game-object.h"

struct CollisionDetected {
    GameObject *other;
};

class CollisionDetector : public Detector<CollisionDetected> {
public:
    void detect() override;
};

#endif
