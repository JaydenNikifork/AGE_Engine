#include "game3.h"
#include "game.h"
#include <cmath>
#include "model/handlers/input-handler.h"
#include "model/handlers/collision-handler.h"
#include "controller/keyboard-controller.h"
#include "view/terminal-view.h"
#include "model/scene-boarder.h"
#include "model/game-object.h"
#include "view/output-stream.h"

enum BallState {
    FALLING,
    JUMPING
};

class Ball : public GameObject, public Sprite, public CollisionHandler {
    double dy;
    double speed;

    void init() {
        x = 34;
        y = -4;
        z = 0;
        dy = y;
        speed = 0;
        std::vector<std::vector<char>> bitmap{
            std::vector<char>{' ',' ','.','.','.','.','.','.',' ',' '},
            std::vector<char>{' ','.','.','.','.','.','.','.','.',' '},
            std::vector<char>{'.','.','.','.','.','.','.','.','.','.'},
            std::vector<char>{'.','.','.','.','.','.','.','.','.','.'},
            std::vector<char>{'.','.','.','.','.','.','.','.','.','.'},
            std::vector<char>{' ','.','.','.','.','.','.','.','.',' '},
            std::vector<char>{' ',' ','.','.','.','.','.','.',' ',' '}
        };
        
        setBitMap(bitmap);
    }

    void update() {
        speed += 0.2;
        dy += speed;
        y = std::round(dy);
    }

    void onCollision(GameObject *other) {
        if (other->tag == "floor") {
            speed = -1 * std::abs(speed) - 0.2;
        }
    }
};

class Floor : public GameObject, public Sprite, public CollisionHandler {
    void init() {
        tag = "floor";
        x = 30;
        y = 15;
        z = 0;
        setRect(4, 15, '#');
    }
};

class Stopper : public GameObject, public InputHandler {
    void onInput(Input) {
        stop();
    }
};

void runGame3() {
    Game game3{};

    SceneManager &sceneManager = game3.getSceneManager();
    InputManager &inputManager = game3.getInputManager();
    OutputManager &outputManager = game3.getOutputManager();
    
    TerminalView tv{};
    outputManager.addView(&tv);

    KeyboardController kbController{};
    inputManager.addInputController(&kbController);

    Scene playScene{};
    sceneManager.addScene("playScene", &playScene);

    CollisionDetector collisionDetector{};
    playScene.attachDetector(&collisionDetector);

    InputDetector id{};
    playScene.attachDetector(&id);
    
    Ball ball{};
    playScene.spawn(&ball);

    Floor floor{};
    playScene.spawn(&floor);

    Stopper stopper{};
    playScene.spawn(&stopper);

    sceneManager.changeScene("playScene");

    game3.start();
}
