#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include "game-object.h"
#include "../utility/observer.h"
#include "../utility/subject.h"
#include "handlers/detector.h"

class SceneManager;
class DetectorBase;

class Scene : public Subject, public Observer {
    std::vector<GameObject*> gameObjects;
    std::vector<DetectorBase*> detectors;
    SceneManager *sceneManager;

    void updateGameObjects();
    void runDetectors();

public:
    using iterator = std::vector<GameObject*>::iterator;
    iterator begin() { return gameObjects.begin(); }
    iterator end() { return gameObjects.end(); }

    void spawn(GameObject*);

    void destroy(GameObject*);

    void destroyFarObjects();

    void notify(Subject*) override;

    void attachDetector(DetectorBase*);

    void detachDetector(DetectorBase*);

    void changeScene(std::string);

    void stop();

    friend class SceneManager;
};

#endif
