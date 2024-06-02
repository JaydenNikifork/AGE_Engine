#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H

#include <vector>
#include <string>
#include "output-view.h"
#include "../utility/observer.h"

class OutputManager : public Observer {
    std::vector<OutputView*> views;

public:
    void addView(OutputView*);

    void removeView(OutputView*);

    void drawAll();

    void notify(Subject*) override;

    ~OutputManager();
};

#endif
