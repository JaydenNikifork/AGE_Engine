#include "output-manager.h"
#include "output-stream.h"

void OutputManager::addView(OutputView *view) { views.push_back(view); }

void OutputManager::removeView(OutputView *view) {
    auto it = views.begin();

    while (it != views.end()) {
        if (*it == view) {
            views.erase(it);
            return;
        }

        ++it;
    }
}

void OutputManager::drawAll() {
    for (auto &viewP : views) {
        viewP->draw();
    }
}

void OutputManager::notify(Subject*) {
    drawAll();
}

OutputManager::~OutputManager() {
    for (auto &view : views) {
        removeView(view);
    }
}
