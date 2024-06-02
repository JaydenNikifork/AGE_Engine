#ifndef OBSERVER_H
#define OBSERVER_H

#include "subject.h"

class Observer {
public:
    virtual void notify(Subject *fromWho) = 0;
    virtual ~Observer() {}
};

#endif
