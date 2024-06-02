#ifndef INPUT_STREAM
#define INPUT_STREAM

#include <queue>
#include "../utility/enums.h"

class InputStream {
    std::queue<Input> theStream;
    bool noAssign = true;

public:
    InputStream &operator<<(const Input&);

    InputStream &operator>>(Input&);

    operator bool() const;
};

extern InputStream iStream;

#endif
