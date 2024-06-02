#include "scene-manager.h"
#include "../game.h"
#include "../utility/game-win-scene.h"
#include "../utility/game-lose-scene.h"

SceneManager::SceneManager(OutputManager *outputManager):
    outputManager{outputManager}, winScene{new WinScene{}}, loseScene{new LoseScene{}} {
    addScene("winScene", winScene);
    addScene("loseScene", loseScene);
}

SceneManager::~SceneManager() {
    delete winScene;
    delete loseScene;
}

void SceneManager::addScene(std::string sceneName, Scene *scene) {
    scenes[sceneName] = scene;
    scene->attach(outputManager);
    scene->sceneManager = this;
}

void SceneManager::changeScene(std::string sceneName) {
    if (scenes[sceneName]) {
        if (currentScene != nullptr) detach(currentScene);
        currentScene = scenes[sceneName];
        attach(currentScene);
    }
}

void SceneManager::stop() { game->stop(); }

void SceneManager::notify(Subject*) { notifyObservers(); } // might need to be changed
