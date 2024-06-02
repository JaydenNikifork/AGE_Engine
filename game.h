#ifndef GAME_H
#define GAME_H

#include "controller/input-manager.h"
#include "model/game-clock.h"
#include "model/scene-manager.h"
#include "view/output-manager.h"

class Game {
    InputManager *inputManager;
    OutputManager *outputManager;
    SceneManager *sceneManager;
    GameClock *gameClock;

public:
    Game():
        inputManager{new InputManager{}},
        outputManager{new OutputManager{}},
        sceneManager{new SceneManager{outputManager}},
        gameClock{new GameClock{inputManager}} {
        gameClock->attach(sceneManager);
        sceneManager->game = this;
    }

    ~Game() {
        delete inputManager;
        delete outputManager;
        delete sceneManager;
        delete gameClock;
    }

    InputManager &getInputManager() { return *inputManager; }
    OutputManager &getOutputManager() { return *outputManager; }
    SceneManager &getSceneManager() { return *sceneManager; }
    void start() { gameClock->start(); }
    void stop() { gameClock->stop(); }
};

#endif
