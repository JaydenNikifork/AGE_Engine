#ifndef OUTPUT_STREAM_H
#define OUTPUT_STREAM_H
#define WIDTH 78
#define HEIGHT 20

#include <vector>
#include <queue>
#include <string>
#include <climits>
#include "../model/components/sprite.h"
#include "../model/game-object.h"

class OutputStream {
    std::vector<std::vector<char>> thePlayArea;
    std::vector<std::vector<int>> depthGrid;
    std::vector<std::string> statuses{3, std::string{}};

public:
    OutputStream();

    OutputStream &operator<<(GameObject*);

    // OutputStream &operator<<(std::string);
    void setStatus(int, std::string);

    OutputStream &operator>>(std::vector<std::vector<char>>&);

    // OutputStream &operator>>(std::string&);
    const std::string &getStatus(int);

    void clearPlayArea();
};

extern OutputStream oStream;

#endif
