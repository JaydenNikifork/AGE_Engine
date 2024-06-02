#ifndef TERMINAL_VIEW
#define TERMINAL_VIEW

#include <ncurses.h>
#include "output-view.h"

class TerminalView : public OutputView {
public:
    TerminalView();

    ~TerminalView();

    void draw() override;
};

#endif
