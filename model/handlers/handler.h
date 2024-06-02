#ifndef HANDLER_H
#define HANDLER_H

#include <typeinfo>
#include "detector.h"
#include "../game-object.h"

template<typename DetectedT>
class Handler {
public:
    virtual void onDetected(DetectedT) = 0;

    GameObject *getGameObject() {
        try {
            return dynamic_cast<GameObject*>(this);
        } catch (std::bad_cast&) {
            return nullptr;
        }
    }
};

#endif
