#include <experimental/random>
#include <queue>
#include <string>
#include "dino-run.h"
#include "game.h"
#include "model/handlers/input-handler.h"
#include "model/handlers/collision-handler.h"
#include "controller/keyboard-controller.h"
#include "view/terminal-view.h"
#include "model/scene-boarder.h"
#include "model/game-object.h"
#include "view/output-stream.h"

enum DinoState {
    RUNNING,
    JUMPING,
    FALLING,
    DUCKING
};

class GroundTile : public GameObject, public Sprite {
    int moveSpeed = 2;

    void init() {
        int random = std::experimental::randint(1, 3);
        switch (random) {
            case 1: {
                setChar('T');
                break;
            }
            case 2: {
                setChar('E');
                break;
            }
            case 3: {
                setChar('7');
                break;
            }
        }

        y = 19;
        z = 2;
    }

    void update() {
        x -= moveSpeed;
        if (x < 0) x += 78;
    }
};

class Ground : public GameObject {
    std::vector<GroundTile*> tiles{};

    void init() {
        for (int i = 0; i < 78; ++i) {
            GroundTile *tile = new GroundTile{};
            tile->x = i;
            spawn(tile);
        }
    }

public:
    ~Ground() {
        for (auto &tile : tiles) delete tile;
    }
};

class Cloud : public GameObject, public Sprite {
    std::vector<std::vector<char>> cloud1{
        std::vector<char>{' ',' ',' ','_','_',' ',' ','_',' ',' '},
        std::vector<char>{' ','_','(',' ',' ',')','(',' ',')',' '},
        std::vector<char>{'(','_',' ',' ','_','_',' ',' ','_',')'},
        std::vector<char>{' ',' ','(','_',')','(','_','_',')',' '}
    };

    int moveSpeed = 1;

    void init() {
        int random = std::experimental::randint(1, 3);
        setBitMap(cloud1);

        x = 80;
        y = 1 + random;
        z = random;
        moveSpeed = (random % 2) + 1;
    }

    void update() {
        x -= moveSpeed;
    }
};

class Bird : public GameObject, public Sprite, public CollisionHandler {
    int moveSpeed = 3;
    int frameSpeed = 3, frameTimer = 0;
    std::vector<std::vector<char>> flying1{
        std::vector<char>{' ',' ',' ',' ',' ','_'},
        std::vector<char>{' ','_','_','_','/','/'},
        std::vector<char>{'<','O',' ',' ',' ',' '},
        std::vector<char>{' ','-','-','-','M',' '}
    };
    std::vector<std::vector<char>> flying2{
        std::vector<char>{' ',' ',' ',' ',' ',' '},
        std::vector<char>{' ','_','_','_','_',' '},
        std::vector<char>{'<','O',' ',' ','\\','\\'},
        std::vector<char>{' ','-','-','-','-','_'}
    };
    std::vector<std::vector<char>> *curFrame = &flying1;

    void init() {
        tag = "bird";
        setBitMap(*curFrame);
        x = 80;
        y = 13;
    }

    void update() {
        setBitMap(*curFrame);
        x -= moveSpeed;
        
        if (frameTimer >= frameSpeed) {
            if (*curFrame == flying1) curFrame = &flying2;
            else curFrame = &flying1;
            frameTimer = 0;
        } else {
            ++frameTimer;
        }
    }
};

class Wall : public GameObject, public Sprite, public CollisionHandler {
    int moveSpeed = 2;

    void init() {
        tag = "wall";
        setRect(4, 2, 'E');
        x = 80;
        y = 15;
    }

    void update() {
        x -= moveSpeed;
    }
};

class VFXSpawner : public GameObject {
    std::queue<Cloud*> clouds;
    Ground ground{};
    int cloudCd = 10, cloudTimer = 0;

    void init() {
        spawn(&ground);
    }

    void update() {
        if (cloudTimer >= 20) {
            cloudTimer = 0;
            Cloud *cloud = new Cloud{};
            spawn(cloud);
            clouds.push(cloud);
            cloudCd = std::experimental::randint(5, 15);
        } else {
            ++cloudTimer;
        }

        if (!clouds.empty() && clouds.front()->spawned == false) {
            delete clouds.front();
            clouds.pop();
        }
    }
};

class EnemySpawner : public GameObject {
    std::queue<Wall*> walls{};
    std::queue<Bird*> birds{};
    int obstacleCd = 20, obstacleTimer = 0;

    void update() {
        if (obstacleTimer >= 20) {
            obstacleTimer = 0;
            int random = std::experimental::randint(0, 1);
            if (random == 0) {
                Wall *wall = new Wall{};
                walls.push(wall);
                spawn(wall);
            } else {
                Bird *bird = new Bird{};
                birds.push(bird);
                spawn(bird);
            }
            obstacleCd = std::experimental::randint(15, 25);
        } else {
            ++obstacleTimer;
        }

        if (!walls.empty() && walls.front()->spawned == false) {
            delete walls.front();
            walls.pop();
        }

        if (!birds.empty() && birds.front()->spawned == false) {
            delete birds.front();
            birds.pop();
        }
    }
};

class Dino : public GameObject, public Sprite, public InputHandler, public CollisionHandler {
    std::vector<std::vector<char>> running1{
        std::vector<char>{' ','P',' '},
        std::vector<char>{' ','|',' '},
        std::vector<char>{' ','|',' '},
    };
    std::vector<std::vector<char>> running2{
        std::vector<char>{' ','P',' '},
        std::vector<char>{',','|','\''},
        std::vector<char>{' ','A',' '},
    };

    std::vector<std::vector<char>> jumping{
        std::vector<char>{' ','P',' '},
        std::vector<char>{'/','|','\\'},
        std::vector<char>{' ','A',' '},
    };

    std::vector<std::vector<char>> falling{
        std::vector<char>{'\\','P','/'},
        std::vector<char>{' ','|',' '},
        std::vector<char>{' ','A',' '},
    };

    std::vector<std::vector<char>> ducking{
        std::vector<char>{' ',' ',' '},
        std::vector<char>{' ','P',' '},
        std::vector<char>{' ','n',' '},
    };

    DinoState state = RUNNING;
    int jumpHeight = 10;
    int startY = 16;
    int duckLength = 14, duckTimer = 0;
    std::vector<std::vector<char>> *curFrame = &running1;
    int lives = 3;
    bool invincible = false;
    int invincibleTimer = 0;

    void init() {
        oStream.setStatus(1, "Lives: " + std::to_string(lives));
        setBitMap(*curFrame);

        x = 15;
        y = startY;
    }

    void update() {
        switch (state) {
            case RUNNING: {
                if (*curFrame == running1) curFrame = &running2;
                else curFrame = &running1;
                break;
            }
            case JUMPING: {
                curFrame = &jumping;
                if (y > startY - jumpHeight) {
                    --y;
                } else {
                    state = FALLING;
                }
                break;
            }
            case FALLING: {
                curFrame = &falling;
                if (y < startY) {
                    ++y;
                } else {
                    state = RUNNING;
                }
                break;
            }
            case DUCKING: {
                curFrame = &ducking;
                if (duckTimer >= duckLength) {
                    duckTimer = 0;
                    state = RUNNING;
                } else {
                    ++duckTimer;
                }
            }
        }

        if (invincibleTimer <= 0) {
            invincible = false;
        } else {
            --invincibleTimer;
        }

        setBitMap(*curFrame);
    }

    void onInput(Input c) {
        switch (c) {
            case ' ': {
                if (state == RUNNING || state == DUCKING) {
                    state = JUMPING;
                }
                break;
            }
            case 's': {
                if (state == JUMPING) {
                    state = FALLING;
                } else if (state == RUNNING || state == DUCKING) {
                    state = DUCKING;
                }
                break;
            }
        }
    }

    void onCollision(GameObject *other) {
        if ((other->tag == "bird" || other->tag == "wall") && !invincible) {
            if (lives == 0) {
                destroy(this);
                lose();
            } else {
                --lives;
            }
            invincible = true;
            invincibleTimer = 20;
        }
        oStream.setStatus(1, "Lives: " + std::to_string(lives));
    }
};

class ScoreKeeper : public GameObject {
    int score = 0;

    void init() {
        oStream.setStatus(0, "Score: 0");
    }

    void update() {
        ++score;
        oStream.setStatus(0, "Score: " + std::to_string(score));
    }
};

void runDinoRun() {
    Game dinoRun{};

    SceneManager &sceneManager = dinoRun.getSceneManager();
    InputManager &inputManager = dinoRun.getInputManager();
    OutputManager &outputManager = dinoRun.getOutputManager();
    
    TerminalView tv{};
    outputManager.addView(&tv);

    KeyboardController kbController{};
    inputManager.addInputController(&kbController);

    Scene playScene{};
    sceneManager.addScene("playScene", &playScene);

    SceneBoarder border{};
    playScene.spawn(&border);
    
    InputDetector inputDetector{};
    CollisionDetector collisionDetector{};
    playScene.attachDetector(&inputDetector);
    playScene.attachDetector(&collisionDetector);

    Dino player{};
    playScene.spawn(&player);

    EnemySpawner wallSpawner{};
    playScene.spawn(&wallSpawner);

    VFXSpawner vfxSpawner{};
    playScene.spawn(&vfxSpawner);

    ScoreKeeper score{};
    playScene.spawn(&score);

    sceneManager.changeScene("playScene");

    dinoRun.start();
}
