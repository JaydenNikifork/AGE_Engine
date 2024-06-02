#include "scene.h"
#include "../view/output-stream.h"
#include "scene-manager.h"

void Scene::spawn(GameObject *gameObject) {
    gameObjects.push_back(gameObject);

    for (auto &detector : detectors) {
        detector->attachGameObject(gameObject);
    }

    gameObject->scene = this;
    gameObject->spawned = true;
    gameObject->init();
}

void Scene::destroy(GameObject *gameObject) {
    auto it = begin();

    while (it != end()) {
        if (*it == gameObject) {
            gameObjects.erase(it);
            break;
        }

        ++it;
    }

    for (auto &detector : detectors) {
        detector->detachGameObject(gameObject);
    }

    gameObject->spawned = false;
}

void Scene::destroyFarObjects() {
    for (auto &go : *this) {
        if (go->x < 0 || go->x > WIDTH || go->y < 0 || go->y > WIDTH) {
            if (go->outOfBoundsTime >= 10) destroy(go);
            else ++go->outOfBoundsTime;
        } else {
            go->outOfBoundsTime = 0;
        }
    }
}

void Scene::updateGameObjects() {
    for (auto &gameObject : gameObjects) gameObject->update();
}

void Scene::runDetectors() {
    for (auto &detector : detectors) detector->detect();
}

void Scene::notify(Subject*) {
    updateGameObjects();
    runDetectors();
    
    oStream.clearPlayArea();
    for (auto &gameObject : *this) {
        oStream << gameObject;
    }

    notifyObservers();
}

void Scene::attachDetector(DetectorBase *detector) {
    detectors.push_back(detector);
}

void Scene::detachDetector(DetectorBase *detector) {
    auto it = detectors.begin();

    while (it != detectors.end()) {
        if (*it == detector) {
            detectors.erase(it);
            return;
        }

        ++it;
    }
}

void Scene::changeScene(std::string sceneName) {
    sceneManager->changeScene(sceneName);
}

void Scene::stop() { sceneManager->stop(); }
