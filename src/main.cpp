#include <iostream>
#include "SimDisplay.h"
#include <memory>
#include <SDL2/SDL_ttf.h>


constexpr int DISPLAY_WIDTH = 1024;
constexpr int DISPLAY_HEIGHT = 980;

int main(){

    auto simulatorDisplay = std::make_unique<SimDisplay>();
    
    // Start Graphics
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
        return -1;
    }
    if( TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    
    simulatorDisplay->SDL_createRenderer("EgoLocalizationSim2D",DISPLAY_WIDTH,DISPLAY_HEIGHT);
    simulatorDisplay->showScreen();

    return 0;
}
