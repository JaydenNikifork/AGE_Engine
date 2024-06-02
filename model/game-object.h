#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "../utility/observer.h"
#include "components/transform.h"

class Scene;

class GameObject : public Transform {
    Scene *scene = nullptr;
    int outOfBoundsTime = 0;
    
public:
    std::string tag;
    bool spawned = false;
    
    template<typename ComponentT>
    ComponentT *getComponent() {
        return dynamic_cast<ComponentT*>(this);
    };

    void spawn(GameObject*);

    void destroy(GameObject*);

    void changeScene(std::string);

    virtual void init() {}

    virtual void update() {}

    void stop();

    void win();

    void lose();

    virtual ~GameObject() {};

    friend class Scene;
};

#endif
