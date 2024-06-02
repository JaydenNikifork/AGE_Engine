#include <ncurses.h>
#include <vector>
#include <string>
#include "terminal-view.h"
#include "output-stream.h"

TerminalView::TerminalView() {
    initscr();
    refresh();
    curs_set(0);
}

TerminalView::~TerminalView() {
    endwin();
}

void TerminalView::draw() {
    std::vector<std::vector<char>> playArea;
    oStream >> playArea;

    for (size_t y = 0; y < playArea.size(); ++y) {
        for (size_t x = 0; x < playArea[0].size(); ++x) {
            mvaddch(y, x, playArea[y][x]);
        }
    }

    addch('\n');
    for (auto const &ch : oStream.getStatus(0)) addch(ch);
    addch('\n');
    for (auto const &ch : oStream.getStatus(1)) addch(ch);
    addch('\n');
    for (auto const &ch : oStream.getStatus(2)) addch(ch);
    
    refresh();
}
