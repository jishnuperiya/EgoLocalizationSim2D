#include <iostream>
#include "SimDisplay.h"
#include <memory>

constexpr int DISPLAY_WIDTH = 1024;
constexpr int DISPLAY_HEIGHT = 980;

int main(){

    auto simulatorDisplay = std::make_unique<SimDisplay>();
    simulatorDisplay->createRenderer("EgoLocalizationSim2D",DISPLAY_WIDTH,DISPLAY_HEIGHT);

    return 0;
}
