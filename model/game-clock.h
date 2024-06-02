#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H
#define CLOCK_SPEED 20

#include "../utility/subject.h"
#include "scene-manager.h"
#include "../controller/input-manager.h"

class GameClock : public Subject {
    InputManager *inputManager;
    bool running = false;

    void tick();

    void run();

public:
    GameClock(InputManager*);

    void start();

    void stop();
};

#endif
