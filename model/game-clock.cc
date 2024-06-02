#include <ctime>
#include <iostream>
#include "game-clock.h"
#include "../view/output-stream.h"
#include <string>

GameClock::GameClock(InputManager *inputManager): inputManager{inputManager} {}

void GameClock::tick() {
    notifyObservers();
}

void GameClock::run() {
    std::clock_t prev = std::clock();
    std::clock_t now;

    while (running) {
        inputManager->scanAllInputs();

        now = std::clock();

        if (1000.0 * (now - prev) / CLOCKS_PER_SEC >= 1000.0 / CLOCK_SPEED) {
            tick();
            prev = now;
        }
    }
}

void GameClock::start() {
    running = true;
    run();
}

void GameClock::stop() {
    running = false;
}
