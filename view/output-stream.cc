#include <iostream>
#include "output-stream.h"

OutputStream oStream{};

OutputStream::OutputStream():
    thePlayArea{std::vector<std::vector<char>>(HEIGHT+2, std::vector<char>(WIDTH+2, ' '))},
    depthGrid{std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, INT_MIN))} {}

void OutputStream::setStatus(int statusNum, std::string status) {
    statuses[statusNum] = status;
}
const std::string &OutputStream::getStatus(int statusNum) {
    return statuses[statusNum];
}

OutputStream &OutputStream::operator<<(GameObject *gameObject) {
    Sprite *sprite = gameObject->getComponent<Sprite>();
    if (!sprite) return *this;

    int x, y;
    for (auto &pix : sprite->getPixels()) {
        x = gameObject->x + pix.x;
        y = gameObject->y + pix.y;

        if (x < 0 || x >= WIDTH) continue;
        if (y < 0 || y >= HEIGHT) continue;
        
        if (gameObject->z < depthGrid[y][x]) continue;

        thePlayArea[y+1][x+1] = pix.c;
        depthGrid[y][x] = gameObject->z;
    }

    return *this;
};

// OutputStream &OutputStream::operator<<(std::string status) {
//     nextSet->status = status;
//     nextSet = nextSet->next;

//     return *this;
// }

OutputStream &OutputStream::operator>>(std::vector<std::vector<char>> &v) {
    for (int x = 1; x < WIDTH + 1; ++x) {
        thePlayArea[0][x] = '-';
        thePlayArea[HEIGHT+1][x] = '-';
    }
    for (int y = 1; y < HEIGHT + 1; ++y) {
        thePlayArea[y][0] = '|';
        thePlayArea[y][WIDTH+1] = '|';
    }
    thePlayArea[0][0] = '+';
    thePlayArea[HEIGHT + 1][0] = '+';
    thePlayArea[0][WIDTH + 1] = '+';
    thePlayArea[HEIGHT + 1][WIDTH + 1] = '+';
    v = thePlayArea;

    return *this;
}

// OutputStream &OutputStream::operator>>(std::string &status) {
//     status = nextGet->status;
//     nextGet = nextGet->next;

//     return *this;
// }

void OutputStream::clearPlayArea() {
    thePlayArea = std::vector<std::vector<char>>(HEIGHT+2, std::vector<char>(WIDTH+2, ' '));
    depthGrid = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, INT_MIN));
}
