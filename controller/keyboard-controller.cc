#include <curses.h>
#include <iostream>
#include "input-stream.h"
#include "keyboard-controller.h"
#include "../view/output-stream.h"
#include <string>

Input KeyboardController::encode(char c) {
    return c;
}

KeyboardController::KeyboardController() {
    // cbreak();
    noecho();
    nodelay(stdscr, true);
}

void KeyboardController::scanForInputs() {
    char c = getch();
    // std::string myC = "Pressed: ";
    // if (c != ERR) {myC += c;
    // oStream << myC;}
    Input input;

    if (c != ERR) {
        input = encode(c);
        iStream << input;
    }
}
