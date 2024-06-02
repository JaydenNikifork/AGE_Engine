#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "collision-detector.h"
#include "handler.h"

class CollisionHandler : public Handler<CollisionDetected> {
    void onDetected(CollisionDetected collisionDetected) override { onCollision(collisionDetected.other); }

public:
    virtual void onCollision(GameObject*) {};
};

#endif
