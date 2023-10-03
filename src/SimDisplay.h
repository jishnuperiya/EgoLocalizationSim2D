#ifndef SimDisplay_H
#define SimDisplay_H
#include "SDL2/SDL.h"
#include <string>



class SimDisplay
{
    public:

    SimDisplay();
    ~SimDisplay();

    bool SDL_createRenderer(std::string title, int displayWidth, int displayHeight);
    void showScreen();

    private:
    int m_displayWidth;
    int m_displayHeight;

    SDL_Window* m_sdlWindow;

};

#endif // SimDisplay_H
