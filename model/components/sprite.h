#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

struct Pixel {
    int x, y;
    char c;
};

class Sprite {
    std::vector<std::vector<char>> theSprite;

public:
    void setBitMap(std::vector<std::vector<char>>);
    void setRect(int, int, char);
    void setChar(char);

    std::vector<Pixel> getPixels();
};

#endif
