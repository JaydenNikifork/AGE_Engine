#include <iostream>
#include "input-stream.h"

InputStream iStream{};

InputStream &InputStream::operator<<(const Input &input) {
    if (!theStream.empty() && input == theStream.back()) return *this;
    theStream.push(input);
    noAssign = false;
    return *this;
}

InputStream &InputStream::operator>>(Input &input) {
    if (theStream.size() == 0) {
        noAssign = true;
        return *this;
    }
    
    input = theStream.front();
    theStream.pop();
    return *this;
}

InputStream::operator bool() const { return !noAssign; }
