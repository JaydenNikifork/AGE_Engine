#include <iostream>
#include "space-invaders.h"
#include "dino-run.h"
#include "game3.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) std::cout << "Please provide game argument" << std::endl;
    else {
        std::string game = argv[1];
        
        if (game == "spaceInvaders") runSpaceInvaders();
        else if (game == "dinoRun") runDinoRun();
        else if (game == "game3") runGame3();
    }
}
