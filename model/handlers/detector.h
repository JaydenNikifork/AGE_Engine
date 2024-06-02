#ifndef DETECTOR_H
#define DETECTOR_H

#include <vector>
#include <typeinfo>
#include <string>
#include "../../view/output-stream.h"
#include "../../utility/observer.h"
#include "handler.h"
#include "../game-object.h"

struct Detected {};

struct DetectorBase {
    virtual void detect() = 0;
    virtual void attachGameObject(GameObject*) = 0;
    virtual void detachGameObject(GameObject*) = 0;
};

template<typename DetectedT>
class Detector : public DetectorBase {
protected:
    std::vector<Handler<DetectedT>*> handlers;

public:
    void attachGameObject(GameObject *gameObject) {
        Handler<DetectedT> *handler = dynamic_cast<Handler<DetectedT>*>(gameObject);
        if (handler) handlers.push_back(handler);
    }

    void detachGameObject(GameObject *gameObject) {
        Handler<DetectedT> *handler = dynamic_cast<Handler<DetectedT>*>(gameObject);
        if (!handler) return;

        auto it = handlers.begin();

        while (it != handlers.end()) {
            if (*it == handler) {
                handlers.erase(it);
                break;
            }
            ++it;
        }
    }

    virtual ~Detector() {}
};

#endif
