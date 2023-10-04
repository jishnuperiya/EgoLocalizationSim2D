#ifndef SimDisplay_H
#define SimDisplay_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <string>



class SimDisplay
{
    public:

    SimDisplay();
    ~SimDisplay();

    bool SDL_createRenderer(std::string title, int displayWidth, int displayHeight);
    void SDL_destroyRenderer();
     
    void showScreen();
    void clearScreen();

    private:
    int m_displayWidth;
    int m_displayHeight;

    SDL_Window* m_sdlWindow;
    SDL_Renderer* m_sdlRenderer;
    TTF_Font *m_sdlMainFont;

};

#endif // SimDisplay_H
