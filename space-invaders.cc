#include <vector>
#include <iostream>
#include <experimental/random>
#include "space-invaders.h"
#include "game.h"
#include "model/handlers/input-handler.h"
#include "model/handlers/collision-handler.h"
#include "model/components/sprite.h"
#include "controller/keyboard-controller.h"
#include "view/terminal-view.h"
#include "view/output-stream.h"
#include "model/scene-boarder.h"

int score = 0;
class EnemyBullet : public GameObject, public Sprite, public CollisionHandler {
    void init() {
        setChar('|');
        tag = "enemyBullet";
    }

    void update() override {
        ++y;
    }

    void onInput(Input c) {}

    void onCollision(GameObject *other) {
        if (other->tag == "player" || other->tag == "playerBullet")
            destroy(this);
    }
};

class Enemy : public GameObject, public Sprite, public CollisionHandler {
public:
    int scaledY;

private:
    void init() override {
        setBitMap(std::vector<std::vector<char>>{
            std::vector<char>{' ', '|', '_', '|', ' '},
            std::vector<char>{' ', '|', ' ', '|', ' '},
            std::vector<char>{'[', '|', ' ', '|', ']'}
        });
        tag = "enemy";
        oStream.setStatus(0, "Score: " + std::to_string(score));
    }

    void update() override {
        ++scaledY;
        y = scaledY / 40;

        int random = std::experimental::randint(0, 150);
        if (random == 0) {
            EnemyBullet *eb = new EnemyBullet();
            eb->x = x + 2;
            eb->y = y + 3;
            spawn(eb);
        }
    }

    void onCollision(GameObject *other) {
        if (other->tag == "playerBullet") {
            ++score;
            oStream.setStatus(0, "Score: " + std::to_string(score));
            destroy(this);
            if (score == 16) {
                win();
            }
        }
        else if (other->tag == "border") {
            changeScene("loseScene");
        }
    }
};

class PlayerBullet : public GameObject, public Sprite, public CollisionHandler {
    void init() {
        setChar('|');
        tag = "playerBullet";
    }

    void update() override {
        --y;
    }

    void onInput(Input c) {}

    void onCollision(GameObject *other) {
        if (other->tag == "enemy" || other->tag == "enemyBullet")
            destroy(this);
    }
};

class Player : public GameObject, public Sprite, public InputHandler, public CollisionHandler {
    int fireCd = 0;
    int prevX = 0;
    int moveSpeed = 10;
    int lives = 3;
    int deathCd = 20;

    void init() override {
        setBitMap(std::vector<std::vector<char>>{
            std::vector<char>{' ', ' ', '_', ' ', ' '},
            std::vector<char>{' ', '|', '_', '|', ' '},
            std::vector<char>{'[', '_', '_', '_', ']'}
        });

        tag = "player";

        y = 16;
        x = 32;
        z = 0;
    }

    void update() {
        if (fireCd != 0) --fireCd;
        
        if (lives == 0) --deathCd;

        if (deathCd <= 0) lose();

        oStream.setStatus(1, "Lives: " + std::to_string(lives));
    }

    void onInput(Input c) override {
        prevX = x;
        if (c == 'a') x -= moveSpeed;
        else if (c == 'd') x += moveSpeed;
        else if (c == ' ' && fireCd <= 0) {
            PlayerBullet *pb = new PlayerBullet{};
            pb->x = x + 2;
            pb->y = y - 1;
            spawn(pb);
            fireCd = 2;
        }
    }

    void onCollision(GameObject *other) {
        if (other->tag == "enemy" || other->tag == "enemyBullet") {
            --lives;
            if (lives == 0) {
                // destroy(this);
                setChar(' ');
            }
        } else if (other->tag == "border") {
            x = prevX;
        }
    }
};

void runSpaceInvaders() {
    Game spaceInvaders{};

    Scene gameScene{};

    SceneManager &sceneManager = spaceInvaders.getSceneManager();
    OutputManager &outputManager = spaceInvaders.getOutputManager();
    InputManager &inputManager = spaceInvaders.getInputManager();
    
    TerminalView tv{};
    outputManager.addView(&tv);

    KeyboardController kc{};
    inputManager.addInputController(&kc);


    InputDetector inputDetector{};
    CollisionDetector collisionDetector{};
    gameScene.attachDetector(&inputDetector);
    gameScene.attachDetector(&collisionDetector);

    sceneManager.addScene("gameScene", &gameScene);
    sceneManager.changeScene("gameScene");

    SceneBoarder sceneBoarder{};
    gameScene.spawn(&sceneBoarder);

    Player player{};
    gameScene.spawn(&player);

    int numEnemies = 16;
    std::vector<Enemy> enemies(numEnemies, Enemy{});

    for (int i = 0; i < numEnemies; ++i) {
        enemies[i].x = (i % 8) * 10 + 2;
        enemies[i].y = (i / 8) * 5 + 1;
        enemies[i].scaledY = enemies[i].y * 40;
        gameScene.spawn(&enemies[i]);
    }

    spaceInvaders.start();
}
