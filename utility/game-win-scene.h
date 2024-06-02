#include <vector>
#include <string>
#include "../model/game-object.h"
#include "../model/components/sprite.h"
#include "../model/scene.h"

class WinText : public GameObject, public Sprite {
    int exitCd = 60;

    void init() {
        std::vector<std::string> text{
            " __     __          __          ___       _  ",
            " \\ \\   / /          \\ \\        / (_)     | | ",
            "  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __ | | ",
            "   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\| | ",
            "    | | (_) | |_| |    \\  /\\  /  | | | | |_| ",
            "    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_(_) "
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

class WinScene : public Scene {
    WinText winText{};
public:
    WinScene(): Scene{} {
        spawn(&winText);
    }
};
