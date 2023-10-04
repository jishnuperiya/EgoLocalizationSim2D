#include <iostream>
#include <memory>
#include "SimDisplay.h"
#include <SDL2/SDL_ttf.h>


bool initializeSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if(TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}


int main() {
    auto simulatorDisplay = std::make_unique<SimDisplay>();
    
    if(!initializeSDL()) {
        return -1;
    }
    
    simulatorDisplay->SDL_createRenderer("EgoLocalizationSim2D");
    
    bool mRunning = true;
    while(mRunning) {
        simulatorDisplay->clearScreen();
        simulatorDisplay->drawBackgroundMesh();
        simulatorDisplay->showScreen();
        //  missing some event handling to set mRunning to false.
        // Otherwise, the loop will run indefinitely.
    }

    simulatorDisplay->SDL_destroyRenderer();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
