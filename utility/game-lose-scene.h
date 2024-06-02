#include <vector>
#include <string>
#include "../model/game-object.h"
#include "../model/components/sprite.h"
#include "../model/scene.h"

class LoseText : public GameObject, public Sprite {
    int exitCd = 60;

    void init() {
        std::vector<std::string> text{
            " __     __           _                    ",
            " \\ \\   / /          | |                   ",
            "  \\ \\_/ /__  _   _  | |     ___  ___  ___ ",
            "   \\   / _ \\| | | | | |    / _ \\/ __|/ _ \\",
            "    | | (_) | |_| | | |___| (_) \\__ \\  __/",
            "    |_|\\___/ \\__,_| |______\\___/|___/\\___|"
        };
        
        std::vector<std::vector<char>> bitmap{};
        
        for (auto &row : text) {
            bitmap.push_back(std::vector<char>{});
            for (auto &ch : row) {
                bitmap.back().push_back(ch);
            }
        }

        setBitMap(bitmap);

        x = 16;
        y = 5;
    }

    void update() {
        --exitCd;
        if (exitCd <= 0) stop();
    }
};

class LoseScene : public Scene {
    LoseText loseText{};
public:
    LoseScene(): Scene{} {
        spawn(&loseText);
    }
};
