#include <cctype>
#include "sprite.h"

void Sprite::setBitMap(std::vector<std::vector<char>> bm) { theSprite = bm; }

void Sprite::setRect(int h, int w, char c) {
    theSprite = std::vector<std::vector<char>>(h, std::vector<char>(w, c));
}

void Sprite::setChar(char c) { theSprite = std::vector<std::vector<char>>{std::vector<char>{c}}; }

std::vector<Pixel> Sprite::getPixels() {
    std::vector<Pixel> pixels;
    int x = 0, y = 0;

    for (auto &row : theSprite) {
        x = 0;
        for (auto &c : row) {
            if (!isspace(c)) pixels.push_back(Pixel{x, y, c});
            ++x;
        }
        ++y;
    }

    return pixels;
}
