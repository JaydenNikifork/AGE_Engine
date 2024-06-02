// #include <iostream>
#include "scene.h"
#include "game-object.h"
#include "../view/output-stream.h"

void GameObject::spawn(GameObject *gameObject) {
    if (scene != nullptr) {
        scene->spawn(gameObject);
    }
}

void GameObject::destroy(GameObject *gameObject) {
    if (scene != nullptr) {
        scene->destroy(gameObject);
    }
}

void GameObject::changeScene(std::string sceneName) {
    scene->changeScene(sceneName);
}

void GameObject::stop() { scene->stop(); }

void GameObject::win() { changeScene("winScene"); }
void GameObject::lose() { changeScene("loseScene"); }
