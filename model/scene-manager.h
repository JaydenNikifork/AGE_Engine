#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <string>
#include "../utility/subject.h"
#include "../utility/observer.h"
#include "scene.h"
#include "../view/output-manager.h"

class Game;
class WinScene;
class LoseScene;

class SceneManager : public Subject, public Observer {
    Scene *currentScene;
    std::map<std::string, Scene*> scenes;
    OutputManager *outputManager;
    Game *game;
    WinScene *winScene;
    LoseScene *loseScene;

public:
    SceneManager(OutputManager *outputManager);

    void addScene(std::string, Scene*);

    void changeScene(std::string);

    void notify(Subject*) override;

    void stop();

    ~SceneManager();

    friend class Game;
};

#endif
