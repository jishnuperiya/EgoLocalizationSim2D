#include <iostream>
#include <memory>
#include "SimDisplay.h"
#include <SDL2/SDL_ttf.h>

constexpr int DISPLAY_WIDTH = 1024;
constexpr int DISPLAY_HEIGHT = 980;
constexpr double MESH_SIZE = 500;
constexpr double MESH_SPACEING = 25;

// Split the SDL Initialization into a function for better organization
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

// Split the drawing code into a separate function
void drawBackgroundMesh(std::unique_ptr<SimDisplay>& display) {
    display->setDrawColour(101, 101, 101);
    for (int x = -MESH_SIZE; x <= MESH_SIZE; x += MESH_SPACEING) {
        display->drawLine(Vector2(x, -MESH_SIZE), Vector2(x, MESH_SIZE));
    }
    for (int y = -MESH_SIZE; y <= MESH_SIZE; y += MESH_SPACEING) {
        display->drawLine(Vector2(-MESH_SIZE, y), Vector2(MESH_SIZE, y));
    }
}

int main() {
    auto simulatorDisplay = std::make_unique<SimDisplay>();
    
    if(!initializeSDL()) {
        return -1;
    }
    
    simulatorDisplay->SDL_createRenderer("EgoLocalizationSim2D", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    
    bool mRunning = true;
    while(mRunning) {
        simulatorDisplay->clearScreen();
        drawBackgroundMesh(simulatorDisplay);
        simulatorDisplay->showScreen();
        //  missing some event handling to set mRunning to false.
        // Otherwise, the loop will run indefinitely.
    }

    simulatorDisplay->SDL_destroyRenderer();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
