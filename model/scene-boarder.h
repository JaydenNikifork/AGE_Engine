#ifndef SCENE_BOARDER_H
#define SCENE_BOARDER_H

#include <vector>
#include "game-object.h"
#include "handlers/collision-handler.h"

class SceneBoarder : public GameObject, public Sprite, public CollisionHandler {
    void init() {
        tag = "border";

        std::vector<std::vector<char>> bitmap(
            32, std::vector<char>(
                90, ' '
            )
        );

        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 90; ++x) {
                if (5 <= x && x <= 84 &&
                    5 <= y && y <= 26) {
                    continue;
                }

                bitmap[y][x] = 'X';
            }
        }

        setBitMap(bitmap);

        x = y = -5;
        z = 0;
    }
};

#endif
