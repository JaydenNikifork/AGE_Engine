#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *observer) { observers.push_back(observer); }

void Subject::detach(Observer *observer) {
    auto it = observers.begin();

    while (it != observers.end()) {
        if (*it == observer) {
            observers.erase(it);
            return;
        } else {
            ++it;
        }
    }
}

void Subject::notifyObservers() {
    for (auto &o : observers) {
        o->notify(this);
    }
}
